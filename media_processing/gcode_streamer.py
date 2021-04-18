import time
import re
import argparse
from pathlib import Path
import logging
import plac
import serial

RX_BUFFER_SIZE = 128


@plac.pos('file', 'the gcode file to stream', type=Path)
@plac.annotations(
    device_file=('the serial device path'),
    baud_rate=('the baud rate of the device to stream to',
               'option', 'br', int),
    zero_cnc=('zero the CNC to cut from it\'s current position.',
              'flag', 'zc'),
    log_level=('the log level for the program. Options are "DEBUG",'
               '"INFO", "WARNING", "ERROR", and "CRITICAL".', 'option',
               'll', str, ["DEBUG", "INFO", "WARNING", "ERROR",
                           "CRITICAL"])
)
def gcode_streamer(
    file: Path,
    device_file: str,
    baud_rate: int = 115200,
    zero_cnc: bool = False,
    log_level: str = "INFO"
):
    logging.basicConfig()
    logging.getLogger().setLevel(log_level)

    with serial.Serial(device_file, baud_rate) as s_conn:
        logging.info("Initializing grbl")
        s_conn.write("\r\n\r\n".encode())
        time.sleep(2)
        s_conn.flushInput()
        s_conn.write("$X\n".encode())
        resp = s_conn.readline().strip().decode()
        logging.info(f"Unlocked: {resp}")
        if zero_cnc:
            s_conn.write("G92X0Y0Z0\n".encode())
            resp = s_conn.readline().strip().decode()
            logging.info(f"Zeroed: {resp}")

        t_start = time.time()
        with open(file, mode='r') as f:
            g_consumed = 0
            g_error = 0
            g_buffer = []
            for i, line in enumerate(f):
                line = re.sub('\s|\(.*?\)', '', line).upper()
                g_buffer.append(len(line))

                # If the buffer is full, wait for a response
                while sum(g_buffer) >= RX_BUFFER_SIZE - 1 | s_conn.inWaiting():
                    grbl_resp = s_conn.readline().strip().decode()

                    # Debug response
                    if grbl_resp.find('ok') < 0 and grbl_resp.find('error') < 0:
                        logging.info(f"MSG: '{grbl_resp}'")
                    else:  # Interpreted GCode response
                        if grbl_resp.find('error') >= 0:
                            logging.warning(f"GCode Error: {grbl_resp}")
                            g_error += 1
                        g_consumed += 1
                        logging.info(f"REC<{g_consumed}: '{grbl_resp}'")
                        del g_buffer[0]

                s_conn.write(f'{line}\n'.encode())
                logging.info(f"SND>{i}: '{line}'")

            while i > g_consumed:
                grbl_resp = s_conn.readline().strip().decode()
                # Debug response
                if grbl_resp.find('ok') < 0 and grbl_resp.find('error') < 0:
                    logging.info(f"MSG: '{grbl_resp}'")
                else:  # Interpreted GCode response
                    if grbl_resp.find('error') >= 0:
                        logging.warning(f"GCode Error: {grbl_resp}")
                        g_error += 1
                    g_consumed += 1
                    logging.info(f"REC<{g_consumed}: '{grbl_resp}'")
                    del g_buffer[0]

        t_end = time.time()
        logging.info("G-code streaming finished!")
        logging.info(f"Time elapsed: {t_end - t_start}")


if __name__ == '__main__':
    plac.call(gcode_streamer)

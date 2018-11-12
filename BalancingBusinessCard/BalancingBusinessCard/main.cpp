/*
 * BalancingBusinessCard.cpp
 *
 * Created: 11/3/2018 4:36:13 PM
 * Author : mschommer
 */ 

#include <avr/io.h>
#include <util/delay.h>

const uint16_t Message[] = {
0b111111111, // H
0b000010000,
0b000010000,
0b111111111,
0b000000000,
0b111111111, // E
0b100010001,
0b100010001,
0b000000000,
0b111111111, // L
0b100000000,
0b100000000,
0b100000000,
0b000000000,
0b111111111, // L
0b100000000,
0b100000000,
0b100000000,
0b000000000,
0b111111111, // O
0b100000001,
0b100000001,
0b111111111,
};

void ShowLine(uint16_t line) {
    PORTA = line & 0b000001111 << 4;
    PORTB = (line & 0b111100000 >> 1) | (line & 0b000010000 >>3);
}

int main (void)
{
	// set PB3 to be output
	DDRB = 0b01111010;
	DDRA = 0b11110000;
	while (1) {
		
		// flash# 1:
		// set PB3 high
		PORTA = 0b11110000;
		PORTB = 0b01111010;
		_delay_ms(1000);
		// set PB3 low
		PORTA = 0b00000000;
		PORTB = 0b00000000;
		_delay_ms(1000);

        for(uint8_t i = 0; i < sizeof(Message) / sizeof(Message[0]); i++){
            ShowLine(Message[i]);
            _delay_ms(10);
        }
	}
}

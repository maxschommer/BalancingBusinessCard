#include <inttypes.h>

#include <avr/io.h>

// Recieve: PA1
// Send: PB0


void initADC()
{
  /* this function initialises the ADC 

        ADC Prescaler Notes:
	--------------------

	   ADC Prescaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
  
           For more information, see table 17.5 "ADC Prescaler Selections" in 
           chapter 17.13.2 "ADCSRA – ADC Control and Status Register A"
          (pages 140 and 141 on the complete ATtiny25/45/85 datasheet, Rev. 2586M–AVR–07/10)

           Valid prescaler values for various clock speeds
	
	     Clock   Available prescaler values
           ---------------------------------------
             1 MHz   8 (125kHz), 16 (62.5kHz)
             4 MHz   32 (125kHz), 64 (62.5kHz)
             8 MHz   64 (125kHz), 128 (62.5kHz)
            16 MHz   128 (125kHz)

           Below example set prescaler to 128 for mcu running at 8MHz
           (check the datasheet for the proper bit values to set the prescaler)
  */

  // 8-bit resolution
  // set ADLAR to 1 to enable the Left-shift result (only bits ADC9..ADC2 are available)
  // then, only reading ADCH is sufficient for 8-bit results (256 values)
  ADMUX =
            (0 << REFS1) |     // left shift result
            (0 << REFS0) |     // Sets ref. voltage to VCC, bit 1
            (1 << ADLAR) |     // Sets ref. voltage to VCC, bit 0
            (0 << MUX4)  |     // use ADC2 for input (PA1), MUX bit 4
            (0 << MUX3)  |     // use ADC2 for input (PA1), MUX bit 3
            (0 << MUX2)  |     // use ADC2 for input (PA1), MUX bit 2
            (0 << MUX1)  |     // use ADC2 for input (PA1), MUX bit 1
            (1 << MUX0);       // use ADC2 for input (PA1), MUX bit 0

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 16, bit 2 
            (0 << ADPS1) |     // set prescaler to 16, bit 1 
            (0 << ADPS0);      // set prescaler to 16, bit 0  
}



void write_touch_output(bool high)
{
    if (high)
    {
        PORTB = PORTB | 0b00000001;
    }
    else
    {
        PORTB = PORTB & 0b11111110;
    }
}

bool get_touch_recieve()
{
    return PORTA & (1 << PA1);
}

uint8_t touch_test()
{
    static bool high = false;
    high = !high;
    write_touch_output(high);
    return get_touch_recieve() ? 2 : 1;
}
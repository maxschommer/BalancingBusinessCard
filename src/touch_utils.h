#include <inttypes.h>

#include <avr/io.h>

// Recieve: PA1
// Send: PB0

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

inline bool get_touch_recieve()
{
    return PINA & 1<<PINA1;
}

uint8_t touch_test()
{
    write_touch_output(true);

    uint8_t count = 0;

    while (!get_touch_recieve())
    {
        count++;
        if (count & 0b100000){
            // count >= 32
            break;
        }
    }

    write_touch_output(false);
    return count;
}
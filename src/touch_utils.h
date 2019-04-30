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
#include <inttypes.h>

#include <avr/io.h>

class TouchSense
{
  public:
    uint8_t threshold = 10;
    uint8_t read_val(){
        write_touch_output(true);

        uint8_t count = 0;

        while (!get_touch_recieve())
        {
            count++;
            if (count & 0b100000)
            {
                // count >= 32
                break;
            }
        }

        write_touch_output(false);
        return count;
    }

    inline bool read()
    {
        return read_val() > threshold;
    }

    // Returns true once each time the button has been newly pressed.
    inline bool just_pressed(){
        bool val = read();
        if (val && !last_value){
            last_value = val;
            return true;
        }
        last_value = val;
        return false;
    }

  private:
    bool last_value = false;

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
        return PINA & 1 << PINA1;
    }
};

// Recieve: PA1
// Send: PB0

// uint8_t touch_test()

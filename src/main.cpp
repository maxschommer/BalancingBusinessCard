/*
 * BalancingBusinessCard.cpp
 *
 * Created: 11/3/2018 4:36:13 PM
 * Author : mschommer
 */
// #define F_CPU 2000000UL  // 2 MHz for delay

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include "alphabet.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "TinyWireM.h"
#include "USI_TWI_Master.h"

#define LIS3DHTR_ADDR 0b0011000 // 7 bit I2C address for LIS3DHTR accelerometer sensor
// #define LIS3DHTR_ADDR 0b0011001 // 7 bit I2C address for LIS3DHTR accelerometer sensor (last bit high)
// #define LIS3DHTR_ADDR 0x28 // Bosch IMU

void Init_ACC()
{ // Setup the LIS3DHTR
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(0xAC);		// Access Command Register
	TinyWireM.send(0b00000001); // Using one-shot mode for battery savings
	//TinyWireM.send(B00000000);          // if setting continious mode for fast reads
	TinyWireM.endTransmission(); // Send to the slave
}

void ShowLine(uint16_t line)
{
	// PORTA = (line & 0b000011111) << 3; // LED0, LED1, LED2, LED3, LED4
	PORTB = ((line & 0b000100000) << 1);  // LED5
	PORTB |= ((line & 0b001000000) >> 1); // LED6
	PORTB |= ((line & 0b010000000) >> 3); // LED7
	PORTB |= ((line & 0b100000000) >> 5); // LED8
}

int lis3dhReadInt(unsigned char address)
{
	unsigned char msb, lsb;
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(address);
	TinyWireM.endTransmission();
	TinyWireM.requestFrom(LIS3DHTR_ADDR, 2);
	while (TinyWireM.available() < 2)
		;
	msb = TinyWireM.receive();
	lsb = TinyWireM.receive();
	return (int)msb << 8 | lsb;
}

static int32_t modifyPointer(uint8_t *bufp)
{
	bufp[0] = 0b10101010;
}

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
							  uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
							 uint16_t len);
static void platform_init(void);

/* Private variables ---------------------------------------------------------*/
static float acceleration_mg[3];
static float temperature_degC;
static uint8_t whoamI;
static uint8_t tx_buffer[1000];

uint8_t test_i2c()
{
	// modifyPointer(&xL);
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(0x0f);		 // read ctrl_reg_0
								 //
	TinyWireM.endTransmission(); // Send 1 byte to the slave
	// TinyWireM.endTransmission(); // Send 1 byte to the slave
	// _delay_ms(0.1);
	TinyWireM.requestFrom(LIS3DHTR_ADDR,1); // Request 1 byte from slave
	uint8_t xL = 0xff;
	return TinyWireM.receive();

	//if(xL ==  0)
	//{
	//PORTA = PORTA | 1<<PA3;
	//}
}

int main()
{

	// Configuring ATTiny

	//CLKPR = 1<<CLKPCE;
	//CLKPR = 1<<CLKPS1;                    // Set clock division to 4

	TCCR0B = 1 << CS02; // Divide clock by 256

	USICR = 1 << USIWM1; // Enable Two-Wire mode of USI register

	DDRB = 0b01111010; // Set LEDs on port B as output
	// DDRA = 0b11111000;                    // Set LEDs on port A as output

	// Parameters
	char message[] = "MAX";				 // Message to display
	int kerning = 2;					 // Space between letters
	int buffer = 20;					 // Space on both sides of displayed message
	uint32_t switchDebounceTime = 200;   // Time switch must debounce
	uint8_t swingTimeTrailingAvgLen = 5; // Trailing average number for swing time

	// Variable Initializations
	uint32_t timerOverflowCount = 0; // Each tick is 0.032768s
	uint32_t totalTime = 0;			 // Each tick of totalTime is 0.000128s
	uint32_t lastSwitchedTime = 0;   // Time that the switch last changed
	long double swingTime = 2000;	// Initial guess for time to swing back and forth
	int messageIndex = 0;			 // Index of displayed message

	bool messageStarted = false;	 // State of message display. Starts on a change of state
	bool switchState = true;		 // State of debounced tilt switch, either 0 or 1
	bool countStarted = false;		 // State of switch counter, 1 if started and 0 if not
	uint32_t switchPreviousTime = 0; // Time of triggering switch

	TinyWireM.begin(); // initialize I2C lib

	uint16_t data_display = 0;

	// Generate Flash Pattern
	struct FlashPattern flashPattern = convertString(message, kerning);
	long double timeToWait;

	int byteCount = 0;

	while (1)
	{
		data_display = test_i2c();
		ShowLine(data_display << 1); // Show high bits
		_delay_ms(500);
		ShowLine(data_display << 5); // Show low bits
		_delay_ms(500);

		ShowLine(0b100000000);
		_delay_ms(10);
	}

	while (1)
	{
		// Calculate how many ticks each line should last
		timeToWait = swingTime / (2 * buffer + flashPattern.length);

		// Record total time since start
		if ((TIFR & (1 << TOV0)) == (1 << TOV0)) // check if overflow flag is set
		{
			TIFR = 1 << TOV0;
			; //clear timer1 overflow flag
			timerOverflowCount++;
		}
		totalTime = TCNT0L + 256 * timerOverflowCount; // total time since start of uC

		// Debounce tilt switch
		if (((PINA & (1 << PINA1)) != (switchState << PINA1))) // Switch triggered
		{
			// PORTA = PORTA | (1<<PA3);
			if (countStarted == false) // If counter hasn't started yet
			{
				countStarted = true;			// Start counter
				switchPreviousTime = totalTime; // Set counter start time
			}
			else // If the counter has started
			{
				if ((totalTime - switchPreviousTime) > switchDebounceTime)
				{
					// On change of state, update trailing average
					swingTime = swingTime * (swingTimeTrailingAvgLen - 1) / swingTimeTrailingAvgLen +
								(totalTime - lastSwitchedTime) / swingTimeTrailingAvgLen;

					lastSwitchedTime = totalTime;
					switchState = !switchState;
					countStarted = false;  // End the counter
					messageStarted = true; // Start message
				}
			}
		}
		else // If switch is not triggered
		{
			countStarted = false; // End the counter
		}

		if (messageStarted)
		{
			if ((totalTime - lastSwitchedTime) > (buffer * timeToWait))
			{
				if (switchState)
				{
					// Get index of message using the time.
					messageIndex = flashPattern.length - floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
				}
				else
				{
					// Get index of message using the time.
					messageIndex = floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
				}
				if (messageIndex < flashPattern.length)
				{
					ShowLine(flashPattern.data[messageIndex]);
				}
				else // Message display finished
				{
					messageStarted = false;
					messageIndex = 0;
				}
			}
		}
	}
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
							  uint16_t len)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(reg); // Access Register
	TinyWireM.write(bufp, len);
	TinyWireM.endTransmission(LIS3DHTR_ADDR);

	return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
							 uint16_t len)
{
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.write(reg); // Register to start at
	TinyWireM.endTransmission(LIS3DHTR_ADDR);

	_delay_ms(1);
	TinyWireM.requestFrom(LIS3DHTR_ADDR, len); // Request len bytes from slave

	uint8_t inc = 0; // Counter for writing to bufp
	while (TinyWireM.available())
	{
		bufp[inc] = TinyWireM.read();
		inc++;
	}
	return 0;
}

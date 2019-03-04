/*
 * BalancingBusinessCard.cpp
 *
 * Created: 11/3/2018 4:36:13 PM
 * Author : mschommer
 */
#define F_CPU 2000000UL // 2 MHz for delay

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TinyWireM.h"
#include "USI_TWI_Master.h"

#include "alphabet.h"
#include "accelerometer_utils.h"

void Init_ACC()
{												   // Setup the LIS3DHTR
	lis3dhWriteByte(LIS3DH_CTRL_REG1, 0b10010111); // 1.344 kHz , No Low-power mode, all axes enabled
	return;
	TinyWireM.beginTransmission(LIS3DHTR_ADDR);
	TinyWireM.send(0xAC);		// Access Command Register
	TinyWireM.send(0b00000001); // Using one-shot mode for battery savings
	//TinyWireM.send(B00000000);          // if setting continious mode for fast reads
	TinyWireM.endTransmission(); // Send to the slave
}

// Gets the current x-axis acceleration in m/s
float read_accel()
{
	// TODO: read all 10 bits
	// int raw = lis3dhReadInt(LIS3DH_OUT_X_L); // 10 bits of data
	int8_t raw = lis3dhReadByte(LIS3DH_OUT_X_H);
	return (int16_t(raw)<<2) * 0.004 * 9.8;			 // 4 milligees per digit in +-2g mode
}

void ShowLine(uint16_t line)
{
	PORTA = (PORTA & (~(0b000011111 << 3))) | (line & 0b000011111) << 3; // LED0, LED1, LED2, LED3, LED4
	PORTB = ((line & 0b000100000) << 1);								 // LED5
	PORTB |= ((line & 0b001000000) >> 1);								 // LED6
	PORTB |= ((line & 0b010000000) >> 3);								 // LED7
	PORTB |= ((line & 0b100000000) >> 5);								 // LED8
}

uint8_t test_i2c()
{
	return lis3dhReadByte(LIS3DH_OUT_X_H);
}

// current_time returns the current time in increments of about 0.1 ms (1 tick), 0.000128s for 2MHz clock
// Must be called at least 30 times per second, or could lose count.
uint32_t current_time()
{
	static uint32_t timerOverflowCount = 0; // Each overflow count is 0.032768s for 2MHz clock

	// Record total time since start
	if ((TIFR & (1 << TOV0)) == (1 << TOV0)) // check if overflow flag is set
	{
		TIFR = 1 << TOV0; //clear timer1 overflow flag
		timerOverflowCount++;
	}
	return TCNT0L + 256 * timerOverflowCount; // total time since start of uC
}

// Positive dir detects minima, negative dir detects maxima
uint32_t detect_edge(int8_t dir)
{
	const float DEBOUNCE_THRESH = 1.0; // m/s^2
	float min_detected = 9999999;
	uint32_t min_time = current_time();

	while (true)
	{
		float val = read_accel() * dir;
		uint32_t t = current_time();
		if (val > min_detected + DEBOUNCE_THRESH)
		{
			return min_time;
		}

		if (val < min_detected)
		{
			min_detected = val;
			min_time = t;
		}
	}
}

int main()
{
	// Configuring ATTiny

	CLKPR = 1 << CLKPCE;
	CLKPR = 1 << CLKPS1; // Set clock division to 4

	TCCR0B = 1 << CS02; // Divide clock by 256

	USICR = 1 << USIWM1; // Enable Two-Wire mode of USI register

	DDRB = 0b01111010; // Set LEDs on port B as output
	DDRA = 0b11111000; // Set LEDs on port A as output
	TinyWireM.begin(); // initialize I2C lib

	Init_ACC();

	// Message Display Parameters
	char message[] = "MAX";			 // Message to display
	int kerning = 2;				 // Space between letters, in bars
	float before_message_time = 0.2; // Target fraction of cycle waiting before display

	// Calculated values
	float message_duration = 1.0 - 2 * before_message_time; // Target fraction of cycle

	// Variable Initializations
	uint32_t lastLeftEdgeTime = 0; // Time that the last left acceleration peak was detected
	uint32_t lastRightEdgeTime = 0;
	uint32_t estimated_period = 10000; // In ticks

	// Generate Flash Pattern
	struct FlashPattern flashPattern = convertString(message, kerning);
	long double timeToWait;

	int byteCount = 0;

	while (1)
	{
		// ShowLine(read_accel());
		// continue;
		detect_edge(-1);
		ShowLine(0b01);
		_delay_ms(100);
		ShowLine(0);
		detect_edge(1);
		ShowLine(0b10);
		_delay_ms(100);
		ShowLine(0);
	}

	while (1)
	{
		// Detect the left edge
		uint32_t previous_edge = lastLeftEdgeTime;

		lastLeftEdgeTime = detect_edge(1);
		estimated_period = previous_edge - lastLeftEdgeTime;

		// Plan the coming playback
		uint32_t message_start_time = lastLeftEdgeTime + (estimated_period / 2.0 * before_message_time);

		// // Calculate how many ticks each line should last
		// timeToWait = swingTime / (2 * buffer + flashPattern.length);

		// // Debounce tilt switch
		// if (((PINA & (1 << PINA1)) != (switchState << PINA1))) // Switch triggered
		// {
		// 	// PORTA = PORTA | (1<<PA3);
		// 	if (countStarted == false) // If counter hasn't started yet
		// 	{
		// 		countStarted = true;			// Start counter
		// 		switchPreviousTime = totalTime; // Set counter start time
		// 	}
		// 	else // If the counter has started
		// 	{
		// 		if ((totalTime - switchPreviousTime) > switchDebounceTime)
		// 		{
		// 			// On change of state, update trailing average
		// 			swingTime = swingTime * (swingTimeTrailingAvgLen - 1) / swingTimeTrailingAvgLen +
		// 						(totalTime - lastSwitchedTime) / swingTimeTrailingAvgLen;

		// 			lastSwitchedTime = totalTime;
		// 			switchState = !switchState;
		// 			countStarted = false;  // End the counter
		// 			messageStarted = true; // Start message
		// 		}
		// 	}
		// }
		// else // If switch is not triggered
		// {
		// 	countStarted = false; // End the counter
		// }

		// if (messageStarted)
		// {
		// 	if ((totalTime - lastSwitchedTime) > (buffer * timeToWait))
		// 	{
		// 		if (switchState)
		// 		{
		// 			// Get index of message using the time.
		// 			messageIndex = flashPattern.length - floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
		// 		}
		// 		else
		// 		{
		// 			// Get index of message using the time.
		// 			messageIndex = floor((totalTime - lastSwitchedTime - buffer * timeToWait) / timeToWait);
		// 		}
		// 		if (messageIndex < flashPattern.length)
		// 		{
		// 			ShowLine(flashPattern.data[messageIndex]);
		// 		}
		// 		else // Message display finished
		// 		{
		// 			messageStarted = false;
		// 			messageIndex = 0;
		// 		}
		// 	}
		// }
	}
}
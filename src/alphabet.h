#include <string.h>
#include <stdlib.h>

const uint16_t TestLEDS[] = {
	0b000000001,
	0b000000010,
	0b000000100,
	0b000001000,
	0b000010000,
	0b000100000,
	0b001000000,
	0b010000000,
	0b100000000};

struct FlashPattern
{
	int length;
	uint16_t *data; // Pointer to take dynamically sized data
};

const uint16_t Alphabet[27][5] = {
	{// A
	 0b111111111,
	 0b000010001,
	 0b000010001,
	 0b000010001,
	 0b111111111},
	{// B
	 0b111111111,
	 0b100010001,
	 0b100010001,
	 0b100010001,
	 0b011101110},
	{// C
	 0b111111111,
	 0b100000001,
	 0b100000001,
	 0b100000001,
	 0b100000001},
	{// D
	 0b111111111,
	 0b100000001,
	 0b100000001,
	 0b110000011,
	 0b011111110},
	{// E
	 0b111111111,
	 0b100010001,
	 0b100010001,
	 0b100010001,
	 0b100010001},
	{// F
	 0b111111111,
	 0b000010001,
	 0b000010001,
	 0b000010001,
	 0b000010001},
	{// G
	 0b111111111,
	 0b100000001,
	 0b100110001,
	 0b100010001,
	 0b111110001},
	{// H
	 0b111111111,
	 0b000010000,
	 0b000010000,
	 0b000010000,
	 0b111111111},
	{// I
	 0b100000001,
	 0b100000001,
	 0b111111111,
	 0b100000001,
	 0b100000001},
	{// J
	 0b111000001,
	 0b100000001,
	 0b111111111,
	 0b000000001,
	 0b000000001},
	{// K
	 0b111111111,
	 0b000010000,
	 0b000101000,
	 0b001000100,
	 0b110000011},
	{// L
	 0b111111111,
	 0b100000000,
	 0b100000000,
	 0b100000000,
	 0b110000000},
	{// M
	 0b111111111,
	 0b000001110,
	 0b000111000,
	 0b000001110,
	 0b111111111},
	{// N
	 0b111111111,
	 0b000001110,
	 0b000111000,
	 0b011100000,
	 0b111111111},
	{// O
	 0b111111111,
	 0b100000001,
	 0b100000001,
	 0b100000001,
	 0b111111111},
	{// P
	 0b111111111,
	 0b000010001,
	 0b000010001,
	 0b000010001,
	 0b000011111},
	{// Q
	 0b011111111,
	 0b010000001,
	 0b011000001,
	 0b011111111,
	 0b100000000},
	{// R
	 0b111111111,
	 0b000010001,
	 0b000110001,
	 0b001010001,
	 0b110011111},
	{// S
	 0b100011111,
	 0b100010001,
	 0b100010001,
	 0b100010001,
	 0b111110001},
	{// T
	 0b000000001,
	 0b000000001,
	 0b111111111,
	 0b000000001,
	 0b000000001},
	{// U
	 0b111111111,
	 0b100000000,
	 0b100000000,
	 0b100000000,
	 0b111111111},
	{// V
	 0b000011111,
	 0b001111000,
	 0b111000000,
	 0b001111000,
	 0b000011111},
	{// W
	 0b011111111,
	 0b111000000,
	 0b011111111,
	 0b111000000,
	 0b011111111},
	{// X
	 0b110000011,
	 0b001101100,
	 0b000010000,
	 0b001101100,
	 0b110000011},
	{// Y
	 0b000000011,
	 0b000001100,
	 0b111110000,
	 0b000001100,
	 0b000000011},
	{// Z
	 0b110000001,
	 0b101101101,
	 0b100010001,
	 0b100001101,
	 0b100000011},
	{// [space]
	 0b000000000,
	 0b000000000,
	 0b000000000,
	 0b000000000,
	 0b000000000}

};

// Given an inputString and letterKerning, convert the string
// to an array of uint16_t which is the message to be flashed
// by the LEDs
struct FlashPattern convertString(char inputString[], uint8_t letterKerning)
{
	struct FlashPattern res;
	int numItems = strlen(inputString) * 5 + ((strlen(inputString)) * letterKerning);
	uint16_t *data = (uint16_t *)malloc(numItems); // Dynamically create array (remember to free)

	// Iterate through input string
	for (uint16_t i = 0; i < strlen(inputString); i++)
	{
		int c = inputString[i];
		if (c == ' ')
		{
			c = 'Z' + 1;
		}

		for (int j = 0; j < 5; j++)
		{
			data[(5 + letterKerning) * i + j] = Alphabet[c - 65][j];
		}

		// Assign kerning spaces
		uint8_t k;
		for (k = 0; k < letterKerning; k++)
		{
			data[(5 + letterKerning) * i + 5 + k] = 0;
		}
	}

	res.length = numItems;
	res.data = data;
	return res;
}

/*
 Group LLK
 Liam Sarwas - lms2260
 Levi Oliver - lpo2105
 Kevin Chen - kxc2103
 */

#include "AT91SAM7L128.h"

#define KEYBOARD_COLUMNS 0x7f
#define KEYBOARD_ROWS 0x400fc00

const unsigned char keyboard_row_index[] = {11,12,13,14,15,26};

void keyboard_init()
{
	// Initialize the keyboard: Columns are outputs, rows are inputs
	AT91C_BASE_PMC->PMC_PCER = (uint32) 1 << AT91C_ID_PIOC; // Turn on PIOC clock
	AT91C_BASE_PIOC->PIO_PER = KEYBOARD_ROWS | KEYBOARD_COLUMNS; // Enable control
	AT91C_BASE_PIOC->PIO_PPUDR = KEYBOARD_COLUMNS; // Disable pullups on columns
	AT91C_BASE_PIOC->PIO_OER = KEYBOARD_COLUMNS;   // Make columns outputs
	AT91C_BASE_PIOC->PIO_PPUER = KEYBOARD_ROWS;    // Enable pullups on rows
	AT91C_BASE_PIOC->PIO_ODR = KEYBOARD_ROWS;      // Make rows inputs
	
	AT91C_BASE_PIOC->PIO_SODR = KEYBOARD_COLUMNS;  // Drive all columns high
	
}

void keyboard_column_high(int column)
{
	AT91C_BASE_PIOC->PIO_SODR = 1 << column;
}

void keyboard_column_low(int column)
{
	AT91C_BASE_PIOC->PIO_CODR = 1 << column;
}

int keyboard_row_read(int row)
{
	return (AT91C_BASE_PIOC->PIO_PDSR) & (1 << keyboard_row_index[row]);
}





int keyboard_get_key()
{
	int col;
	for (col = 0; col < 7; col++)
	{
		keyboard_column_low(col);
		
		int row;
		for (row = 0; row < 6; row++)
		{
			if (!keyboard_row_read(row))
			{
				keyboard_column_high(col);
				return ((row+1)*10 + (col+1));
			}
		}
		
		keyboard_column_high(col);
	}
	
	return -1;
}








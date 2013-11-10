#include "AT91SAM7L128.h"
#include "keyboard.h"

#define NUM_COLUMNS 7
#define NUM_ROWS 6
#define KEYBOARD_COLUMNS 0x7f
#define KEYBOARD_ROWS 0x400fc00

const unsigned char keyboard_row_index[] = {11,12,13,14,15,26};

/* Character codes returned by keyboard_key */

const char keyboard_keys[NUM_COLUMNS][NUM_ROWS] = {
  {'N',  'I', 'P', 'M', 'F', 'A'},
  {'C',  'R', 'V', 'B', '%', 'L'},
  {'\r', '(', ')', '~', '\b', 0},
  {'\v', '7', '8', '9', '/',  0},
  {'\n', '4', '5', '6', '*',  0},
  {'S',  '1', '2', '3', '-',  0},
  { 0,   '0', '.', '=', '+',  0}};

int old_key = -1;

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

int keyboard_current_key()
{
  int row, col;
  for (col = 0 ; col < NUM_COLUMNS ; col++)
  {
    keyboard_column_low(col);
    for (row = 0 ; row < NUM_ROWS ; row++)
      if (!keyboard_row_read(row))
      {
		keyboard_column_high(col);
		//if(key_has_been_pressed == 0)
		//{
			return keyboard_keys[col][row];
		//}
      }
    keyboard_column_high(col);
  }
  return -1;
}

void keyboard_get_entry(struct entry *result){
	int sign = 1;
	int has_number = 0;
	result->number = 0;
	
	while(1){
		int key_pressed = keyboard_get_key();	
		if(key_pressed <= '9' && key_pressed >= '0' && (result->number <= INT_MAX/10 - 1))
		{
  		  result->number *= 10;
  		  result->number += key_pressed - '0';
  		  has_number = 1;
  	}
  	if(key_pressed == '~'){
    	sign *= -1;
  	}
  	if(key_pressed == '\b'){
  		result->number /= 10;
		}
  	if(key_pressed == '*' || key_pressed == '/' || key_pressed == '+' || key_pressed == '-' || key_pressed == '\r'){
  	  if(!has_number){
  			result->number = INT_MAX;
  		}
  		result->number *= sign;
  		result->operation = key_pressed;
  		return;
  	}
  	if (has_number){
			lcd_print_int(sign*result->number);
		}
	}
}

int keyboard_get_key(){
	int current_key = keyboard_current_key();
	
	if(old_key == current_key){
		return -1;
	}else{
		old_key = current_key;
		return current_key;
	}
}

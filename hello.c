/*
Liam Sarwas
Nellie Leddy
Levi Oliver
9/16/13
*/

#include "AT91SAM7L128.h"
#include "lcd.h"

#define END_OF_NUM 11
#define END_OF_NUM_AND_EXP 15
#define ZERO 48
#define BLANK_SPACE ' '

int main()
{
  lcd_init();

  printNumber(347);
  
  return 0;
}

int printNumber(int input)
{
  int counter = END_OF_NUM;
	char output = 'a';
	int isNegative = 0;
	
	clrScreen();
	
	if(input < 0)
	{
		input = -1*input;
		isNegative = 1;
	}
		
	if(input == 0)
	{
		lcd_put_char7(ZERO, counter);
	}
	
	while(input != 0)
	{
		output = ((input % 10) + ZERO);
		input = input/10;
		lcd_put_char7(output, counter);
		counter--;
	}

	if(isNegative == 1)
	{
		lcd_put_char7('-', counter);
	}
	
	return 0;
}

int clrScreen()
{
	int i;
	for(i = 0; i < END_OF_NUM_AND_EXP; i++)
	{
		lcd_put_char7(BLANK_SPACE, i);
	}
	return 0;
}

#include "keyboard.h"

int keyboard_get_key()
{
	for (int col = 0; col < 7; col++)
	{
		keyboard_column_low(col);
		
		// TODO: do we need to use actual row numbers?
		for (int row = 0; row < 7; row++)
		{
			if (keyboard_row_read(row) == 0)
			{
				return row*10 + col;
			}
		}
		
		keyboard_column_high(col);
	}
	
	return -1;
}

// TODO: REMOVE
int main()
{
	keyboard_init();
	
	while (1)
	{
		keyboard_get_key();
	}
}
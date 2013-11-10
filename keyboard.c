#include "keyboard.h"

int keyboard_get_key()
{
	for (int col = 0; col < NUM_COLUMNS; col++)
	{
		keyboard_column_low(col);
		
		for (int row = 0; row < NUM_ROWS; row++)
		{
			if (keyboard_row_read(row) == 0)
			{
				keyboard_column_high(col);
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

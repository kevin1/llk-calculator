#ifndef _keyboard_h
#define _keyboard_h

// Initialize the keyboard and set all columns high
// with pullups on the rows
void keyboard_init();

// Set the column high or low
void keyboard_column_high(int column);
void keyboard_column_low(int column);

// Return true if the row is high, false if otherwise
unsigned char keyboard_row_read(unsigned char row);

// Returns ID of key being pressed or -1 if no key is pressed
int keyboard_get_key();

#endif

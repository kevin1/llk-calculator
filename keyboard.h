#ifndef _KEYBOARD_H
#  define KEYBOARD_H

/*
 Group LLK
	Liam Sarwas - lms2260
	Levi Oliver - lpo2105
	Kevin Chen - kxc2103

 */

/* Keyboard Layout

   Rows and columns on HP 20b schematic are reversed from what you'd expect

   Columns are outputs; rows are read

            Row0  Row1  Row2 Row3 Row4 Row5
            PC11  PC12  PC13 PC14 PC15 PC26

Col0  PC0     N   I/YR  PV   PMT   FV  Amort
Col1  PC1   CshFI  IRR  NPV  Bond  %    RCL
Col2  PC2   INPUT   (    )   +/-   <-
Col3  PC3    UP     7    8    9    /                             
Col4  PC4   DOWN    4    5    6    *                                
Col5  PC5   SHIFT   1    2    3    -                             
Col6  PC6           0    .    =    +         

  ON/CE is separate
 */

// Initialize the keyboard and set all columns high with pullups on the rows
extern void keyboard_init(void);

// Set the given column high
extern void keyboard_column_high(int column);

// Set the given column low
extern void keyboard_column_low(int column);

// Return true if the row is high, false otherwise
extern int keyboard_row_read(int row);

// Returns an int equal to 10*(row being pressed + 1) + (column be pressed + 1) or -1 if nothing is being pressed. This is our own keyboard matrix.
int keyboard_get_key();


#endif



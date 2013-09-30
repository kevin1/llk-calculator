/*
 Group LLK
 Liam Sarwas - lms2260
 Levi Oliver - lpo2105
 Kevin Chen - kxc2103
 */

#include "AT91SAM7L128.h"
#include "lcd.h"
#include "keyboard.h"

int main()
{

  // Disable the watchdog timer
  *AT91C_WDTC_WDMR = AT91C_WDTC_WDDIS;

  lcd_init();
  keyboard_init();

	
  for (;;) {
	  char button;
	  switch(keyboard_get_key()){
		  case -1: button = '\\'; break;
		  case 11: button = 'N'; break;
		  case 12: button = 'C'; break;
		  case 13: button = 'I'; break;
		  case 14: button = 'u'; break;
		  case 15: button = 'd'; break;
		  case 16: button = 'b'; break;
		  case 21: button = 'I'; break;
		  case 22: button = 'I'; break;
		  case 23: button = '('; break;
		  case 24: button = '7'; break;
		  case 25: button = '4'; break;
		  case 26: button = '1'; break;
		  case 27: button = '0'; break;
		  case 31: button = 'P'; break;
		  case 32: button = 'N'; break;
		  case 33: button = ')'; break;
		  case 34: button = '8'; break;
		  case 35: button = '5'; break;
		  case 36: button = '2'; break;
		  case 37: button = '.'; break;
		  case 41: button = 'P'; break;
		  case 42: button = 'B'; break;
		  case 43: button = '/'; break;
		  case 44: button = '9'; break;
		  case 45: button = '6'; break;
		  case 46: button = '3'; break;
		  case 47: button = '='; break;
		  case 51: button = 'F'; break;
		  case 52: button = '%'; break;
		  case 53: button = '<'; break;
		  case 54: button = '/'; break;
		  case 55: button = '*'; break;
		  case 56: button = '-'; break;
		  case 57: button = '+'; break;
		  case 61: button = 'A'; break;
		  case 62: button = 'R'; break;

	  }
	  lcd_put_char7(button, 11);	

	  
  }

  return 0;
}



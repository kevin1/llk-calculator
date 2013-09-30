#include "AT91SAM7L128.h"
#include "lcd.h"
#include "keyboard.h"

int main()
{
  int i;

  // Disable the watchdog timer
  *AT91C_WDTC_WDMR = AT91C_WDTC_WDDIS;

  lcd_init();
  keyboard_init();

	
  for (;;) {
	  lcd_print_int(keyboard_get_key());
	  
  }

  return 0;
}

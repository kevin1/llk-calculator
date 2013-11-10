/*
 * Engi E1102
 * Lab 4
 * Levi Oliver, Liam Sarwas, Kevin Chen
 * 14 Oct 2013
 */

#include "AT91SAM7L128.h"
#include "lcd.h"
#include "keyboard.h"

// Initialize hardware
void init()
{
	// Disable the watchdog timer
	*AT91C_WDTC_WDMR = AT91C_WDTC_WDDIS;
	
	lcd_init();
	keyboard_init();
	
	lcd_print_int(0);
}

#define STACK_LEN 512
// We don't need to initialize the stack because that's how stacks work
int stack[STACK_LEN];
// Index of the next open spot on the stack
int stack_pointer = 0;

void push(int num);
int pop();
void set(int index, int num);
int get(int index);

void taunt_user();

int main(){
	init();
	
	struct entry entry;
	
	// User input loop
	while (1){
		// get either number and operation, or just an operation
		keyboard_get_entry(&entry);
		// Process the entry
		// If there was a number in this entry, save to stack
		if (entry.number != INT_MAX){
			push(entry.number);
		}
		
		// If the action was the input key, or the stack is too small to do an operation
		if (entry.operation == '\r' || stack_pointer < 2){
			continue;
		}
		
		// Save the operands as the last 2 things on the stack
		int a = get(stack_pointer - 2);
		int b = get(stack_pointer - 1);
		// Store the answer
		int ans;
		// Only used in division
		int is_neg;
		
		switch (entry.operation){
			// Addition
			case '+':
				ans = a + b;
				break;
				
			// Subtraction
			case '-':
				ans = a - b;
				break;
			
			// Multiplication
			case '*':
				ans = a * b;
				break;
				
			// Division
			// Our toolchain doesn't let us divide by a variable, so this code is nasty
			case '/':
				// If Kevin tries to divide by zero
				if (b == 0){
					taunt_user();
					continue;
				}
				
				// Determine whether the result will be negative
				is_neg = (a * b < 0);
				// Take absolute value of operands
				if (a < 0) a *= -1;
				if (b < 0) b *= -1;
				
				ans = 0;
				
				// Calculate a / b
				// Subtract a - b until a is zero, counting how many times we subtracted
				while (a > 0){
					a -= b;
					ans++;
				}
				// If there is a remainder
				if (a < 0){
					// Always round down
					ans--;
				}
				
				// Correct the sign of the result
				if (is_neg){
					ans *= -1;
				}
				
				break;
				
			default:
				break;
		}
		
		// Take the 2 operands off the stack
		pop();
		pop();
		// Save answer to the end of the stack
		push(ans);
		lcd_print_int(ans);
	}
	
	return 0;
}

// Push num onto the stack and increment stack_pointer
void push(int num){
	if (stack_pointer < STACK_LEN){
		stack[stack_pointer] = num;
		stack_pointer++;
	}
}

// Return the top of the stack and decrement stack_pointer
int pop(){
	if (stack_pointer > 0){
		stack_pointer--;
		return stack[stack_pointer];
	}else{
		return INT_MAX;
	}
}

// Set the stack value at an index to num
void set(int index, int num){
	if (0 <= index && index < STACK_LEN){
		stack[index] = num;
	}
}

// Get the stack value at index without removing it from the stack
int get(int index){
	if (0 <= index && index < STACK_LEN){
		return stack[index];
	}else{
		return INT_MAX;
	}
}

// Clear all values from the stack
void clear(){
	stack_pointer = 0;
}

// Print a slowly scrolling error message onto the screen
void taunt_user(){
	// Buffer that will be sliced to make the message
	char* err_msg = "          Error";
	
	int i;
	for (i = 0; i < 15; i++){
		lcd_clear();
		// Give the pointer of the first value we want to print
		// Manipulating i slices characters off the beginning of the printed message
		lcd_print7(err_msg + i);
		
		int j;
		// Wait before shifting the message
		for (j = 0; j < 40000; j++);
	}
	lcd_clear();
}

/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "lcd_functions.h"
#include <stdio.h>

// Initialize the LCD
void initLCD() {
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Ready!");
}

// Print a string to the LCD
void printLCD(char str[], int line) {
    LCD_Position(line,0);
    LCD_PrintString(str);
}

// Clear the LCD display
void clearLCD() {
    LCD_ClearDisplay();
}

// Print an integer to the LCD
void printUint32LCD(uint32 val, int line) {
    char buf[16];
    sprintf(buf, "%lu", val);
    printLCD(buf, line);
}

// Print a double to the LCD (unused)
void printDoubleLCD(double val, int line) {
    char buf[16];
    sprintf(buf, "%lf", val);
    printLCD(buf, line);
}

// Print a signed integer to the LCD
void printIntegerLCD(int val, int line) {
    char buf[16];
    sprintf(buf, "%d", val);
    printLCD(buf, line);
}
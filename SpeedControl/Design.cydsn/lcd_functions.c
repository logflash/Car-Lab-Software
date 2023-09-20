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

void initLCD() {
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Ready!");
}

void printLCD(char str[], int line) {
    LCD_Position(line,0);
    LCD_PrintString(str);
}

void clearLCD() {
    LCD_ClearDisplay();
}

void printUint32LCD(uint32 val, int line) {
    char buf[16];
    sprintf(buf, "%lu", val);
    printLCD(buf, line);
}

void printDoubleLCD(double val, int line) {
    char buf[16];
    sprintf(buf, "%lf", val);
    printLCD(buf, line);
}

void printIntegerLCD(int val, int line) {
    char buf[16];
    sprintf(buf, "%d", val);
    printLCD(buf, line);
}
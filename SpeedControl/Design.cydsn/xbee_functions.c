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

#include "xbee_functions.h"
#include "pid_functions.h"
#include <stdlib.h>

uint8 quitFlag = 0;

void xBeeWrite(char str[]) {
    XBee_PutString(str);
    XBee_PutString("\r\n");
}

void xBeeInterpret(char str[]) {
    
    if (!strcmp(str, "q")) {
        quitFlag = 1;
    }
    
    if (strlen(str) < 2) {
        return;
    }
    
    switch(str[0] | 32) {
        case 'p':
            setKP(atof(str+1));
        case 'i':
            setKD(atof(str+1));
        case 'd':
            setKP(atof(str+1));
    }
}

/* [] END OF FILE */
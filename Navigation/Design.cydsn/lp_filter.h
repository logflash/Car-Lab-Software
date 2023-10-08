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

#include "project.h"
#include <stdlib.h>

// Low-pass filter on the input
typedef struct {
    
    // Filter (max size 128)
    volatile uint32 buf[128];
    volatile int size;
    volatile int idx;
    volatile uint32 sum;
    volatile uint32 avg;
    volatile uint32 median;
    
} lpFilter;

void filterResize(volatile lpFilter *filter, int size);

void filterPush(volatile lpFilter *filter, uint32 input);

/* [] END OF FILE */

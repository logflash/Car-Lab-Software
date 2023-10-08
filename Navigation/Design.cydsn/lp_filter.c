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

#include "lp_filter.h"

void filterResize(volatile lpFilter *filter, int size) {
    
    // Filter size
    filter->size = size;
}

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void filterPush(volatile lpFilter *filter, uint32 input) {
    
    // Get the filter size
    int size = filter->size;
    
    // Go to the next index
    int currIdx = filter->idx;
    int nextIdx = (currIdx + 1) % (size + 1);
    
    // Update the value
    (filter->buf)[currIdx] = input;
    
    // Update the sum
    filter->sum += (filter->buf)[currIdx];
    filter->sum -= (filter->buf)[nextIdx];
    
    // Update the average
    filter->avg = (filter->sum) / (filter->size);
    
    // Update the median
    uint32 aux[size];
    for (int i=0; i<size; i++) {
        aux[i] = (filter->buf)[i];
    }
    qsort(aux, size, sizeof(aux[0]), cmp);

    filter->median = aux[size>>1];
    
    // Update the index
    filter->idx = nextIdx;
}

/* [] END OF FILE */

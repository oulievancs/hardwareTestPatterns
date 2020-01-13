#include "stdio.h"

unsigned long long int lfsr(void) {
    int shifts[3] = {7, 9, 13}, j=0;
    unsigned long long int start_state = (unsigned long long int) 0xACE1u;
    unsigned long long int lfsr = start_state;
    unsigned long long int period = 0;
    
    do {
        lfsr ^= lfsr >> shifts[0];
        printf("\tCycle %d %llu\n", ++j, lfsr);
        
        lfsr ^= lfsr << shifts[1];
        printf("\tCycle %d %llu\n", ++j, lfsr);
        
        lfsr ^= lfsr >> shifts[2];
        printf("\tCycle %d %llu\n", ++j, lfsr);
        
        ++period;
    } while (lfsr != start_state);
    
    return period;
}

int main() {
    printf("Period: %llu \n", lfsr());
}

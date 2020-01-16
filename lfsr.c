/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#include "shift.h"

void lfsr_counter(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N, xor_in1, xor_in2;
    N = (unsigned long long int) pow(2, n) - 1;
    
    unsigned long long int x = N;
    for (i=0; i<N; i++) {
        counter[i] = x;
        
        xor_in1 = x & 0x1;
        xor_in2 = (x >> (n - 1)) & 0x1;
        
        if ((xor_in1 ^ xor_in2) & 0x1) {
            if (! (x >> (n - 1) & 0x1)) {
                x += pow(2, n-1);
            }
        } else {
            if (x >> (n - 1) & 0x1) {
                x -= pow(2, n-1);
            }
        }
        x = rightRotateOneBit(x, n);
    }
    counter[N] = N;
}

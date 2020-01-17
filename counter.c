/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#include "math.h"

void counter(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N;
    N = (unsigned long long int) pow(2, n) - 1;
    
    for (i=1; i<N; i++) {
        counter[i-1] = (unsigned long long int) i;
    }
}

unsigned long long int counter_next_state(unsigned long long int n, unsigned long long int prev_state) {
    unsigned long long int i, N, next_state=0;
    N = (unsigned long long int) pow(2, n) - 1;
    
    if (prev_state < N) {
        next_state = prev_state + 1;
    }
    
    return next_state;
}

void counter1(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N;
    N = (unsigned long long int) pow(2, n);
    
    counter[0] = 1;
    for (i=1; i<N; i++) {
        counter[i] = (unsigned long long int) i;
    }
}

unsigned long long int counter1_next_state(unsigned long long int n, unsigned long long int prev_state) {
    unsigned long long int i, N, next_state=0;
    N = (unsigned long long int) pow(2, n);
    
    if (prev_state < N) {
        next_state = prev_state + 1;
    } else {
    	next_state = 1;
   	}
    
    return next_state;
}

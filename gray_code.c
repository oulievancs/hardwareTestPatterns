/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#include "gray_code.h"

void gray_code(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int N = 1 << n, x, i, j=0;
    
    for (i=0; i<N; i++) {
        x = i ^ (i >> 1);
        if (x != 0 && x != N-1) {
            counter[j++] = x;
        }
    }
}

unsigned long long int gray_code_next_state(unsigned long long int n, unsigned long long int prev_state) {
    unsigned long long int N = 1 << n, i, x, j=0, next_state=0;
    int found = 0;
    
    for (i=0; i<N; i++) {
		x = i ^ (i >> 1);
		
		if (prev_state == x && found == 0) {
			found = 1;
			continue;
		}
		
		if (found == 1 && x != 0) {
			next_state = x;
			break;
		}
	}
    
    return next_state;
}

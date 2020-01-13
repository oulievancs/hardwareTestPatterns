#include "stdio.h"
#include "binaryToString.h"

void gray_code(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int N = 1 << n, i, j=0;
    
    for (i=0; i<N; i++) {
        int x = i ^ (i >> 1);
        if (x != 0 && x != N-1) {
            counter[j++] = x;
        }
    }
}

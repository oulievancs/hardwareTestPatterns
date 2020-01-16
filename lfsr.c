/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#define NUMBER_BITS sizeof(unsigned long long int)*8

unsigned long long int leftRotateOneBit(unsigned long long int n, unsigned long long int bits);

void lfsr_counter(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N, tmp;
    N = (unsigned long long int) pow(2, n) - 1;
    
    unsigned long long int x = N;
    for (i=0; i<N; i++) {
        counter[i] = x;
        
        tmp = leftRotateOneBit(x, n);
        if ((tmp >> 1 & 0x1) ^ (tmp & 0x1)) {
            if (! (tmp >> 1 & 0x1)) {
                tmp += pow(2, 1);
            }
        } else {
            if (tmp >> 1 & 0x1) {
                tmp -= pow(2, 1);
            }
        }
        
        x = tmp;
    }
}

unsigned long long int leftRotateOneBit(unsigned long long int n, unsigned long long int bits) {
    /* In n>>d, first d bits are 0.
    To put last 3 bits of at
    first, do bitwise or of n>>d 
    with n <<(INT_BITS - d) */
    unsigned long long int result = (n << 1)|(n >> (NUMBER_BITS - 1)); 
    
    if (result >= pow(2, bits)) {
        unsigned long long int res = result >> bits;
        if (res & 0x1) {
            result += 1;
            result -= pow(2, bits);
        }
    }
    return result;
}

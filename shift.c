/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#include "math.h"

unsigned long long int leftRotateOneBit(unsigned long long int n, unsigned long long int BITS) {
    /* In n<<d, first d bits are 0.
    To put last 3 bits of at
    first, do bitwise or of n>>d 
    with n >> (INT_BITS - d) */
    unsigned long long int tmp = (n >> (BITS - 1)) & 0x1;
    unsigned long long int result = (n << 1); 
    
    if (tmp & 0x1) {
        result += 1;
        result -= (unsigned long long int) pow(2, BITS);
    }
    
    return result;
}

unsigned long long int rightRotateOneBit(unsigned long long int n, unsigned long long int BITS) {
    /* In n>>d, first d bits are 0.
    To put last 3 bits of at
    first, do bitwise or of n>>d 
    with n << (INT_BITS - d) */
    unsigned long long int tmp = n & 0x1;
    unsigned long long int result = (n >> 1);
    
    if (tmp & 0x1) {
        result += (unsigned long long int) pow(2, BITS-1);
    }
    
    return result;
}

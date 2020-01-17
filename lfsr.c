/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#include "shift.h"
#include "stdio.h"
#include "stdlib.h" 
#include "time.h"

void lfsr_counter(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N, xor_in1, xor_in2, xor_in3, xor_in4;
    N = (unsigned long long int) pow(2, n) - 1;
    
    // Use current time as  
    // seed for random generator 
    srand(time(NULL));
    
    unsigned long long int x = (unsigned long long int) (rand() % N + 1);
    
    printf("### LFSR STARTS RANDOMLY FROM: %llu .\n", x);
    for (i=0; i<N; i++) {
        counter[i] = x;
        
        xor_in1 = x & 0x1;
        if ((n > 2 && n < 5) || (n > 5 && n < 8) || n == 15 || n == 22) {
            xor_in2 = (x >> (n - 1)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 5 || n == 11 || n == 21 || n == 29) {
            xor_in2 = (x >> (n - 2)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 8 || n == 19) {
            xor_in2 = (x >> (n-2)) & 0x1;
            xor_in3 = (x >> (n-3)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 9) {
            xor_in2 = (x >> (n-5)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 10 || n == 17 || n == 20 || n == 25 || n == 28) {
            xor_in2 = (x >> (n - 7)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 12) {
            xor_in2 = (x >> (n - 5)) & 0x1;
            xor_in3 = (x >> (n - 8)) & 0x1;
            xor_in4 = (x >> (n - 9)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3 ^ xor_in4) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 13 || n == 24) {
            xor_in2 = (x >> (n - 9)) & 0x1;
            xor_in3 = (x >> (n - 10)) & 0x1;
            xor_in4 = (x >> (n - 12)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3 ^ xor_in4) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 14) {
            xor_in2 = (x >> (n - 2)) & 0x1;
            xor_in3 = (x >> (n - 3)) & 0x1;
            xor_in4 = (x >> (n - 13)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3 ^ xor_in4) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 18) {
            xor_in2 = (x >> (n - 11)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 23) {
            xor_in2 = (x >> (n - 18)) & 0x1;
            
            if ((xor_in1 ^ xor_in2) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 26 || n == 27) {
            xor_in2 = (x >> (n - 18)) & 0x1;
            xor_in3 = (x >> (n - 19)) & 0x1;
            xor_in4 = (x >> (n - 25)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3 ^ xor_in4) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        } else if (n == 30) {
            xor_in2 = (x >> (n - 14)) & 0x1;
            xor_in3 = (x >> (n - 15)) & 0x1;
            xor_in4 = (x >> (n - 29)) & 0x1;
            
            if ((xor_in1 ^ xor_in2 ^ xor_in3 ^ xor_in4) & 0x1) {
                if (!(x & 0x1)) {
                    x += 1;
                }
            } else  {
                if (x & 0x1) {
                    x -= 1;
                }
            }
        }
        x = rightRotateOneBit(x, n);
    }
}

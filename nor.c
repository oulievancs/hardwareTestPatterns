#include "stdio.h"
#include "math.h"
#include "nor.h"

unsigned int nor(unsigned int a, unsigned int b, unsigned int n) {
	int i;
	int res=0;
	for (i=n-1; i>= 0; i--) {
		int k = !((a >> i) | (b >> i));
		if (k >= 1) {
			res += pow(2, i);
		} else {
			
		}
	}
	return res;
}

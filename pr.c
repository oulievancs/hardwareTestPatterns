#include "stdio.h"
#include "nor.h"

int main() {
	unsigned int a=0, b=1, res;
	res = nor(a, b, 3);

	printf("%u\n", res);
}

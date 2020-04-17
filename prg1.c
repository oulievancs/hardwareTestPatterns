/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * Subject: C progam that implements an accumulator which
 *             is powered from an k-bit counter.
*/
#include "stdio.h"
#include "stdlib.h"


int main(int argc, char **argv) {
	if (argc == 3) {
		int i, j, ii, jj;
		char cmdbuf[80];
		
		i = (int) atoi(argv[1]);
		j = (int) atoi(argv[2]);
		
		// jj like n-coverage and ii like k accumulator size.
		for (ii=3; ii <= i; ii++) {
			for (jj=3; jj <= j; jj++) {
				snprintf (cmdbuf, sizeof(cmdbuf), "./prg -m 6 -n %d -k %d -onlycoverage", jj, ii);
				system(cmdbuf);
				printf(" ");
			}
			printf("\n");
		}
	} else {
		exit(1);
	}
}
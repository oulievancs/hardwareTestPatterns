/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * Subject: C functions for Binary printing and String builder from number operators.
*/
#include "stdio.h"
#include "stdlib.h"
#include "binaryToString.h"

void printBinary(unsigned long long int number, int digits, FILE *fp) {
    if (digits <= 0) {
        fprintf(stderr, "*At printBinary(<usigned long long int>, <digits>, <FILE *>) you can't use digits as <= 0.\n");
        exit(1);
    }
    int i;
    for(i=digits-1; i>=0; i--) {
        if (number >> i & 0x1) {
            fprintf(fp, "%d", 1);
        } else {
            fprintf(fp, "%d", 0);
        }
    }
}

void binaryToStr(unsigned int long long number, int digits, char *p) {
    if (digits <= 0) {
        fprintf(stderr, "*At printBinary(<usigned long long int>, <digits>, <FILE *>) you can't use digits as <= 0.\n");
        exit(1);
    }
    int i;
    for(i=digits-1; i>=0; i--) {
        if (number >> i & 0x1) {
            p[i] = '1';
        } else {
            p[i] = '0';
        }
    }
}

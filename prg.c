/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * Subject: C progam that implements an accumulator which
 *             is powered from an k-bit counter.
*/
#include "stdio.h"
#include "string.h"
#include "math.h"	
#include "add.h"
#include "binaryToString.h"

int main(int argc, char **argv){
    int k, cov, prev_reg, idx=0, cnt_idx, arr_idx=0, i, there_is;
    unsigned int *arr, *cnt, reg;
    
    printf("Enter K: ");
    scanf("%d", &k);
    
    printf("Enter n-bit coverage: ");
    scanf("%d", &cov);
    
    arr = (unsigned int *) malloc(sizeof(unsigned int) * (int) pow(2, k));
    cnt = (unsigned int *) malloc(sizeof(unsigned int) * ((int) pow(2, k) - 2));
    
    for(i=1; i<=(pow(2, k)-2); i++) {
        cnt[i-1] = (unsigned int) i;
    }
    
    if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            stdout = fopen(argv[2], "w");
        }
    }
    
    printf("********************ACCUMULATOR STARTED*******************************\n");
    printf("----------------------------------------------------------------------\n");
    /*Initialize the zero at Register.*/
    reg = 0;
    arr[arr_idx++] = (unsigned int) 0;
    
    /*
     * Start Calculate the Accumularor output using counter.
     * Register starts from 0
    */
    printf("cnt = ");
    for(i=0; i<k; i++) {
        printf("-");
    }
    printf(", Reg = ");
    printBinary(reg, k, stdout);
    printf("\n");
    do {
        cnt_idx = 0;
        do {
            idx++;
            
            there_is = 0;
            reg = add(reg, cnt[cnt_idx], 3);
            
            for (i=0; i<arr_idx; i++) {              
                if (arr[i] == (reg % (unsigned int)pow(2, k))) {
                    there_is = 1;
                }
            }
            
            if (there_is != 1) {
                arr[arr_idx++] = (reg % (unsigned int)pow(2, k));
            }
                
            printf("cnt = ");
            printBinary(cnt[cnt_idx], k, stdout);
            printf(", Reg = ");
            printBinary(reg, k, stdout);
            printf("\n");
            cnt_idx++;
        } while (cnt[cnt_idx] <= (pow(2, k) -2));
    } while((reg % (unsigned int)pow(2, k)) != 0);
    
    printf("\n****************STATISTICS***************************************\n");
    printf("***\tNumber of cycles:\t\t %d.\n", idx);
    printf("***\t%d-coverage:\t\t\t\t%f%% .\n", cov, ((double)arr_idx/(pow(2, cov)))*100);
    printf("\n*****************************************************************\n");
    
    /*Free memory.*/
    free(arr);
    free(cnt);
    
    fclose(stdout);
    return 0;
}

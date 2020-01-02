/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * Subject: C progam that implements an accumulator which
 *             is powered from an k-bit counter.
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"	
#include "add.h"
#include "binaryToString.h"

int main(int argc, char **argv){
    int k, cov, M, prev_reg, cnt_idx, i, j, ii, there_is, tuples, idx=0, mSeq_idx=0, arr_idx=0;
    unsigned int *cnt, reg;
    char *reg1, *mSeq, **arr;
    
    printf("Enter K: ");
    scanf("%d", &k);
    
    printf("Enter n-bit coverage: ");
    scanf("%d", &cov);
    
    do {
        printf("Enter M sequence as bit(s): ");
        scanf("%d", &M);
    } while (M <= cov);
    
    tuples = (M-cov)+1;
    
    arr = (char **) malloc(sizeof(char *) * tuples);
    cnt = (unsigned int *) malloc(sizeof(unsigned int) * ((int) pow(2, k) - 2));
    reg1 = (char *) malloc(sizeof(char) * k);
    mSeq = (char *) malloc(sizeof(char) * M);
    
    if (arr == NULL || cnt == NULL || reg1 == NULL || mSeq == NULL) {
        fprintf(stderr, "There was a problem on memory allocation.\n");
        exit(10);
    }
    
    for(i=1; i<=(pow(2, k)-2); i++) {
        cnt[i-1] = (unsigned int) i;
    }
    
    if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            stdout = fopen(argv[2], "w");
        }
        
        if (stdout == NULL) {
            fprintf(stderr, "There was a problem on file opening.\n");
            exit(11);
        }
    }
    
    printf("***********************ACCUMULATOR STARTED****************************\n");
    printf("----------------------------------------------------------------------\n");
    /*Initialize the zero at Register.*/
    reg = 0;
    
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
            
            reg = ADD(reg, cnt[cnt_idx], k);
            
            printf("cnt = ");
            printBinary(cnt[cnt_idx], k, stdout);
            printf(", Reg = ");
            printBinary(reg, k, stdout);
            printf("\n");
            
            if (M > idx-1) {
                binaryToStr(reg, k, reg1);
                
                mSeq[mSeq_idx++] = reg1[k-1];
            }
            cnt_idx++;
        } while (cnt[cnt_idx] <= (unsigned int)(pow(2, k) - 2));
    } while((reg % (unsigned int)pow(2, k)) != 0);
    
    printf("**************************%d-TUPLES******************************\n", tuples);
    
    if (M <= idx) {
        for(i=0; i<tuples; i++) {
            printf("->\t");
            for(j=0; j<cov; j++) {
                printf("%c", mSeq[i+j]);
            }
            
            /*
             * Check four multipled patterns.
             * If current parrern is already counted, throw it away.
            */
            for (ii=0; ii<arr_idx; ii++) {
                there_is = 1;

                for (j=0; j<cov; j++) {
                    if (arr[ii][j] != mSeq[i+j]) {
                        there_is = 0;
                        break;
                    }
                }
                if (there_is == 1) {
                    break;
                }
            }
            
            /*
             * If current pattern isn't counted or is the 1st pattern
             *   then we dave it at "arr" array.
            */
            if (there_is == 0 || arr_idx == 0) {
                arr[arr_idx++] = &mSeq[i];
            } else {
                printf(" *");
            }
            printf("\n");
        }
        
        printf("**************************STATISTICS*****************************\n");
        printf("***\tNumber of cycles           :%d\n", idx);
        printf("***\tNumber of sequence patterns:%d\n", arr_idx);
        printf("***\t%d-coverage                 :%f%%\n", cov, ((double)arr_idx/(pow(2, cov)))*100);
        
        printf("M sequence (%d-bits)           :{", M);
        for (i=0; i<M; i++) {
            printf("%c", mSeq[i]);
        }
        printf("}\n");
    } else {
        printf("Message: You must Provide M sequence less or equal than cycles of Accumulator.\n");
    }
    
    printf("*****************************************************************\n");
    
    fclose(stdout);
    /*Free memory.*/
    free(cnt);
    free(reg1);
    free(mSeq);
    free(arr);
    return 0;
}

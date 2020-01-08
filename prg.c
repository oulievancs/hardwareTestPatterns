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
    int k, cov;
    int there_is, cir_read=0;
    unsigned long long int *cnt, cnt_idx, idx=0, mSeq_idx=0, arr_idx=0, tuples, reg, M, goal=0, test_cycle=1;
    unsigned long long int i, j, ii;
    char *reg1, *mSeq, **arr, cir_name[30];
    
    /*For output and log file Stream.*/
    FILE *log, *out, *test;
    
    if (argc == 4) {
        if (strcmp(argv[3], "-o") == 0) {
            out = fopen(argv[4], "w");
            
            if (out == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(11);
            }
        }
        
        if (strcmp(argv[1], "-f") == 0) {
            test = fopen(argv[2], "w");
            cir_read = 1;
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(12);
            }
            
            out = stdout;
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "-o") == 0) {
            out = fopen(argv[2], "w");
            
            if (out == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(11);
            }
        } else if (strcmp(argv[1], "-f") == 0) {
            test = fopen(argv[2], "w");
            cir_read = 1;
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(12);
            }
            
            out = stdout;
        }
    } else {
        out = stdout;
    }
    
    if (cir_read != 1) {
        printf("Give the circuit name: ");
        scanf("%s", cir_name);
        
        test = fopen(cir_name, "w");
        
        if (test == NULL) {
            fprintf(stderr, "There was a problem on file opening.\n");
            exit(13);
        }
    }
    
    printf("Enter K: ");
    scanf("%d", &k);
    
    printf("Enter n-bit coverage: ");
    scanf("%d", &cov);
    
    /*do {
        printf("Enter M sequence as bit(s): ");
        scanf("%d", &M);
    } while (M <= cov);*/
    
    /*Calculate M sequence as Accumulator Cycles number.*/
    M = (unsigned long long int)pow(2, k)*(pow(2, k) - 2);
    /*Calculating tuples.*/
    tuples = (M-cov)+1;
    
    arr = (char **) malloc(sizeof(char *) * tuples);
    cnt = (unsigned long long int *) malloc(sizeof(unsigned long long int) * ((int) pow(2, k) - 2));
    reg1 = (char *) malloc(sizeof(char) * k);
    mSeq = (char *) malloc(sizeof(char) * M);
    
    if (arr == NULL || cnt == NULL || reg1 == NULL || mSeq == NULL) {
        fprintf(stderr, "There was a problem on memory allocation.\n");
        exit(10);
    }
    
    for(i=1; i<=(pow(2, k)-2); i++) {
        cnt[i-1] = (unsigned long long int) i;
    }
    
    
    log = fopen("accumulator.log", "w");
    if (log == NULL) {
        fprintf(stderr, "There was a problem on file opening. \"accumulator.log\"\n");
        exit(12);
    }
    
    fprintf(out, "***********************ACCUMULATOR STARTED****************************\n");
    fprintf(out, "----------------------------------------------------------------------\n");
    fprintf(log, "***********************ACCUMULATOR STARTED****************************\n");
    fprintf(log, "----------------------------------------------------------------------\n");
    /*Initialize the zero at Register.*/
    reg = 0;
    
    /*
     * Start Calculate the Accumularor output using counter.
     * Register starts from 0
    */
    fprintf(log, "cnt = ");
    for(i=0; i<k; i++) {
        printf("-");
    }
    fprintf(log, ", Reg = ");
    printBinary(reg, k, log);
    fprintf(log, "\n");
    do {
        cnt_idx = 0;
        do {
            idx++;
            
            reg = ADD(reg, cnt[cnt_idx]);
            
            fprintf(log, "Round: %llu, cnt = ", idx);
            printBinary(cnt[cnt_idx], k, log);
            fprintf(log, ", Reg = ");
            printBinary(reg, k, log);
            fprintf(log, "\n");
            
            if (M > idx-1) {
                binaryToStr(reg, k, reg1);
                
                mSeq[mSeq_idx++] = reg1[k-1];
            }
        } while (cnt[cnt_idx++] < (unsigned long long int)(pow(2, k) - 2));
    } while((reg % (unsigned long long int)pow(2, k)) != 0);
    
    
    
    fprintf(log, "**************************%d-TUPLES******************************\n", tuples);
    
    if (M <= idx) {
        for(i=0; i<tuples; i++) {
            fprintf(log, "->\t");
            for(j=0; j<cov; j++) {
                fprintf(log, "%c", mSeq[i+j]);
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
             *   then we keep it at "arr" array.
            */
            if (there_is == 0 || arr_idx == 0) {
                arr[arr_idx++] = &mSeq[i];
                
                fprintf(test, "\n%llu:", test_cycle++);
                for(j=0; j<cov; j++) {
                    fprintf(test, "%c", mSeq[i+j]);
                }
            } else {
                fprintf(log, " *");
            }
            fprintf(log, "\n");
            
            if ((int)arr_idx/(int) (pow(2, cov))*100 != 100) {
                goal++;
            }
        }
        
        fprintf(out, "**************************STATISTICS*****************************\n");
        fprintf(out, "***\tNumber of cycles           :%llu\n", idx);
        fprintf(out, "***\tNumber of sequence patterns:%llu\n", arr_idx);
        if (((double) arr_idx/(pow(2, cov))*100) >= ((double) 100)) {
            fprintf(out, "***\t100%% Reached at            :%llu\n", goal);
        } else {
            fprintf(out, "***\t100%% not Reached.          :-\n");
        }
        fprintf(out, "***\t%d-coverage                 :%f%%\n", cov, (double) arr_idx/(pow(2, cov))*100);
        
        fprintf(out, "M sequence (%llu-bits)           :{", M);
        /*for (i=0; i<M; i++) {
            printf("%c", mSeq[i]);
        }*/
        fprintf(out, "}\n");
    } else {
        fprintf(stderr, "Message: You must Provide M sequence less or equal than cycles of Accumulator.\n");
    }
    
    fprintf(log, "*****************************************************************\n");
    fprintf(out, "*****************************************************************\n");
    
    fclose(test);
    fclose(out);
    fclose(log);
    /*Free memory.*/
    free(cnt);
    free(reg1);
    free(mSeq);
    free(arr);
    return 0;
}

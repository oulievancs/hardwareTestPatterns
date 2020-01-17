/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * Subject: C progam that implements an accumulator which
 *             is powered from an k-bit counter.
*/

/*
 * Include all libraries.
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"	
#include "add.h"
#include "binaryToString.h"
#include "time.h"
#include "unistd.h"
#include "gray_code.h"
#include "counter.h"
#include "lfsr.h"

/*
 * Define Functions.
*/
void printLogo(void);
unsigned long long int next_state(const int ans, const unsigned long long int cnt, const int k);

/*
 * Start main program.
*/
int main(int argc, char **argv){
    int k, n, ans, reached = 0, non_linear;
    int there_is, test_b=0, work_b=0;
    unsigned long long int /***/cnt, cnt_c, /*cnt_idx=0,*/ idx=0, mSeq_idx=0, arr_idx=0, tuples, reg, M, goal=0, test_cycle=1;
    unsigned long long int start_counter, start_reg = 0, stop, up_limit, N, N1, N2;
    unsigned long long int i, j, ii;
    char *reg1, *mSeq, **arr, cir_name[30], signal[30];
    clock_t start, end;
    double cpu_time_used, min_cycl_per = (double) 0, tmp_per;
    
    /*For output file Stream.*/
    FILE *test, *workb;
    
    /*
     * Initialize the zero at Register.
     */
    reg = 0;
    
    printLogo();
    
    /************************************MENU***********************************************/
    if (argc == 7) {
        if (strcmp(argv[1], "-o") == 0) {
            test = fopen(argv[2], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(11);
            }
            test_b = 1;
        } else if (strcmp(argv[3], "-o") == 0) {
            test = fopen(argv[4], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(12);
            }
            test_b = 1;
        } else if (strcmp(argv[5], "-o") == 0) {
            test = fopen(argv[6], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(13);
            }
            test_b = 1;
        }
        
        if (strcmp(argv[1], "-f") == 0) {
            workb = fopen(argv[2], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(14);
            }
            work_b=1;
        } else if (strcmp(argv[3], "-f") == 0) {
            workb = fopen(argv[4], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(15);
            }
            work_b=1;
        } else if (strcmp(argv[5], "-f") == 0) {
            workb = fopen(argv[6], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(16);
            }
            work_b=1;
        }
        
        if (strcmp(argv[1], "-z") == 0) {
            reg = (int) atoi(argv[2]);
        } else if (strcmp(argv[3], "-z") == 0) {
            reg = (int) atoi(argv[4]);
        } else if (strcmp(argv[5], "-z") == 0) {
            reg = (int) atoi(argv[6]);
        }
    } else if (argc == 5) {
        if (strcmp(argv[1], "-o") == 0) {
            test = fopen(argv[2], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(17);
            }
            test_b = 1;
        } else if (strcmp(argv[3], "-o") == 0) {
            test = fopen(argv[4], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(18);
            }
            test_b = 1;
        }
        
        if (strcmp(argv[1], "-f") == 0) {
            workb = fopen(argv[4], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(19);
            }
            work_b=1;
        } else if (strcmp(argv[3], "-f") == 0) {
            workb = fopen(argv[5], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(20);
            }
            work_b=1;
        }
        
        if (strcmp(argv[1], "-z") == 0) {
            reg = (int) atoi(argv[2]);
        } else if (strcmp(argv[3], "-z") == 0) {
            reg = (int) atoi(argv[4]);
        }
    } else if (argc == 3) {
        if (strcmp(argv[1], "-o") == 0) {
            test = fopen(argv[2], "w");
            
            if (test == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(11);
            }
            test_b = 1;
        }
        
        if (strcmp(argv[1], "-f") == 0) {            
            workb = fopen(argv[2], "w");
            
            if (workb == NULL) {
                fprintf(stderr, "There was a problem on file opening.\n");
                exit(13);
            }
            work_b=1;
        }
        
        if (strcmp(argv[1], "-z") == 0) {
            reg = (int) atoi(argv[2]);
        }
    } else {
        fprintf(stderr, "./prg <-o> <fsim output> <-f> <Do script for Workbench> <-r> <start stage register>\n");
    }
    
    printf("\n\n\n");
    
    if (work_b) {
        printf("--Give Signal name: ");
        scanf("%s", signal);
    }
    /***************************************************************************************/
    /***************************************************************************************/
    
    
    
    
    
    
    printf("--Enter K: ");
    scanf("%d", &k);
    
    printf("--Enter n-bit coverage: ");
    scanf("%d", &n);
    
    N = (unsigned long long int) pow(2, k) - 2;
    N1 = (unsigned long long int) pow(2, k);
    N2 = (unsigned long long int) pow(2, k) - 1;
    
    printf("=====MENU=====\n");
    printf("Select a counter type:\n");
    printf("[1]: Regular Counter.\n[2]: Gray Counter.\n[3]: Regular Counter with step.\n[4]: Add after N cycles (N-1).\n[5]: 1,1,....,N-1 sequence counter.\n[6]: LFSR counter.\n[7]: NFSR counter.\n\n\n");
    
    do {
        printf("--Give option:\t");
        scanf("%d", &ans);
     } while (!(ans == 1 || ans == 2 || ans == 3 || ans == 4 || ans == 5 || ans == 6 || ans == 7));
    
    printf("\n\n\n");
    printf("***********************ACCUMULATOR STARTED****************************\n");
    printf("----------------------------------------------------------------------\n");
    
    
    
    
    
    
    /*Calculate M sequence as Accumulator Cycles number.*/
    if (ans == 5 || ans == 7) {
        M = (unsigned long long int)N1 * N1;
    } else if (ans == 6 || ans == 2) {
        M = (unsigned long long int)N1 * N2;
    } else {
        M = (unsigned long long int)N1 * N;
    }
    /*Calculating tuples.*/
    tuples = (M-n)+1;
    
    arr = (char **) malloc(sizeof(char *) * tuples);
    reg1 = (char *) malloc(sizeof(char) * k);
    mSeq = (char *) malloc(sizeof(char) * M);
    
    if (arr == NULL || /*cnt == NULL ||*/ reg1 == NULL || mSeq == NULL) {
        fprintf(stderr, "There was a problem on memory allocation.\n");
        exit(10);
    }
    
    
    /*
     * Turn the accumulator to zero.
     * 
    */
    start = clock();    //start time.
    if (ans == 5 || ans == 7) {
    	start_counter = 1;
        stop = (unsigned long long int) N1;
        up_limit = (unsigned long long int) N1;
    } else if (ans == 6 || ans == 2) {
    	start_counter = 1;
        stop = (unsigned long long int) N2;
        up_limit = (unsigned long long int) N2;
    } else {
    	start_counter = 1;
        stop = (unsigned long long int) N;
        up_limit = (unsigned long long int) N;
    }
    
    
    
    
    
    
    /*Initialize Register Value.*/
    reg = start_reg;
    do {
        //cnt_idx = start_counter;
        cnt_c = 0;
        cnt = start_counter;
        non_linear = 1;
        
        do {
            idx++;
            
            if (ans == 6) {
            	reg = cnt;
           	} else {
           		reg = ADD(reg, cnt);
           	}
            
            /*printf("Round: %llu, cnt[%llu] = ", idx, cnt_c);
            printBinary(cnt, k, stdout);
            printf(", Reg = ");
            printBinary(reg, k, stdout);
            printf("\n");*/
            
            if (M > idx-1) {
                binaryToStr(reg, k, reg1);
                
                mSeq[mSeq_idx++] = reg1[k-1];
            }
            
            cnt_c/*cnt_idx*/ = (++cnt_c/*cnt_idx*/) % up_limit;
            /*Go to next state - At each counter type.*/
            if (ans == 7 && non_linear == 1 && cnt == (pow(2, k)-1)) {
           		cnt == pow(2, k)-1;
           		non_linear = 0;
           	} else if (ans == 5 && non_linear == 1 && cnt == 1) {
           		cnt = 1;
           		non_linear = 0;
           	}else {
            	cnt = next_state(ans, cnt, k);
           	}
        } while (!(cnt_c/*ctn_idx*/ == stop%up_limit));
        
        if (ans == 3) {
            stop = (++stop) % up_limit;
            start_counter = (++start_counter) % up_limit;
        } else if (ans == 4) {
            reg = ADD(reg, up_limit+1);
        }
    } while(/*(reg % (unsigned long long int)pow(2, k)) != 0*/idx != M);
    
    
    
    
    
    end = clock();      //stop time.
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;      //calculate time duration.
    
    //printf("**************************%d-TUPLES******************************\n", tuples);
    
    if (M <= idx) {
        for(i=0; i<tuples && reached == 0; i++) {
            /*
             * Check four multipled patterns.
             * If current parrern is already counted, throw it away.
            */
            there_is = 0;
            for (ii=0; ii<arr_idx; ii++) {
                if (strncmp(arr[ii], &mSeq[i], n * sizeof(char)) == 0) {
                    there_is = 1;
                    break;
                }
            }
            
            /*
             * If current pattern isn't counted or is the 1st pattern
             *   then we keep it at "arr" array.
            */
            if (there_is == 0 || arr_idx == 0) {
                arr[arr_idx++] = &mSeq[i];
                
                if (test_b) fprintf(test, "\n%llu:", test_cycle++);
                if (work_b) fprintf(workb, "force -freeze %s ", signal);
                for(j=0; j<n; j++) {
                    if (test_b) fprintf(test, "%c", mSeq[i+j]);
                    if (work_b) fprintf(workb, "%c", mSeq[i+j]);
                }
                if (work_b) fprintf(workb, " 0\nrun\n");
            }
            
            tmp_per = (double) arr_idx/(pow(2, n))* (double) 100;
            if (tmp_per > min_cycl_per) {
                goal++;
                min_cycl_per = tmp_per;
            } else if (tmp_per == min_cycl_per && tmp_per != 100) {
                goal++;
            }
            
            if (tmp_per == 100) {
                reached = 1;
            }
        }
        
        printf("****************************STATISTICS********************************\n");
        printf("***\tNumber of cycles           :%llu\n", idx);
        printf("***\tNumber of sequence patterns:%llu\n", arr_idx);
        if (((double) arr_idx/(pow(2, n))*100) >= (double) 100) {
            printf("***\t100%% Reached at              :%llu cycles\n", --goal);
        } else {
            printf("***\t%.3f%% Reached at            :%llu cycles\n", tmp_per, --goal);
        }
        printf("***\t%d-coverage                   :%f%%\n", n, tmp_per);
        
        printf("***\tM sequence (%llu-bits)       :{}\n", M);
        printf("***\tTime duration msec(s)        :%f\n", cpu_time_used*(double) 1000);
    } else {
        fprintf(stderr, "Message: You must Provide M sequence less or equal than cycles of Accumulator.\n");
    }
    
    
    
    
    printf("**********************************************************************\n");
    
    if (test_b) fclose(test);
    if (work_b) fclose(workb);
    
    /*Free memory.*/
    /*free(cnt);*/
    free(reg1);
    free(mSeq);
    free(arr);
    return 0;
}







/* Define next state for each module counter. */
unsigned long long int next_state(const int ans, const unsigned long long int cnt, int k) {
	unsigned long long int result;
	switch(ans) {
		case 1:
	       //cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N);
	       result = counter_next_state(k, cnt);
	       break;
	    case 2:
	      	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N);
	     	result =  gray_code_next_state(k, cnt);
	      	break;
	    case 3:
	      	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N);
	      	result = counter_next_state(k, cnt);
	      	break;
	    case 4:
	      	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N);
	      	result = counter_next_state(k, cnt);
	      	break;
	    case 5:
	      	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
	      	result = counter1_next_state(k, cnt);
	      	break;
	    case 6:
	      	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N2);
	      	result = lfsr_counter_next_state(k, cnt);
	     	break;
	    case 7:
		  	//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
		  	result = nfsr_counter_next_state(k, cnt);
		  	break;
		default:
			result = 0;
			break;
	}
	return result;
}

void printLogo(void) {
    
    printf("\n\n\n");
    printf("    **     **    **    **  **   **    **  **  **  **         **    ******    *****   ****\n");
    printf("   *  *   **    **     **  **   ** ** **  **  **  **        *  *     **     **   **  ** **\n");
    printf("  ****** **    **      **  **   **    **  **  **  **       ******    **     **   **  **** \n");
    printf(" *      * **    **     **  **   **    **  **  **  **      *      *   **     **   **  **  ** \n");
    printf("*        * **    **    ******   **    **  ******  ****** *        *  **      ****    **   ** \n");
    printf("==============================================================================================\n");
}

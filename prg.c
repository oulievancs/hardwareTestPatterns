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
#include "nfsr.h"

/*
 * Define Functions.
*/
void printLogo(void);
unsigned long long int next_state(const int ans, const unsigned long long int cnt, const int k);

/*
 * Start main program.
*/
int main(int argc, char **argv){
    int k, n, ans, reached, non_linear;
    int there_is, test_b=0, work_b=0, debug_mode=0, regs=1, halt, halt_d;
    unsigned long long int /***/cnt, cnt_c, /*cnt_idx=0,*/ idx=0, mSeq1_idx=0, *arr1_idx=NULL, tuples, reg=1, M, *goal=NULL, test_cycle=1, reg_idx;
    unsigned long long int start_counter, start_reg = 0, stop, up_limit, N, N1, N2;
    unsigned long long int i, j, ii, iii, i_reg, i_reg_c, mSeqs1_idx=0;
    char *reg1=NULL, *reg2=NULL, *mSeqs=NULL, **arrs=NULL, cir_name[50], signal[50], *mSeqs1=NULL;
    clock_t start, end;
    double cpu_time_used, min_cycl_per, *tmp_per=NULL;
    
    /*For output file Stream.*/
    FILE *test, *workb;
    
    printLogo();
	
	/********************************USER INPUT*********************************************/
	printf("--Enter K: ");
    scanf("%d", &k);
    
    printf("--Enter n-bit coverage: ");
    scanf("%d", &n);
	/***************************************************************************************/
	
	/******************************Prepare Operations****************************************/
	N = (unsigned long long int) pow(2, k) - 2;
    N1 = (unsigned long long int) pow(2, k);
    N2 = (unsigned long long int) pow(2, k) - 1;
	
	
    
    printf("=====MENU=====\n");
    printf("Select a counter type:\n");
    printf("[1]: Regular Counter.\n[2]: Gray Counter.\n[3]: Regular Counter with step.\n[4]: Add after N cycles (N-1).\n[5]: 1,1,....,N-1 sequence counter.\n[6]: LFSR counter.\n[7]: NFSR counter.\n[8]: NFSR non-linear.\n[9]: NFSR counter and n shift registers.\n\n");
    
    do {
        printf("--Give option:\t");
        scanf("%d", &ans);
    } while (!(ans == 1 || ans == 2 || ans == 3 || ans == 4 || ans == 5 || ans == 6 || ans == 7 || ans == 8 || ans == 9));
	
	
	/*Calculate M sequence as Accumulator Cycles number.*/
    if (ans == 5 || ans == 7 || ans == 9) {
        M = (unsigned long long int)N1 * N1;
    } else if (ans == 2 || ans == 6 || ans == 8) {
        M = (unsigned long long int)N1 * N2;
    } else {
        M = (unsigned long long int)N1 * N;
    }
    
    /*Calculating tuples.*/
    tuples = (unsigned long long int) ((M - n) + 1);
    
    if (ans == 9) {
        do {
            printf("--Give the number of registered bit yout want to check:\t");
            scanf("%d", &regs);
        } while (! (regs <= k));
        halt = ((int) (n/regs));
        halt_d = ((int) (n % regs));
        
        mSeqs1 =    (char *) malloc((unsigned long long int) sizeof(char) * tuples * n);
        reg2 =      (char *) malloc((unsigned long long int) sizeof(char) * n);
        if (mSeqs1 == NULL) {
            fprintf(stderr, "There was a problem on memory allocation. (-1)\n");
            exit(9);
        }
        if (reg2 == NULL) {
            fprintf(stderr, "There was a problem on memory allocation. (-2)\n");
            exit(8);
        }
    } else {
        arrs =  (char **) malloc((unsigned long long int) sizeof(char *) * regs * tuples);
        if (arrs == NULL) {
            fprintf(stderr, "There was a problem on memory allocation. (4)\n");
            exit(13);
        }
    }
    
	
	if (n <= 0 || k <= 0) {
		fprintf(stderr, "You must provide k and n as positive integers.\n");
		exit(12);
	}
	
	if (M <= n && n > 0) {
		fprintf(stderr, "You must provide a bigger k value.\n");
		exit(11);
	}
	
	reg1 =      (char *) malloc((unsigned long long int) sizeof(char) * k);
    mSeqs =     (char *) malloc((unsigned long long int) sizeof(char) * regs * M);
    goal =      (unsigned long long int *) malloc((int) sizeof(unsigned long long int) * regs);
    tmp_per =   (double *) malloc((int) sizeof(double) * regs);
    arr1_idx =  (unsigned long long int *) malloc((int) sizeof(unsigned long long int) * regs);
    
    
    /*
     * Check memory allocation.
    */
    if (arr1_idx == NULL) {
		fprintf(stderr, "There was a problem on memory allocation. (1)\n");
        exit(10);
	}
	if (reg1 == NULL) {
		fprintf(stderr, "There was a problem on memory allocation. (2)\n");
        exit(11);
	}
	if (mSeqs == NULL) {
		fprintf(stderr, "There was a problem on memory allocation. (3)\n");
        exit(12);
	}
    if (goal == NULL) {
		fprintf(stderr, "There was a problem on memory allocation. (4)\n");
        exit(13);
	}
    if (tmp_per == NULL) {
		fprintf(stderr, "There was a problem on memory allocation. (5)\n");
        exit(14);
	}
    
    printf("\n\n\n");
    printf("***********************ACCUMULATOR STARTED****************************\n");
    printf("----------------------------------------------------------------------\n");
	
	
    /***************************************************************************************/
    /********************************PROCCESS MENU******************************************/
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
    } else if (argc == 2) {
        if (strcmp(argv[1], "-debug") == 0) {
                debug_mode = 1;
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
    
    
    
    
    
    /*
     * Turn the accumulator to zero.
     * 
    */
    start = clock();    //start time.
    if (ans == 5 || ans == 7 || ans == 9) {
    	start_counter = 1;
        stop = (unsigned long long int) N1;
        up_limit = (unsigned long long int) N1;
    } else if (ans == 6 || ans == 2 || ans == 8) {
    	start_counter = 1;
        stop = (unsigned long long int) N2;
        up_limit = (unsigned long long int) N2;
    } else {
    	start_counter = 1;
        stop = (unsigned long long int) N;
        up_limit = (unsigned long long int) N;
    }
    
    
    
    
    
    /*
     * Initialize Register Value.
     */
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
            
            if (debug_mode) {
                printf("Round: %llu, cnt[%llu] = ", idx, cnt_c);
                printBinary(cnt, k, stdout);
                printf(", Reg = ");
                printBinary(reg, k, stdout);
                printf("\n");
            }
            
            binaryToStr(reg, k, reg1);
            for (i_reg=0; i_reg<regs; i_reg++) {
                if (M > idx-1) {
                    mSeqs[i_reg * M + mSeq1_idx] = reg1[k-1-i_reg];
                }
            }
            mSeq1_idx++;
            
            cnt_c/*cnt_idx*/ = (++cnt_c/*cnt_idx*/) % up_limit;
            /*Go to next state - At each counter type.*/
            if ((ans == 9 || ans == 7) && non_linear == 1 && cnt == (pow(2, k)-1)) {
           		cnt == pow(2, k)-1;
           		non_linear = 0;
           	} else if (ans == 5 && non_linear == 1 && cnt == 1) {
           		cnt = 1;
           		non_linear = 0;
           	}else {
            	cnt = next_state(ans, cnt, k);
           	}
        } while (!(cnt_c/*ctn_idx*/ == stop%up_limit || idx == M));
        
        if (ans == 3) {
            stop = (++stop) % up_limit;
            start_counter = (++start_counter) % up_limit;
        } else if (ans == 4) {
            reg = ADD(reg, up_limit+1);
        }
    } while(/*(reg % (unsigned long long int)pow(2, k)) != 0*/idx != M);
    
    
    
    
    end = clock();      //stop time.
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;      //calculate time duration.
    
    if (debug_mode) printf("\n\n**************************%d-TUPLES******************************\n", tuples);
    
    if (M <= idx) {
        if (ans != 9) {
            for(i_reg=0; i_reg<regs; i_reg++) {
                /*
                 * For debug mode.
                */
                if (debug_mode) printf("\n***M sequence for nr. %d Shift-Register: ", i_reg);
                
                arr1_idx[i_reg] = 0;
                reached = 0;
                min_cycl_per = (double) 0;
                goal[i_reg] = 0;
                tmp_per[i_reg] = 0;
                
                for(i=0; i<tuples && reached == 0; i++) {
                    /*
                     * Check four multipled patterns.
                     * If current parr1ern is already counted, throw it away.
                    */
                    there_is = 0;
                    for (ii=0; ii<arr1_idx[i_reg] && there_is == 0; ii++) {
                        if (strncmp(arrs[i_reg * M + ii], &mSeqs[i_reg * M + i], n * sizeof(char)) == 0) {
                            there_is = 1;
                        }
                    }
                    
                    
                    for (i_reg_c=0; i_reg_c<regs && i_reg_c < i_reg && there_is == 0; i_reg_c++) {
                        for (ii=0; ii<arr1_idx[i_reg_c] && there_is == 0; ii++) {
                            if (strncmp(arrs[i_reg_c * M + ii], &mSeqs[i_reg * M + i], n * sizeof(char)) == 0) {
                                there_is = 1;
                            }
                        }
                    }
                    
                    /*
                     * For debug mode.
                    */
                    if (debug_mode) printf("%c", mSeqs[i_reg * M + i]);
                    
                    /*
                     * If current pattern isn't counted or is the 1st pattern
                     *   then we keep it at "arrs[i_reg]" arr1ay.
                    */
                    if ((i_reg == 0 && (there_is == 0 || arr1_idx[i_reg] == 0)) || (i_reg != 0 && there_is == 0)) {
                        arrs[i_reg * M + arr1_idx[i_reg]] = &mSeqs[i_reg * M + i];
                        arr1_idx[i_reg]++;
                        
                        if (test_b) fprintf(test, "\n%llu:", test_cycle++);
                        if (work_b) fprintf(workb, "force -freeze %s ", signal);
                        for(j=0; j<n; j++) {
                            if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
                            if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
                        }
                        
                        if (work_b) fprintf(workb, " 0\nrun\n");
                        
                        tmp_per[i_reg] = (double) arr1_idx[i_reg]/(pow(2, n))* (double) 100;
                        
                        if (tmp_per[i_reg] == (double) 100) {
                            reached = 1;
                        }
                    }
                    
                    if (tmp_per[i_reg] > min_cycl_per) {
                        goal[i_reg]++;
                        min_cycl_per = tmp_per[i_reg];
                    }
                    else if (tmp_per[i_reg] == min_cycl_per && tmp_per[i_reg] != (double) 100) {
                        goal[i_reg]++;
                    }
                }
                
                printf("\n***\tNumber of sequence patterns\t:%llu\n", arr1_idx[i_reg]);
                printf("***\t%d-coverage                   :%f%%\n", n, tmp_per[i_reg]);
                if (((double) arr1_idx[i_reg]/(pow(2, n))*100) >= (double) 100) {
                    printf("***\t100%% Reached at              :%llu cycles\n", --goal[i_reg]);
                } else {
                    printf("***\t%.3f%% Reached at            :%llu cycles\n", tmp_per[i_reg], --goal[i_reg]);
                }
            }
        } else {
            for(i_reg=0; i_reg<regs; i_reg++) {
                arr1_idx[i_reg] = 0;
                goal[i_reg] = 0;
                tmp_per[i_reg] = 0;
                /*
                 * For debug mode.
                */
                //if (debug_mode) printf("\n***M sequence for nr. %d Shift-Register: ", i_reg);
            }
            reached = 0;
            min_cycl_per = (double) 0;
            
            for(i=0; i<tuples; i++) {
                reg_idx = 0;
                
                for(i_reg=0; i_reg<regs; i_reg++) {
                    /*
                     * Check four multipled patterns.
                     * If current parr1ern is already counted, throw it away.
                    */
                    if (i_reg == 0) {
                        for(j=0; j<(halt+halt_d); j++) {
                            reg2[reg_idx++] = mSeqs[i_reg * M + (i+j)];
                        }
                    } else {
                        for(j=0; j<halt; j++) {
                            reg2[reg_idx++] = mSeqs[i_reg * M + (i+j)];
                        }
                    }
                }
                
                there_is = 0;
                for (ii=0; ii<mSeqs1_idx && there_is == 0; ii+=n) {
                    if (strncmp(&mSeqs1[ii], reg2, n * sizeof(char)) == 0) {
                        there_is = 1;
                    }
                }
                
                if (there_is == 0) {
                    if (test_b) fprintf(test, "\n%llu:", test_cycle++);
                    if (work_b) fprintf(workb, "force -freeze %s ", signal);
                    
                    for(i_reg=0; i_reg<regs; i_reg++) {
                        if (i_reg == 0) {
                            for(j=0; j<(halt+halt_d); j++) {
                                if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
                                if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
                                
                                mSeqs1[mSeqs1_idx++] = mSeqs[i_reg * M + (i+j)];
                            }
                            arr1_idx[i_reg]++;
                        } else {
                            for(j=0; j<halt; j++) {
                                if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
                                if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
                                
                                mSeqs1[mSeqs1_idx++] = mSeqs[i_reg * M + (i+j)];
                            }
                            arr1_idx[i_reg]++;
                        }
                        
                        tmp_per[i_reg] = (double) arr1_idx[i_reg]/(pow(2, n))* (double) 100;
                        
                        
                    }
                }
                
                for(i_reg=0; i_reg<regs; i_reg++) {
                    if (tmp_per[i_reg] == (double) 100) {
                        reached = 1;
                    }
                        
                    if (tmp_per[i_reg] > min_cycl_per) {
                        goal[i_reg]++;
                        min_cycl_per = tmp_per[i_reg];
                    }
                    else if (tmp_per[i_reg] == min_cycl_per && tmp_per[i_reg] != (double) 100) {
                        goal[i_reg]++;
                    }
                }
                if (work_b) fprintf(workb, " 0\nrun\n");
            }
            
            printf("\n***\tNumber of sequence patterns\t:%llu\n", arr1_idx[0]);
            printf("***\t%d-coverage                   :%f%%\n", n, min_cycl_per);
            if (((double) arr1_idx[0]/(pow(2, n))*100) >= (double) 100) {
                printf("***\t100%% Reached at              :%llu cycles\n", --goal[0]);
            } else {
                printf("***\t%.3f%% Reached at            :%llu cycles\n", tmp_per[0], --goal[0]);
            }
        }
        
        printf("\n\n****************************STATISTICS********************************\n");
        printf("***\tNumber of cycles           :%llu\n", idx);
        
        
        
        printf("***\tM sequence (%llu-bits)       :{}\n", M);
        printf("***\tTime duration msec(s)        :%f\n", cpu_time_used*(double) 1000);
        printf("**********************************************************************\n");
        
        if (regs > 1 && ans == 9) {
            printf("*****************************SIMILARITY*******************************\n");
            for(i_reg=0; i_reg<regs; i_reg++) {
                for(i_reg_c=0; i_reg_c<regs; i_reg_c++) {
                    
                    if (i_reg < i_reg_c) {
                        there_is = 0;
                        
                        for (ii=0; ii<N1; ii++) {
                            for (iii=0; iii<N1; iii++) {
                                if (strncmp(&mSeqs[i_reg * M + ii], &mSeqs[i_reg_c * M + iii], n * sizeof(char)) != 0) {
                                    there_is++;
                                }
                            }
                        }
                        printf("***\tRegister%d[%llu] and Register%d[%llu] has similar %d patterns.\n\n", i_reg, goal[i_reg], i_reg_c, goal[i_reg_c], there_is);
                    }
                }
            }
        }
    } else {
        fprintf(stderr, "Message: You must Provide M sequence less or equal than cycles of Accumulator.\n");
    }
    
    
    
    
    printf("**********************************************************************\n");
    
    if (test_b) fclose(test);
    if (work_b) fclose(workb);
    
    /*Free memory.*/
    /*free(cnt);*/
    if (mSeqs1 != NULL) free(mSeqs1);
    if (reg2 != NULL) free(reg2);
    if (goal != NULL) free(goal);
    if (tmp_per != NULL) free(tmp_per);
    if (arr1_idx != NULL) free(arr1_idx);
    if (reg1 != NULL) free(reg1);
    if (mSeqs != NULL) free(mSeqs);
    if (arrs != NULL) free(arrs);
    
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
        case 8:
            //cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
		  	result = nfsr_counter_next_state(k, cnt);
		  	break;
        case 9:
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

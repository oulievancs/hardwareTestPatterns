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
    int k=0, n=0, ans=0, reached, non_linear, high_bit=0, only_cov=0, only_pat=0;
    int there_is, test_b=0, work_b=0, debug_mode=0, no_compare=0, regs=1, halt, halt_d;
    unsigned long long int /***/cnt, cnt_c, /*cnt_idx=0,*/ idx=0, *mSeq1_idx=NULL, *arr1_idx=NULL, tuples, reg=1, M, M_tmp, *goal=NULL, test_cycle=1, reg_idx;
    unsigned long long int start_counter, start_reg = 0, stop, up_limit, N, N1, N2, N3;
    unsigned long long int i, j, ii, iii, i_reg, i_reg_c, mSeqs1_idx=0;
    char *reg1=NULL, *reg2=NULL, *mSeqs=NULL, **arrs=NULL, cir_name[50], signal[50], *mSeqs1=NULL;
    clock_t start, end;
    double cpu_time_used, min_cycl_per, *tmp_per=NULL;
    
    /*For output file Stream.*/
    FILE *test, *workb;
	
	/********************************USER INPUT*********************************************/
	/***************************************************************************************/
    /********************************PROCCESS MENU******************************************/
    if (argc > 1) {
        for (i=1; i<argc;) {
			if (strcmp(argv[i], "-o") == 0) {
				if (argv[i+1] != NULL) {
					test = fopen(argv[i+1], "w");
					
					if (test == NULL) {
						fprintf(stderr, "There was a problem on file opening.\n");
						exit(11);
					}
					test_b = 1;
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-f") == 0) {
				if (argv[i+1] != NULL) {
					workb = fopen(argv[i+1], "w");
					
					if (workb == NULL) {
						fprintf(stderr, "There was a problem on file opening.\n");
						exit(14);
					}
					
					work_b=1;
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-z") == 0) {
				if (argv[i+1] != NULL) {
					reg = (int) atoi(argv[i+1]);
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-debug") == 0) {
					debug_mode = 1;
					i ++;
			} else if (strcmp(argv[i], "-nocompare") == 0) {
				no_compare = 1;
				i ++;
			} else if (strcmp(argv[i], "-k") == 0) {
				if (argv[i+1] != NULL) {
					k = (int) atoi(argv[i+1]);
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-n") == 0) {
				if (argv[i+1] != NULL) {
					n = (int) atoi(argv[i+1]);
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-m") == 0) {
				if (argv[i+1] != NULL) {
					ans = (int) atoi(argv[i+1]);
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp(argv[i], "-bit") == 0) {
				if (argv[i+1] != NULL) {
					high_bit = (int) atoi(argv[i+1]);
					i += 2;
				} else {
					exit(1);
				}
			} else if (strcmp (argv[i], "-onlycoverage") == 0) {
				only_cov = 1;
				i++;
			} else if (strcmp (argv[i], "-onlypatterns") == 0) {
				only_pat = 1;
				i++;
			}
		}
    } else {
        fprintf(stderr, "./prg <-o> <fsim output> <-f> <Do script for Workbench> <-r> <start stage register>\n");
    }
    
    if (!(only_cov || only_pat)) {
		printLogo();
		printf("\n\n\n");
	}
    
    if (work_b) {
        printf("--Give Signal name: ");
        scanf("%s", signal);
    }
    /***************************************************************************************/
	if (k==0) {
		printf("--Enter K: ");
		scanf("%d", &k);
	}
    
    if (n == 0) {
		printf("--Enter n-bit coverage: ");
		scanf("%d", &n);
	}
	/***************************************************************************************/
	
	/******************************Prepare Operations****************************************/
    N = (unsigned long long int) pow(2, k) - 2;
    N1 = (unsigned long long int) pow(2, k);
    N2 = (unsigned long long int) pow(2, k) - 1;
    N3 = (unsigned long long int) pow(2, k) - 3;
	
	
    while (!(ans == 1 || ans == 2 || ans == 3 || ans == 4 || ans == 5 || ans == 6 || ans == 7 || ans == 8 || ans == 9 || ans == 10 || ans == 11 || ans == 12 || ans == 13 || ans == 14 || ans == 15 || ans == 16 || ans == 17 || ans == 18)) {
		printf("=====MENU=====\n");
		printf("Select a counter type:\n");
		printf("[1]: Regular Counter + ACC.\n[2]: Gray Counter + ACC.\n[3]: Regular Counter with step + ACC.\n[4]: Add after N cycles (N-1) counter + ACC.\n[5]: 1,1,....,N-1 sequence counter + ACC.\n[6]: LFSR - internal counter.\n[7]: NFSR + ACC - internal counter.\n[8]: NFSR + ACC non-linear.\n[9]: NFSR + ACC counter and n shift registers.\n[10]: NFSR + ACC - internal non-linear extra xor.\n[11]: LFSR - external counter.\n[12]: NFSR + ACC - external counter.\n[13]: NFSR + ACC - external non-linear and extra xor.\n[14]: NFSR + ACC - internal xor 2 high bit.\n[15]: NFSR + ACC - external xor 2 high bit.\n[16]: LFSR - external squares (Giving a dimension).\n[17]: NFSR + ACC - external (Giving a dimension).\n[18]: NFSR + ACC squares - complement adder.\n\n");
		
        printf("--Give option:\t");
        scanf("%d", &ans);
    }
	
	if ((ans == 16 || ans == 17 || ans == 18) && high_bit != 0 && n > k) {
		fprintf(stderr, "You can not provide n grater that k.\n");
	}
	
	if ((ans == 16 || ans == 17) && high_bit != 0 && high_bit > k-n) {
		fprintf(stderr, "You must provide less high bit.\n");
		exit(20);
	}
	
	/*Calculate M sequence as Accumulator Cycles number.*/
    if (ans == 5 || ans == 7 || ans == 9 || ans == 10 || ans == 12 || ans == 13 || ans == 14 || ans == 15) {
        	M = (unsigned long long int) (N1 * N1 + 2*n);
    } else if (ans == 2 || ans == 8) {
        	M = (unsigned long long int) (N1 * N2 + 2*n);
    } else if (ans == 6 || ans == 11) {
		M = (unsigned long long int) (N2 + 2*n);
    } else if (ans == 16) {
		M = (unsigned long long int) (N2 * n + k * n);
    } else if (ans == 17) {
		M = (unsigned long long int) (N1 * N1 * n + k * n);
    } else if (ans == 18) {
		M = (unsigned long long int) (N1 * N3 * n);
    } else {
        	M = (unsigned long long int)(N1 * N + n);
    }
    
    /*Calculating tuples.*/
	if (ans == 16 || ans == 17/* || ans == 18*/) {
		tuples = (unsigned long long int) ((M - pow(2, n)) + 1);
	} else {
		tuples = (unsigned long long int) ((M - n) + 1);
	}
    
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
    mSeqs =     (char *) calloc(regs * M, (unsigned long long int) sizeof(char));
    goal =      (unsigned long long int *) malloc((int) sizeof(unsigned long long int) * regs);
    tmp_per =   (double *) malloc((int) sizeof(double) * regs);
    arr1_idx =  (unsigned long long int *) malloc((int) sizeof(unsigned long long int) * regs);
    mSeq1_idx = (unsigned long long int *) malloc((int) sizeof(unsigned long long int) * regs);
    
    
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
    
    if (!(only_cov || only_pat)) {
		printf("\n\n\n");
		printf("***********************ACCUMULATOR STARTED****************************\n");
		printf("----------------------------------------------------------------------\n");
	}
	
	
    
    /***************************************************************************************/
    
    
    
    
    
    /*
     * Turn the accumulator to zero.
     * 
    */
    start = clock();    //start time.
    if (ans == 5 || ans == 7 || ans == 9 || ans == 10 || ans == 12 || ans == 13 || ans == 14 || ans == 15 || ans == 17) {
    	start_counter = 1;
        stop = (unsigned long long int) N1;
        up_limit = (unsigned long long int) N1;
    } else if (ans == 6 || ans == 2 || ans == 8 || ans == 11 || ans == 16) {
    	start_counter = 1;
        stop = (unsigned long long int) N2;
        up_limit = (unsigned long long int) N2;
    } else if (ans == 18) {
	start_counter = pow(2, k-1) - 1;
	stop = (unsigned long long int) N3;
	up_limit = (unsigned long long int) N3;
    } else {
    	start_counter = 1;
        stop = (unsigned long long int) N;
        up_limit = (unsigned long long int) N;
    }
    
    
    for (i_reg=0; i_reg<regs; i_reg++) {
		mSeq1_idx[i_reg] = 0;
	}
    
    
    /*
     * Initialize Register Value.
     */
    reg = start_reg;
	
	if (ans != 16 && ans != 17 && ans != 18) {
		binaryToStr(start_reg, k, reg1);
		if (ans != 9) {
			for (i_reg=0; i_reg<regs; i_reg++) {
				for (i=0; i<n; i++) {
					mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[0];
					mSeq1_idx[i_reg]++;
				}
			}
		} else {
			for (i_reg=0; i_reg<regs; i_reg++) {
				if (i_reg == 0) {
					for (i=0; i<halt+halt_d; i++) {
						mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[0];
						mSeq1_idx[i_reg]++;
					}
				} else {
					for (i=0; i<halt; i++) {
						mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[0];
						mSeq1_idx[i_reg]++;
					}
				}
			}
		}
		idx += n;
	}
	
	
    do {
        //cnt_idx = start_counter;
        cnt_c = 0;
        cnt = start_counter;
        non_linear = 1;
        
        do {
            idx++;
            
            if (ans == 6 || ans == 11 || ans == 16) {
            	reg = cnt;
            } else if (ans == 18) {
		reg = ADD(reg, cnt);
		if (reg >= pow(2, k)) {
			reg = (reg % (unsigned long long int) pow(2, k)) + 1;
		}
	    }  else {
           	reg = ADD(reg, cnt);
            }
            
            if (debug_mode) {
                if (ans != 16 && ans != 17 && ans != 18) printf("Round: %llu, cnt[%llu] = ", idx-n, cnt_c);
		else printf("Round: %llu, cnt[%llu] = ", idx, cnt_c);
		
                printBinary(cnt, k, stdout);
                printf(", Reg = ");
                printBinary(reg, k, stdout);
                if (ans != 16 && ans != 17 && ans != 18) printf(" -> Out Bit: ");
            }
            
            binaryToStr(reg, k, reg1);
            for (i_reg=0; i_reg<regs; i_reg++) {
                //if (M > idx-1) {
				if (ans == 6 || ans == 11) {
					mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[i_reg];
					mSeq1_idx[i_reg]++;
				} else if (ans == 10 || ans == 13) {
					mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[k-1-i_reg-((~((reg>>(1)&0x1) ^ reg&0x1)) & 0x1)];
					if (debug_mode) printf("%c", mSeqs[i_reg * M + mSeq1_idx[i_reg]]);
					mSeq1_idx[i_reg]++;
				} else if (ans == 14 || ans == 15) {
					if (((((reg >> (k-1)) & 0x1) ^ ((reg >> (k-2)) & 0x1)) & 0x1)) {
							mSeqs[i_reg * M + mSeq1_idx[i_reg]] = '1';
					} else {
							mSeqs[i_reg * M + mSeq1_idx[i_reg]] = '0';
					}
					mSeq1_idx[i_reg]++;
				} else if (ans == 16 || ans == 17 || ans == 18) {
					for (ii=0; ii<n; ii++) {
						mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[k-1-high_bit-ii];
						mSeq1_idx[i_reg] ++;
					}
				} else {
					mSeqs[i_reg * M + mSeq1_idx[i_reg]] = reg1[k-1-i_reg-high_bit];
					mSeq1_idx[i_reg]++;
				}
		    
                //}
            }
	    if (debug_mode) printf("\n");
            
            
            cnt_c/*cnt_idx*/ = (++cnt_c/*cnt_idx*/) % up_limit;
            /*Go to next state - At each counter type.*/
	    if (ans == 16 || ans == 17 || ans == 18) {
		M_tmp = M/n;
	    } else {
	    	M_tmp = M;
	    }
            if ((ans == 9 || ans == 7 || ans == 10 || ans == 12 || ans == 13 || ans == 14 || ans == 15 || ans == 17) && non_linear == 1 && cnt == 1) {
           		cnt = 1;
           		non_linear = 0;
            } else if (ans == 5 && non_linear == 1 && cnt == 1) {
           		cnt = 1;
           		non_linear = 0;
            } else {
            	cnt = next_state(ans, cnt, k);
            }
        } while (!(cnt_c/*ctn_idx*/ == stop%up_limit || idx == M_tmp));
        
        if (ans == 3) {
            stop = (++stop) % up_limit;
            start_counter = (++start_counter) % up_limit;
        } else if (ans == 4) {
            reg = ADD(reg, up_limit+1);
        }
    } while(!/*(reg % (unsigned long long int)pow(2, k)) != 0*/(idx == M_tmp));
    
    
    
    
    end = clock();      //stop time.
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;      //calculate time duration.
    
    if (debug_mode) printf("\n\n**************************%d-TUPLES******************************\n", tuples);
    if (!(only_cov || only_pat)) printf("\n****************************STATISTICS********************************\n");
    
    if (ans == 16 || ans == 17 || ans == 18) {
		/*
		 * For debug mode.
		*/
		if (debug_mode) printf("\n***\tM sequence for nr. %d Shift-Register: ", 0);
		
		arr1_idx[0] = 0;
		reached = 0;
		min_cycl_per = (double) 0;
		goal[0] = 0;
		tmp_per[0] = 0;
		
		for(i=0; i<tuples && (reached == 0 || debug_mode == 1);) {
			/*
			 * Check four multipled patterns.
			 * If current parr1ern is already counted, throw it away.
			*/
			there_is = 0;
			for (ii=0; ii<arr1_idx[0] && there_is == 0 && no_compare == 0; ii++) {
				if (strncmp(arrs[0 * M + ii], &mSeqs[0 * M + i], pow(n, 2) * sizeof(char)) == 0) {
					there_is = 1;
				}
			}
			
			/*
			 * For debug mode.
			*/
			if (debug_mode) {
				for(j=n; j-- > 0;) {
					printf("%c", mSeqs[0 * M + (i+j)]);
				}
			}
			
			/*
			 * If current pattern isn't counted or is the 1st pattern
			 *   then we keep it at "arrs[0]" array.
			*/
			
			if (no_compare == 0) {
				if (there_is == 0 || arr1_idx[0] == 0) {
					arrs[0 * M + arr1_idx[0]] = &mSeqs[0 * M + i];
					arr1_idx[0]++;
					
					tmp_per[0] = (double) arr1_idx[0]/(pow(2, n*n))* (double) 100;
					
					if (test_b) fprintf(test, "\n%llu:", test_cycle++);
					if (work_b) fprintf(workb, "force -freeze %s ", signal);
					for(j=pow(n, 2); j-- > 0;) {
						if (test_b) fprintf(test, "%c", mSeqs[0 * M + (i+j)]);
						if (work_b) fprintf(workb, "%c", mSeqs[0 * M + (i+j)]);
					}
					if (work_b) fprintf(workb, " 0\nrun\n");
				}
			} else {
			
				if (test_b) fprintf(test, "\n%llu:", test_cycle++);
				if (work_b) fprintf(workb, "force -freeze %s ", signal);
				for(j=pow(n, 2); j-- > 0;) {
					if (test_b) fprintf(test, "%c", mSeqs[0 * M + (i+j)]);
					if (work_b) fprintf(workb, "%c", mSeqs[0 * M + (i+j)]);
				}
				if (work_b) fprintf(workb, " 0\nrun\n");
			}
			
			if (no_compare == 0) {
				if (tmp_per[0] == (double) 100) {
					reached = 1;
				}
				
				if (tmp_per[0] > min_cycl_per) {
					goal[0]++;
					min_cycl_per = tmp_per[0];
				}
				else if (tmp_per[0] == min_cycl_per && tmp_per[0] != (double) 100) {
					//goal[0]++;
				}
			}
			
			i += n;
		}
		
		if (only_cov) {
			printf("%.6f", tmp_per[0]);
		} else if (only_pat) {
			printf("%llu", arr1_idx[0]);
		} else {
			printf("\n***\tNumber of sequence patterns              :%llu\n", arr1_idx[0]);
			printf("***\tTuples                                   :%llu\n", tuples);
			if (no_compare == 0) {
				printf("***\tn-coverage                               :%.6f%%\n", tmp_per[0]);
				if (((double) arr1_idx[0]/(pow(pow(2, n), 2))*100) >= (double) 100) {
					printf("***\t100%% Reached at                        :%llu cycles\n", goal[0]);
				} else {
					printf("***\tBiggest Reached at                       :%llu cycles\n", goal[0]);
				}
			}
		}
	}
	else if ((ans != 16 && ans != 17 && ans != 18) && ans != 9) {
		for(i_reg=0; i_reg<regs; i_reg++) {
			/*
			 * For debug mode.
			*/
			if (debug_mode) printf("\n***\tM sequence for nr. %d Shift-Register: ", i_reg);
			
			arr1_idx[i_reg] = 0;
			reached = 0;
			min_cycl_per = (double) 0;
			goal[i_reg] = 0;
			tmp_per[i_reg] = 0;
			
			for(i=0; i<tuples && (reached == 0 || debug_mode == 1); i++) {
				/*
				 * Check four multipled patterns.
				 * If current parr1ern is already counted, throw it away.
				*/
				there_is = 0;
				for (ii=0; ii<arr1_idx[i_reg] && there_is == 0 && no_compare == 0; ii++) {
					if (strncmp(arrs[i_reg * M + ii], &mSeqs[i_reg * M + i], n * sizeof(char)) == 0) {
						there_is = 1;
					}
				}
				
				
				for (i_reg_c=0; i_reg_c<regs && i_reg_c < i_reg && there_is == 0 && no_compare == 0; i_reg_c++) {
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
				 *   then we keep it at "arrs[i_reg]" array.
				*/
				
				if (no_compare == 0) {
					if (there_is == 0 || arr1_idx[i_reg] == 0) {
						arrs[i_reg * M + arr1_idx[i_reg]] = &mSeqs[i_reg * M + i];
						arr1_idx[i_reg]++;
						
						tmp_per[i_reg] = (double) arr1_idx[i_reg]/(pow(2, n))* (double) 100;
						
						if (test_b) fprintf(test, "\n%llu:", test_cycle++);
						if (work_b) fprintf(workb, "force -freeze %s ", signal);
						for(j=n; j-- > 0;) {
							if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
							if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
						}
						if (work_b) fprintf(workb, " 0\nrun\n");
					}
				} else {
				
					if (test_b) fprintf(test, "\n%llu:", test_cycle++);
					if (work_b) fprintf(workb, "force -freeze %s ", signal);
					for(j=n; j-- > 0;) {
						if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
						if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
					}
					if (work_b) fprintf(workb, " 0\nrun\n");
				}
				
				if (no_compare == 0) {
					if (tmp_per[i_reg] == (double) 100) {
						reached = 1;
					}
					
					if (tmp_per[i_reg] > min_cycl_per) {
						goal[i_reg]++;
						min_cycl_per = tmp_per[i_reg];
					}
					else if (tmp_per[i_reg] == min_cycl_per && tmp_per[i_reg] != (double) 100) {
						//goal[i_reg]++;
					}
				}
			}
			
			if (only_cov) {
				printf("%.3f", tmp_per[i_reg]);
			} else if (only_pat) {
				printf("%llu", arr1_idx[i_reg]);
			} else {
				printf("\n***\tNumber of sequence patterns              :%llu\n", arr1_idx[i_reg]);
				printf("***\tTuples                                   :%llu\n", tuples);
				if (no_compare == 0) {
					printf("***\tn-coverage                               :%f%%\n", tmp_per[i_reg]);
					if (((double) arr1_idx[i_reg]/(pow(2, n))*100) >= (double) 100) {
						printf("***\t100%% Reached at                        :%llu cycles\n", goal[i_reg]);
					} else {
						printf("***\tBiggest Reached at                       :%llu cycles\n", goal[i_reg]);
					}
				}
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
			if (debug_mode) {
				printf("\n***\tM sequence for nr. %d Shift-Register: ", i_reg);
				for (i=0; i<mSeq1_idx[i_reg]; i++) {
					printf("%c", mSeqs[i_reg * M + i]);
				}
			}
		}
		reached = 0;
		min_cycl_per = (double) 0;
		
		for(i=0; i<tuples; i++) {
			reg_idx = 0;
			
			for(i_reg=0; i_reg<regs && no_compare == 0; i_reg++) {
				/*
				 * Check four multipled patterns.
				 * If current parr1ern is already counted, throw it away.
				*/
			    if (i_reg == 0) {
					for(j=halt+halt_d; j-- > 0;) {
						reg2[reg_idx++] = mSeqs[i_reg * M + (i+j)];
					}
				} else {
					for(j=halt; j -- > 0;) {
						reg2[reg_idx++] = mSeqs[i_reg * M + (i+j)];
					}
				}
			}
			
			there_is = 0;
			for (ii=0; ii<mSeqs1_idx && there_is == 0 && no_compare == 0; ii+=n) {
				if (strncmp(&mSeqs1[ii], reg2, n * sizeof(char)) == 0) {
					there_is = 1;
				}
			}
			
			
			if ((no_compare == 0 && there_is == 0) || no_compare == 1) {
				if (test_b) fprintf(test, "\n%llu:", test_cycle++);
				if (work_b) fprintf(workb, "force -freeze %s ", signal);
			}
			
			for(i_reg=0; i_reg<regs; i_reg++) {
				if ((no_compare == 0 && there_is == 0 ) || no_compare == 1) {
					if (i_reg == 0) {
						for(j=halt+halt_d; j -- > 0;) {
							if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
							if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
							
							mSeqs1[mSeqs1_idx++] = mSeqs[i_reg * M + (i+j)];
						}
					} else {
						for(j=halt; j -- > 0;) {
							if (test_b) fprintf(test, "%c", mSeqs[i_reg * M + (i+j)]);
							if (work_b) fprintf(workb, "%c", mSeqs[i_reg * M + (i+j)]);
							
							mSeqs1[mSeqs1_idx++] = mSeqs[i_reg * M + (i+j)];
						}
					}
				}
				if (no_compare == 0 && there_is != 0) {
					arr1_idx[i_reg]++;
					tmp_per[i_reg] = (double) arr1_idx[i_reg]/(pow(2, n))* (double) 100;
				}
				
			}
			
			if (no_compare == 0) {
				for(i_reg=0; i_reg<regs && no_compare == 0; i_reg++) {
					if (tmp_per[i_reg] == (double) 100) {
						reached = 1;
					}
						
					if (tmp_per[i_reg] > min_cycl_per) {
						goal[i_reg]++;
						min_cycl_per = tmp_per[i_reg];
					}
					else if (tmp_per[i_reg] == min_cycl_per && tmp_per[i_reg] != (double) 100) {
						//goal[i_reg]++;
					}
				}
			}
			if ((no_compare == 0 && there_is == 0) || no_compare == 1) {
				if (work_b) fprintf(workb, " 0\nrun\n");
			}
		}
		
		if (only_cov) {
			printf("%.3f", tmp_per[i_reg]);
		} else if (only_pat) {
			printf("%llu", arr1_idx[0]);
		} else {
			printf("\n***\tNumber of sequence patterns              :%llu\n", arr1_idx[0]);
			printf("***\tTuples                                   :%llu\n", tuples);
			if (no_compare == 0) {
				printf("***\tn-coverage                               :(%d) %f%%\n", min_cycl_per);
				if (((double) arr1_idx[0]/(pow(2, n))*100) >= (double) 100) {
					printf("***\t100%% Reached at                         :%llu cycles\n", goal[0]);
				} else {
					printf("***\tBiggest Reached at                       :%llu cycles\n", goal[0]);
				}
			}
		}
	}
	
	if (!(only_cov || only_pat)) {
		printf("***\tNumber of cycles                         :%llu\n", idx-n);
		
		
		
		printf("***\tM sequence (%llu-bits)\n", M);
		printf("***\tTime duration msec(s)                    :%f\n", cpu_time_used*(double) 1000);
		printf("**********************************************************************\n");
	}
	
	if (regs > 1 && ans == 9) {
		if (!(only_cov || only_pat)) printf("*****************************SIMILARITY*******************************\n");
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
					if (!(only_cov || only_pat)) printf("***\tRegister%d[%llu] and Register%d[%llu] has similar %d patterns.\n\n", i_reg, goal[i_reg], i_reg_c, goal[i_reg_c], there_is);
				}
			}
		}
	}
    
    
    
    
    if (!(only_cov || only_pat)) printf("**********************************************************************\n");
    
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
	if (mSeq1_idx != NULL) free(mSeq1_idx);
    
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
	    case 10:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    case 11:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = lfsr_counter_next_state_external(k, cnt);
			break;
	    case 12:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    case 13:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    case 14:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state(k, cnt);
			break;
	    case 15:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    case 16:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = lfsr_counter_next_state_external(k, cnt);
			break;
	    case 17:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N1);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    case 18:
			//cnt = (unsigned long long int) malloc(sizeof(unsigned long long int) * N3);
			result = nfsr_counter_next_state_external(k, cnt);
			break;
	    default:
			result = 0;
			break;
	}
	return result;
}

void printLogo(void) {
    
    /*printf("\n\n\n");
    printf("    **     **    **    **  **   **    **  **  **  **         **    ******    *****   ****\n");
    printf("   *  *   **    **     **  **   ** ** **  **  **  **        *  *     **     **   **  ** **\n");
    printf("  ****** **    **      **  **   **    **  **  **  **       ******    **     **   **  **** \n");
    printf(" *      * **    **     **  **   **    **  **  **  **      *      *   **     **   **  **  ** \n");
    printf("*        * **    **    ******   **    **  ******  ****** *        *  **      ****    **   ** \n");
    printf("==============================================================================================\n");*/
	printf("        ************************************************\n");
	printf("        *                                              *\n");
	printf("        *     Welcome to ACCUMULATOR(version 2.1)      *\n");
	printf("        *                                              *\n");
	printf("        *  Student Evangelos Oulis (cs151051@uniwa.gr) *\n");
	printf("        *           Web: http://ice.uniwa.gr           *\n");
	printf("        *   University of West Attica, Athens, Greece  *\n");
	printf("        ************************************************\n");
}

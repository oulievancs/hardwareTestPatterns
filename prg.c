#include <stdio.h>
#include "nor.h"
#include "and.h"

int main(int argc, char **argv){
    int k, cav, prev_reg, idx=0, cnt_idx, arr_idx=0;
    unsigned int reg;
    const unsigned int cnt[] = {1, 2, 3, 4, 5, 6};
    unsigned int arr[100];
    
    printf("Enter K = ");
    scanf("%d", &k);
    
    printf("Enter n-bit cavarage = ");
    scanf("%d", &cav);
    
    reg++;
    do {
        cnt_idx = 0;
        do {
            idx += 1;
            reg = and(reg, cnt[cnt_idx], 3);
            
            arr[arr_idx++] = reg >> k;
                
            printf("cnt = %d, Reg = %d\n", cnt[cnt_idx], reg);
            cnt_idx++;
        } while (cnt[cnt_idx] <= 6);
    } while(nor(reg, 1, 3) == 6);
    
    printf("Number of cycles = %d.\n", idx);
    
    return 0;
}

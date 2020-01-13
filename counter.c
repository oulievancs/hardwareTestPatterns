/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
void counter(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N;
    N = (unsigned long long int) pow(2,n) - 1;
    
    for (i=1; i<N; i++) {
        counter[i-1] = (unsigned long long int) i;
    }
}

void counter1(unsigned long long int n, unsigned long long int *counter) {
    unsigned long long int i, N;
    N = (unsigned long long int) pow(2,n);
    
    counter[0] = 1;
    for (i=1; i<N; i++) {
        counter[i] = (unsigned long long int) i;
    }
}

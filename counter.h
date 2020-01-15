/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#ifdef COUNTER_H_
#define COUNTER_H_

void counter(unsigned long long int n, unsigned long long int *counter);
void counter1(unsigned long long int n, unsigned long long int *counter);
void lfsr_counter(unsigned long long int n, unsigned long long int *counter);
unsigned long long int leftRotate(unsigned long long int n, unsigned long long int d, unsigned long long int BITS);

#endif // COUNTER_H_

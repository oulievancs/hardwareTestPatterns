/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/
#ifdef COUNTER_H_
#define COUNTER_H_

void counter(unsigned long long int n, unsigned long long int *counter);
unsigned long long int counter_next_state(unsigned long long int n, unsigned long long int prev_state);
void counter1(unsigned long long int n, unsigned long long int *counter);
unsigned long long int counter1_next_state(unsigned long long int n, unsigned long long int prev_state)

#endif // COUNTER_H_

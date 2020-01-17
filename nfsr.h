/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
*/

#ifdef LFSR_H_
#define LFSR_H_

void nfsr_counter(const unsigned long long int n, unsigned long long int *counter);
unsigned long long int nfsr_counter_next_state(const unsigned long long int n, const unsigned long long int prev_state);

#endif //LFSR_H_

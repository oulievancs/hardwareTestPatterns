/*
 * Authors: Oulis Evangelos & Kalliopi Voudouri
 *          711151051         46577
 * LFSR counter applied using Internal & External Feedback.
*/

#ifdef LFSR_H_
#define LFSR_H_

void lfsr_counter(unsigned long long int n, unsigned long long int *counter);
unsigned long long int lfsr_counter_next_state(const unsigned long long int n, const unsigned long long int prev_state);
unsigned long long int lfsr_counter_next_state_external(const unsigned long long int n, const unsigned long long int prev_state);

#endif //LFSR_H_

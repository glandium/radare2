/* radare - LGPL - Copyright 2009 pancake<nopcode.org> */

#include "r_util.h"

// Subtract the 'struct timeval' values begin from end, storing result in RESULT
// Return 1 if the difference is negative, otherwise 0.
static int timeval_subtract(struct timeval *result, struct timeval *end, struct timeval *begin)
{
	// Perform the carry for the later subtraction by updating Y
	if (end->tv_usec < begin->tv_usec) {
		int nsec = (begin->tv_usec - end->tv_usec) / 1000000 + 1;
		begin->tv_usec -= 1000000 * nsec;
		begin->tv_sec += nsec;
	}
	if (end->tv_usec - begin->tv_usec > 1000000) {
		int nsec = (end->tv_usec - begin->tv_usec) / 1000000;
		begin->tv_usec += 1000000 * nsec;
		begin->tv_sec -= nsec;
	}

	// Compute the time remaining to wait. 'tv_usec' is certainly positive.
	result->tv_sec = end->tv_sec - begin->tv_sec;
	result->tv_usec = end->tv_usec - begin->tv_usec;

	// Return 1 if result is negative
	return end->tv_sec < begin->tv_sec;
}

void r_prof_start(struct r_prof_t *p)
{
	struct timeval *begin = &p->begin;
	p->result = 0.0;
	gettimeofday(begin, NULL);
}

double r_prof_end(struct r_prof_t *p)
{
	struct timeval *begin = &p->begin;
	struct timeval end;
	struct timeval diff;
	int    sign;

	gettimeofday(&end, NULL);
	sign = timeval_subtract(&diff, begin, &end);
	p->result = R_ABS(((double)(diff.tv_sec) + ((double)diff.tv_usec / 1000000.)));
	return R_ABS(sign);
}

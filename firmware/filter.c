#include <stdio.h>
#include <stdlib.h>
#include "filter.h"

/*
 * http://en.wikipedia.org/wiki/Low-pass_filter#Simple_infinite_impulse_response_filter
 * α := dt / (RC + dt)
 * y[i] := α * x[i] + (1-α) * y[i-1]
 * y[i] := y[i-1] + α * (x[i] - y[i-1])
 */

void    low_pass_filter(uint8_t a, double *lp, double u)
{
    *lp = *lp + (( u - *lp ) / a);
}


/*
 * http://en.wikipedia.org/wiki/High-pass_filter#Algorithmic_implementation
 * α := RC / (RC + dt)
 * y[i] := α * y[i-1] + α * (x[i] - x[i-1])
 */

void    high_pass_filter(uint8_t a, double *hp, double u, double *u_mem)
{
    low_pass_filter(a, u_mem, u);
    *hp = u - *u_mem;
}

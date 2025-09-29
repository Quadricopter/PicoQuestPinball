#ifndef __FILTER_H__
#define __FILTER_H__

#include <stdint.h>

void    low_pass_filter(uint8_t a, double *lp, double u);
void    high_pass_filter(uint8_t a, double *hp, double u, double *u_mem);


#endif /*__FILTER_H__*/

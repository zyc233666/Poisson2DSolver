#include<iostream>
#include "head.h"

// f1r: 1 D, righ f of 1 order
double f1r1(double x, double xl, double xr)
{
	return (double)(x - xl) / (xr - xl);
}
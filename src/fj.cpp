#include<iostream>
#include "head.h"

double fj(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)f1l1(y, yd, yu) * f1r1(x, xl, xr);
}
#include<iostream>
#include "head.h"

double fn(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)f1r1(y, yd, yu) * f1l1(x, xl, xr);
}
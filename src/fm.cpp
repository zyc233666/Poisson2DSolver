#include<iostream>
#include "head.h"

double fm(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)f1r1(y, yd, yu) * f1r1(x, xl, xr);
}
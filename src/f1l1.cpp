#include<iostream>
#include "head.h"

// 一维1次形函数
// f1l: 1 D, left f of 1 order
double f1l1(double x, double xl, double xr)
{
	return (double)(x - xr) / (xl - xr);
}

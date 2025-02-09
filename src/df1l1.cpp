#include<iostream>
#include "head.h"

// 定义一维一次函数的导数
double df1l1(double x, double xl, double xr)
{
	return (double)1 / (xl - xr);
}
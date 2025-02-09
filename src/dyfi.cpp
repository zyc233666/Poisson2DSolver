#include<iostream>
#include "head.h"

// 定义二维形函数的偏导数
//y

double dyfi(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)df1l1(y, yd, yu) * f1l1(x, xl, xr);
}
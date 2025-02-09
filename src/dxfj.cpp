#include<iostream>
#include "head.h"

// 定义二维形函数的偏导数
// x

double dxfj(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)f1l1(y, yd, yu) * df1r1(x, xl, xr);
}
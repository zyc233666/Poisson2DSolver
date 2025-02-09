#include<iostream>
#include "head.h"

// 定义二维形函数
// f_(i, j, m, n)表示在该点的值为1
double fi(double y, double x, double yd, double yu, double xl, double xr)
{
	return (double)f1l1(y, yd, yu) * f1l1(x, xl, xr);
}
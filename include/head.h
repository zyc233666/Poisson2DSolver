#ifndef _HEAD_H
#define _HEAD_H
#include<fstream>  //ifstream
#include<iostream>
#include <iomanip>
#include<string>     //包含getline()
#include <vector>
#include <assert.h>

#include <cstdio>
#include "exprtk.hpp"

#include<cmath>
#include <time.h>
#include"Matrix.h" //Matrix库下载地址
#include"MatrixIO.h"//MatrixIO库下载地址
#include <windows.h>
#include <ctime>

#include "head.h"

using sym_table_t = exprtk::symbol_table<double>;
using expr_t = exprtk::expression<double>;
using parser_t = exprtk::parser<double>;
#define _pi_ 3.141592653535897

using namespace std;
using namespace Numeric_lib;//整个库定义在名字空间  Numeric_lib 中
typedef Numeric_lib::Matrix<double, 2>Matrix2;
typedef Numeric_lib::Matrix<double, 1> Vector;

// 一维1次形函数
double f1l1(double x, double xl, double xr);// f1l: 1 D, left f of 1 order
double f1r1(double x, double xl, double xr);// f1r: 1 D, righ f of 1 order
// 定义一维一次函数的导数
double df1l1(double x, double xl, double xr);
double df1r1(double x, double xl, double xr);
// 定义二维形函数
// f_(i, j, m, n)表示在该点的值为1
double fi(double y, double x, double yd, double yu, double xl, double xr);
double fj(double y, double x, double yd, double yu, double xl, double xr);
double fm(double y, double x, double yd, double yu, double xl, double xr);
double fn(double y, double x, double yd, double yu, double xl, double xr);
// 定义二维形函数的偏导数
// x
double dxfi(double y, double x, double yd, double yu, double xl, double xr);
double dxfj(double y, double x, double yd, double yu, double xl, double xr);
double dxfm(double y, double x, double yd, double yu, double xl, double xr);
double dxfn(double y, double x, double yd, double yu, double xl, double xr);
//y
double dyfi(double y, double x, double yd, double yu, double xl, double xr);
double dyfj(double y, double x, double yd, double yu, double xl, double xr);
double dyfm(double y, double x, double yd, double yu, double xl, double xr);
double dyfn(double y, double x, double yd, double yu, double xl, double xr);

//2.2 数值积分
// 计算勒让德多项式
double legendre(int n, double x);
double legendre_derivative(int n, double x);// 计算勒让德多项式的导数
vector<double> reverseArray(vector<double> a);//颠倒一维数组排序
// 计算 N 点高斯-勒让德正交规则的积分点和权重
void gauss_legendre(int N, vector<double>& x, vector<double>& w);
vector<double> gpoints(int gp, int ngp);
//计算形函数及其偏导
vector<vector<double>> shp_cal(double xi, double eta, double xa, double xb, double ya, double yb);
//线空间函数
vector<double> linspace(double start_in, double end_in, int num_in);
//求解线性方程
void classical_elimination(Matrix2& A, Vector& b);
Vector back_substitution(const Matrix2& A, const Vector& b);
void elim_with_partial_pivot(Matrix2& A, Vector& b);
Vector classic_gaussian_elimination(Matrix2 A, Vector b);
Matrix2 converVector2Matrix2(vector<vector<double>>& a);
Vector converVector2Matrix(vector<double>& b);


double mynorm(vector<double>& duu);

template <typename T>
double muP(string& exqa, double in_v, double in_u);
void readTxt(char* file, int& lx, int& ly, int& Nx, int& Ny,
    double& left, double& right, double& up, double& down, vector<int>& bc_index,
    string& u0, string& fu, string& df, double& rel_tol, double& abs_tol, string& path_det);

vector<double> U_standard(vector<double> y, vector<double> x, int num, int level, double bc, int lx, int ly);
#endif

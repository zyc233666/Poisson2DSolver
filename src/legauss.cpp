#include<iostream>
#include "head.h"

//2.2 数值积分

// 计算勒让德多项式
double legendre(int n, double x) {
	if (n == 0) {
		return 1.0;
	}
	else if (n == 1) {
		return x;
	}
	else {
		return ((2 * n - 1) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
	}
}

// 计算勒让德多项式的导数
double legendre_derivative(int n, double x) {
	if (n == 0) {
		return 0.0;
	}
	else if (n == 1) {
		return 1.0;
	}
	else {
		return (n * (legendre(n - 1, x) - x * legendre(n, x))) / (1 - x * x);
	}
}

vector<double> reverseArray(vector<double> a)
{
	return { a.rbegin(), a.rend() };
}

// 计算 N 点高斯-勒让德正交规则的积分点和权重
void gauss_legendre(int N, vector<double>& x, vector<double>& w) {
	const double eps = 1e-15;
	const int max_iter = 100;

	x.resize(N);
	w.resize(N);

	for (int i = 0; i < N; ++i) {
		double z = cos(_pi_ * (i + 0.75) / (N + 0.5));
		double z1;

		for (int iter = 0; iter < max_iter; ++iter) {
			double p1 = 1.0;
			double p2 = 0.0;

			for (int j = 0; j < N; ++j) {
				double p3 = p2;
				p2 = p1;
				p1 = ((2 * j + 1) * z * p2 - j * p3) / (j + 1);
			}

			double pp = N * (z * p1 - p2) / (z * z - 1);
			z1 = z;
			z = z1 - p1 / pp;

			if (abs(z - z1) < eps) {
				break;
			}
		}

		x[i] = z;
		w[i] = 2 / ((1 - z * z) * pow(legendre_derivative(N, z), 2));
	}
	x = reverseArray(x);
}


vector<double> gpoints(int gp, int ngp) {

	vector<double> XI, W;
	gauss_legendre(ngp, XI, W);
	int n_ngp = ngp * ngp;
	vector<int> gpx(n_ngp);
	vector<int> gpy(n_ngp);
	int cnt = 0;
	for (int i = 0; i < ngp; i++) {
		for (int j = 0; j < ngp; j++) {
			gpx[cnt] = i;
			gpy[cnt] = j;
			cnt += 1;
		}
	}
	double xi = XI[gpx[gp]];
	double eta = XI[gpy[gp]];
	double wi = W[gpx[gp]];
	double wj = W[gpy[gp]];
	vector<double> GPM{ xi,eta,wi,wj };

	return GPM;
}
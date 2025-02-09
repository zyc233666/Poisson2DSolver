#include<iostream>
#include "head.h"

vector<double> U_standard(vector<double> y, vector<double> x,int num,int level, double bc, int lx, int ly) {
    vector<double> US(num);
    int us_cnt = 0;
    for (int i = 0; i < y.size(); i++) {
        for (int j = 0; j < x.size(); j++) {
            int k = 1;
            for (int ks = 0; ks < level; ks++) {
                US[us_cnt] += 4 * bc / _pi_ * (sin(k * _pi_ * x[j] / lx) * sinh(k * _pi_ * y[i] / lx)) / (k * sinh(k * _pi_ * ly / lx));                
                k += 2;
            }
            us_cnt++;
        }
    }

    return US;
}
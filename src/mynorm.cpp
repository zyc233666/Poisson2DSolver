#include<iostream>
#include "head.h"

double mynorm(vector<double>& duu) {
    double NORM = 0;
    for (int i = 0; i < duu.size(); i++) {
        NORM += pow(duu[i], 2);
    }

    return sqrt(NORM);
}

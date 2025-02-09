#include<iostream>
#include "head.h"


vector<vector<double>> shp_cal(double xi, double eta, double xa, double xb, double ya, double yb) {
	double a = (xb - xa) * xi / 2 + (xb + xa) / 2;
	double b = (yb - ya) * eta / 2 + (yb + ya) / 2;
	double fie = fi(a, b, ya, yb, xa, xb);
	double fje = fj(a, b, ya, yb, xa, xb);
	double fme = fm(a, b, ya, yb, xa, xb);
	double fne = fn(a, b, ya, yb, xa, xb);
	vector<double> ft{ fie,fje,fme,fne };

	double dxfie = dxfi(a, b, ya, yb, xa, xb);
	double dxfje = dxfj(a, b, ya, yb, xa, xb);
	double dxfme = dxfm(a, b, ya, yb, xa, xb);
	double dxfne = dxfn(a, b, ya, yb, xa, xb);
	vector<double> dx{ dxfie,dxfje,dxfme,dxfne };

	double dyfie = dyfi(a, b, ya, yb, xa, xb);
	double dyfje = dyfj(a, b, ya, yb, xa, xb);
	double dyfme = dyfm(a, b, ya, yb, xa, xb);
	double dyfne = dyfn(a, b, ya, yb, xa, xb);
	vector<double> dy{ dyfie,dyfje,dyfme,dyfne };

	vector < vector<double>> shp{ ft,dx,dy };
	return shp;
}
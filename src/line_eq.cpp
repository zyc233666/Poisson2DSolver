#include<iostream>
#include "head.h"


void classical_elimination(Matrix2& A, Vector& b) {
	const Index n = A.dim1();
	//从第1列一直遍历到倒数第二列
	//将对角线之下所以元素都填充0
	for (Index j = 0; j < n - 1; ++j) {
		const double pivot = A(j, j);
		if (pivot == 0)cerr << "错误：其中有一对角线位为0" << '\n';

		//将第i行在对角线之下的元素都填充为0
		for (Index i = j + 1; i < n; ++i) {
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);  //对b做对应变化
		}
	}
}

Vector back_substitution(const Matrix2& A, const Vector& b) {
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i) {
		double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

		if (double m = A(i, i))
			x(i) = s / m;
		else
			;
	}
	return x;
}


void elim_with_partial_pivot(Matrix2& A, Vector& b) {
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		//查找一个合适的主元：
		for (Index k = j + 1; k < n; ++k)
			if (abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = k;

		//如果我们找到了一个更好的主元，交换两行：
		if (pivot_row != j) {
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		//消去：
		for (Index i = j + 1; i < n; ++i) {
			const double pivot = A(j, j);
			if (pivot == 0)error("can't solve:pivot==0");
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);

		}
	}
}

Vector classic_gaussian_elimination(Matrix2 A, Vector b) {
	elim_with_partial_pivot(A, b);
	//classical_elimination(A, b);
	return back_substitution(A, b);
}


Matrix2 converVector2Matrix2(vector<vector<double>>& a) {
    int am = a.size();
    int an = a[0].size();
    Matrix2 A(am, an);
    for (int i = 0; i < am; i++) {
        for (int j = 0; j < an; j++) {
            A[i][j] = a[i][j];
        }
    }
    return (Matrix2)A;
}

Vector converVector2Matrix(vector<double>& b) {
    int nn = b.size();
    Vector B(nn);
    for (int i = 0; i < nn; i++) {
        B[i] = b[i];
    }
    return (Vector)B;

}
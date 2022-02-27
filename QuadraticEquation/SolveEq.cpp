#include<Header.hpp>

double Disriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

char SolveEquation(double a, double b, double c, double& x1, double& x2) {
	double d = Disriminant(a, b, c);
	if (d < 0) {
		return -1;
	}
	else if (d == 0) {
		x1 = x2 = (-b) / 2 * a;
		return 0;
	}
	else {
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);
		return 1;
	}
}

int main() {
	double a, b, c, x1, x2;
	char flag;
	cout << "Enter coefficients of quadratic equation ax^2 + bx + c = 0 (a is not quel to 0):" << endl;
	cin >> a >> b >> c;
	flag = SolveEquation(a, b, c, x1, x2);
	cout << "The result is:" << endl;
	if (flag == -1) {
		cout << "no real roots";
	}
	else if (flag == 0) {
		cout << "roots are equal: x1 = x2 = " << x1;
	}
	else {
		cout << "x1 = " << x1 << ";  x2 = " << x2;
	}
	
}
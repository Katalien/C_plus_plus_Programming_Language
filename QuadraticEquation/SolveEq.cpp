#include "Header.hpp"

double Disriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

roots SolveEquation(const double a, const double b, const double c, double& x1, double& x2) {
	double d = Disriminant(a, b, c);
	if (d < 0) {
		return noRoots;
	}
	else if (d == 0) {
		x1 = x2 = (-b) / 2 * a;
		return oneRoot;
	}
	else {
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);
		return twoRoots;
	}
}

void EnterCoefficient(double &a, double &b, double &c) {
	cout << "Enter coefficients of quadratic equation ax^2 + bx + c = 0 (a is not quel to 0):" << endl;
	cout << "a = " ;
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
}

void PrintResult(roots amountOfRoots, const double x1, const double x2) {
	cout << "The result is:" << endl;
	if (amountOfRoots == noRoots) {
		cout << "no real roots";
	}
	else if (amountOfRoots == oneRoot) {
		cout << "roots are equal: x1 = x2 = " << x1;
	}
	else {
		cout << "x1 = " << x1 << ";  x2 = " << x2;
	}
}

int main() {
	double a, b, c, x1, x2;
	roots amountOfRoots;
	EnterCoefficient(a, b, c);
	amountOfRoots = SolveEquation(a, b, c, x1, x2);
	PrintResult(amountOfRoots, x1, x2);
}
#include"Equation.hpp"

double Equation::Disriminant() {
	return b * b - 4 * a * c;
}

void Equation::SolveEqCorrect() {
	double d = Disriminant();
	if (d < 0) {
		correctSolution.amountOfRoots = noRoot;
		return;
	}
	else if (d == 0) {
		correctSolution.x1 = correctSolution.x2 = (-b) / 2 * a;
		correctSolution.amountOfRoots = oneRoot;
		return;
	}
	else {
		correctSolution.x1 = (-b + sqrt(d)) / (2 * a);
		correctSolution.x2 = (-b - sqrt(d)) / (2 * a);
		correctSolution.amountOfRoots = twoRoots;
		return;
	}
}
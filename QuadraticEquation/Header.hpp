#pragma once
#include<iostream>
#include<cmath>
using namespace std;

typedef enum roots {
	noRoots,
	oneRoot,
	twoRoots
}roots;

void EnterCoefficient(double& a, double& b, double& c);
double Disriminant(double a, double b, double c);
roots SolveEquation(const double a, const double b, const double c, double& x1, double& x2);
void PrintResult(roots amountOfRoots, const double x1, const double x2);
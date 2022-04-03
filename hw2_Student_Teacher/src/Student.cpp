#pragma once
#include"Student.hpp"
#include"Equation.hpp"
#include"HomeWork.hpp"
#include<random>
#include<ctime>

Equation::Solution Student::SolveOneEquation(Equation eq) {
	Equation::Solution sol = { Equation::noRoot, 0, 0 };
	cout << "Function must be override\n";
	return sol;
}

Equation::Solution BadStudent::SolveOneEquation(Equation eq) {
	Equation::Solution studentSolution;
	studentSolution.x1 = 0;
	studentSolution.amountOfRoots = Equation::oneRoot;
	return studentSolution;
}

Equation::Solution NormStudent::SolveOneEquation(Equation eq) {
	Equation::Solution studentSolution;
	if (!(rand() % 2)) {
		studentSolution.x1 = 0;
		studentSolution.amountOfRoots = Equation::oneRoot;
		return studentSolution;
	}
	else {
		return eq.getSolution();
	}
}

Equation::Solution GoodStudent::SolveOneEquation(Equation eq) {
	return eq.getSolution();
}

void Student::DoHomeWork() {
	vector <Equation> equations = hw->getEquations();
	vector <Equation::Solution> studentAnswers;
	for (int i = 0; i < equations.size(); i++) {
		studentAnswers.push_back(SolveOneEquation(equations[i]));
	}
	hw->SetStudentAnswer(studentAnswers);
}
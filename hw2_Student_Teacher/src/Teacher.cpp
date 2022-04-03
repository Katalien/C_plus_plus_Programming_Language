#pragma once
#include"Equation.hpp"
#include"HomeWork.hpp"
#include"Student.hpp"
#include"Teacher.hpp"
#include<iomanip>

using namespace::std;

void Teacher::AddToQeuee(HomeWork hw) {
	vector <Equation::Solution> answers = hw.getAnswers();
	for (int i = 0; i < answers.size(); i++) {
		QueueItem curQueue = { hw.getEquations()[i],hw.getAnswers()[i], hw.GetStudent() };
		answersToCheck.push(curQueue);
	}
}

Teacher::Bool Teacher::IsSolCorrect(Equation::Solution correctSolution, Equation::Solution solToCheck) {
	if (correctSolution.amountOfRoots != solToCheck.amountOfRoots) {
		return FALSE;
	}
	else if (correctSolution.amountOfRoots == Equation::Roots::noRoot) {
		return TRUE;
	}
	else if (correctSolution.amountOfRoots == Equation::Roots::oneRoot && correctSolution.x1 == solToCheck.x1) {
		return TRUE;
	}
	else if (correctSolution.amountOfRoots == Equation::Roots::twoRoots && correctSolution.x1 == solToCheck.x1 && correctSolution.x2 == solToCheck.x2) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Teacher::CheckAnswers() {
		while(!answersToCheck.empty()) {
			QueueItem answerItem = answersToCheck.front();
			answersToCheck.pop();
			resultsTable[answerItem.student];
			Equation::Solution correctSol = answerItem.eq.getSolution();
			Equation::Solution studentSol = answerItem.ans;
			if (IsSolCorrect(correctSol, studentSol) == TRUE) {
				resultsTable[answerItem.student]++;
			}
		}
	}

void Teacher::PrintTable() {
	int line = 46;
	int firstColSize = 20;
	int secondColSize = 26;
	cout << "+" << setfill('-') << setw(34) << "+" << endl;
	cout << "|    Surname Name     |" << setfill(' ') << setw(10)  << "  Score    |" << endl;
	cout << "+" << setfill('-') << setw(34) << "+" << endl;
	for (auto& item : Teacher::resultsTable) {
		cout << "|  " << item.first->getname()  << setfill(' ') << setw(firstColSize - item.first->getname().length()) << "|" << "     " << item.second << "     |" << endl;
	}
	cout << "+" << setfill('-') << setw(34) << "+" << endl;
}
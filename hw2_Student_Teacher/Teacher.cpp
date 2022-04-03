#pragma once
#include"Equation.hpp"
#include"HomeWork.hpp"
#include"Student.hpp"
#include"Teacher.hpp"


void Teacher::AddToQeuee(HomeWork hw) {
	vector <Equation::Solution> answers = hw.getAnswers();
	for (int i = 0; i < answers.size(); i++) {
		QueueItem* curQueue = nullptr;
		curQueue->student = hw.GetStudent();
		curQueue->eq = hw.getEquations()[i];
		curQueue->ans = hw.getAnswers()[i];
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
	QueueItem* answerItem = nullptr;
	for (int i = 0; i < answersToCheck.size(); i++) {
		resultsTable[answerItem->student] = 0;
	}
	while(!answersToCheck.empty()) {
		answerItem = answersToCheck.front();
		answersToCheck.pop();		
		Equation::Solution correctSol = answerItem->eq.getSolution();
		Equation::Solution studentSol = answerItem->ans;
		if (IsSolCorrect(correctSol, studentSol) == TRUE) {
			resultsTable[answerItem->student]++;
		}
	}
}

void Teacher::PrintTable() {
	cout << "Student" << "   " << "Score" << "\n";
	for (auto item : Teacher::resultsTable) {
		cout << item.first << "  " << item.second <<"\n";
	}
}
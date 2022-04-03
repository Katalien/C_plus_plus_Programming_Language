#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Equation.hpp"
//#include "Student.hpp"

class Student;
using std::vector;

class HomeWork {
public:
	void SetEquations(vector <Equation> _equations) { equations = _equations; };
	void SetStudentAnswer(vector <Equation::Solution> _studentAnswers) { studentAnswers = _studentAnswers; };
	void SetStudent(Student* _student) { student = _student; };
	vector <Equation> getEquations() { return equations; };
	vector <Equation::Solution> getAnswers() { return studentAnswers; };
	Student* GetStudent() { return student; };
private:
	vector <Equation> equations;
	vector <Equation::Solution> studentAnswers;
	Student* student;
};
#pragma once
#include<iostream>
#include<string>
#include"Equation.hpp"
#include"HomeWork.hpp"
#include"Teacher.hpp"

using namespace std;
using std::string;





class Student {
public:
	Student(string& studentName) : name(studentName) {};
	string getname() { return name; };
	void DoHomeWork();
	virtual Equation::Solution SolveOneEquation(Equation eq);
	void SetTeacher(Teacher* _teacher) { teacher = _teacher; };
	void SetHomework(HomeWork* _hw) { hw = _hw;  hw->SetStudent(this);}; 
	HomeWork* GetHomework() { return hw; };
private:
	string name;
	Teacher* teacher;
	HomeWork* hw;
};

class BadStudent : public Student {
public:
	BadStudent(string studentName) : Student(studentName) {};
	Equation::Solution SolveOneEquation(Equation eq);
};

class NormStudent : public Student {
public:
	NormStudent(string studentName) : Student(studentName) {};
	Equation::Solution SolveOneEquation(Equation eq);
};

class GoodStudent : public Student {
public:
	GoodStudent(string studentName) : Student(studentName) {};
	Equation::Solution SolveOneEquation(Equation eq);
};
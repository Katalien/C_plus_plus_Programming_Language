#pragma once
#pragma once
#include<queue>
#include<string>
#include<map>
#include"Student.hpp"
#include"Equation.hpp"

using std::queue;
using std::string;
using std::map;

class HomeWork;

class Teacher {
public:
	struct QueueItem {
		Equation eq;
		Equation::Solution ans;
		Student* student;
	};
	struct Result {
		string name;
		int correctAnswers;
	};
	typedef enum Bool {
		FALSE,
		TRUE
	}Bool;

	Teacher(string& teacherName) : name(teacherName) {};
	queue<QueueItem> GetQueue() { return answersToCheck; };
	void AddToQeuee(HomeWork hw);
	Bool IsSolCorrect(Equation::Solution correctSolution, Equation::Solution solToCheck);
	void CheckAnswers();
	void PrintTable();

private:
	string name;
	queue<QueueItem> answersToCheck;
	map<Student*, int > resultsTable;
};
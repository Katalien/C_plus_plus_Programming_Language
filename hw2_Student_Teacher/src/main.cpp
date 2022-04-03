#include"Equation.hpp"
#include"HomeWork.hpp"
#include"Student.hpp"
#include<iostream>
#include<fstream>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

const vector <string> firstName = { "Ivan", "Petya", "Alisa", "Maya", "Kolya", "Jensen", "Michel", "Yana" };
const vector <string> lastName = { "Ivanovich", "Sviridich", "Trimovich", "Veselco", "Petrovco", "Hrapovich", "Voilenco", "Berch" };

string CreateName(const int i, const int j);
vector <Student*> CreateStudents(int amountOfStudents, Teacher* teacher);
Teacher* CreateTeacher(string teacherName);
vector<Equation> ReadEquations();
void DoHomework(vector <Student*> students, vector<Equation> equations, Teacher* teacher);
void FreeMemory(vector <Student*> students, Teacher* teacher);

int main() {
	srand(time(0));
	int amountOfStudents = 10;
	string teacherName = "Vasiliy Miroshenko";
	Teacher* teacher = CreateTeacher(teacherName);
	vector <Student*> students = CreateStudents(amountOfStudents, teacher);
	vector<Equation> equations = ReadEquations();
	DoHomework(students, equations, teacher);
	teacher->CheckAnswers();
	teacher->PrintTable();
	FreeMemory(students, teacher);
}

string CreateName(const int i, const int j) {
	return (lastName.at(i) + " " + firstName.at(j));
}

vector <Student*> CreateStudents(int amountOfStudents, Teacher* teacher) {
	int tmp;
	vector <Student*> students;
	for (int i = 0; i < amountOfStudents; i++) {
		Student* newStudent = NULL;
		tmp = rand() % 3;
		if (tmp == 0) {
			newStudent = new BadStudent(CreateName(rand() % 7, rand() % 7));
		}
		if (tmp == 1) {
			newStudent = new NormStudent(CreateName(rand() % 7, rand() % 7));
		}
		if (tmp == 2) {
			newStudent = new GoodStudent(CreateName(rand() % 7, rand() % 7));
		}
		newStudent->SetTeacher(teacher);
		students.push_back(newStudent);
	}
	return students;
}

Teacher* CreateTeacher(string teacherName) {
	Teacher* teacher = new Teacher(teacherName);
	return teacher;
}

vector<Equation> ReadEquations() {
	ifstream fp("test.txt");
	double a, b, c;
	if (!fp.is_open()) {
		cout << "error in file";
	}
	vector<Equation> equations;
	while (!fp.eof()) {
		fp >> a;
		fp >> b;
		fp >> c;
		Equation curEq { a, b, c };
		equations.push_back(curEq);
	}
	return equations;
}

void DoHomework( vector <Student*> students, vector<Equation> equations, Teacher* teacher) {
	for (int i = 0; i < students.size(); i++) {
		HomeWork* hw = new HomeWork;
		hw->SetEquations(equations);
		students[i]->SetHomework(hw);
		students[i]->DoHomeWork();
		teacher->AddToQeuee(*(students[i]->GetHomework()));
	}
}

void FreeMemory(vector <Student*> students, Teacher* teacher) {
	for (int i = 0; i < students.size(); i++) {
		delete students[i]->GetHomework();
		delete students[i];
	}
	delete teacher;
}
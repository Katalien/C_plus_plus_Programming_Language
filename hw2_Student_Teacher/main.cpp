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

const vector <string> firstName = { "Ivan", "Petya", "Alisa", "Maya", "Kolya", "Fransya", "Michel", "Yana" };
const vector <string> lastName = { "Ivanovich", "Sviridich", "Trimovich", "Veselco", "Petrovco", "Hrapovich", "Voilenco", "Berch" };

string createName(const int i, const int j) {
	return (lastName.at(i) + " " + firstName.at(j));
}

vector <Student*> CreateStudents() {



}

int main() {
	srand(time(0));
	// create teacher and students
	int amountOfStudents = 10;
	vector <Student*> students;
	int tmp;
	string teacherName = "Vasiliy Miroshenko";
	Teacher* teacher = new Teacher(teacherName);

	for (int i = 0; i < amountOfStudents; i++) {
		Student* newStudent = NULL;
		tmp = rand() % 3;
		if (tmp == 0) {
			newStudent = new BadStudent(createName(rand() % 7, rand() % 7));			
		}
		if (tmp == 1) {
			newStudent = new NormStudent(createName(rand() % 7, rand() % 7));			
		}
		if (tmp == 2) {
			newStudent = new GoodStudent(createName(rand() % 7, rand() % 7));
		}
		newStudent->SetTeacher(teacher);
		students.push_back(newStudent);
	}
	// read equations
	ifstream fp("test.txt");
	double a, b, c;
	if (!fp.is_open()) {
		cout << "error in file";
	}
	vector<Equation> equations;
	while (fp.is_open()) {
		fp >> a;
		fp >> b;
		fp >> c;
		Equation* curEq = new Equation(a, b, c);
		equations.push_back(*curEq);
	}
	//give in hw
	for (int i = 0; i < amountOfStudents; i++) {
		HomeWork* hw = new HomeWork;
		hw->SetEquations(equations);
		students[i]->SetHomework(hw);
	}
	// do homework and send to teacher
	for (int i = 0; i < amountOfStudents; i++) {
		students[i]->DoHomeWork();
		teacher->AddToQeuee(*(students[i]->GetHomework()));
	}
	//check and print Table
	teacher->CheckAnswers();
	teacher->PrintTable();

	for(int i = 0; i<amountOfStudents; i++){
		delete students[i];
	}
	delete teacher;
}

// заполнить equation
// решить equation
// очистить память
// поменять на указатели?
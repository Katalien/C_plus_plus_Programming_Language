#include<iostream>
using namespace::std;

class Figure {
public:
	Figure(int height_, int width_) : height(height_), width(width_) {};
	void SetSides(int height_, int width_) {}
	int getHeight() { return height; };
	int getWidth() { return width; };
	int CountS() { return height * width; };
	virtual int getS() { if (S == -1) return CountS(); else return CountS(); }
	virtual void Draw() {};
protected:
	int height;
	int width;
	int S = -1;
};

class Square : public Figure {
public:
	Square(int height_, int width_) : Figure(height_, width_) {};
	void Draw() { cout << "H:" << height << ",W:" << width << endl; return; };
};

class Rectangle : public Figure {
public:
	Rectangle(int height_, int width_) : Figure(height_, width_) {};
	void Draw() { cout << "H:" << height << ",H:" << height << endl; return; };
};

int main() {
	Square* A = new Square(5, 5);
	Rectangle* B = new Rectangle(5, 10);
	cout << "Square A = " << A->CountS() << " Square B = " << B->CountS() << endl;
	A->Draw();
	B->Draw();
}
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<math.h>
#include "Additional.hpp"

class Container;

using namespace sf;

constexpr float blockSide{ 85.0 };

using namespace std;


class Block {
public:
	typedef enum blockColors {
		Green, 
		Yellow, 
		Red, 
		Blue, 
		Magenta,
	}blockColors;

	Color RandBlockColor() {
		int a = rand() % 5;
		if (a == 0) { return Color::Green; }
		if (a == 1) { return Color::Yellow; }
		if (a == 2) { return Color::Red; }
		if (a == 3) { return Color::Blue; }
		if (a == 4) { return Color::Magenta; }
		
	}

	RectangleShape shape;
	Block() { isChosen = false; };
	Block(float _x, float _y) { 
		shape.setPosition(_x, _y); 
		shape.setSize({ blockSide, blockSide });
		shape.setOrigin({ blockSide / 2.f, blockSide / 2.f });
		shape.setFillColor(RandBlockColor());
		shape.setRotation(45.0);
		isChosen = false;
	};
	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float getLeft() { return getX() - diag / 2.f; };
	float getRight() { return getX() + diag / 2.f; };
	float getTop() { return getY() - diag / 2.f; };
	float getButton() { return getY() + diag / 2.f; };
	float getDiag() { return diag; };

	//bool IsActivated(float x, float y) {
	//	
	//	//if ((x > getLeft()) && (y > getTop()) && (x < getRight()) && (y < getButton())) {
	//	float _x = fabs(-getLeft() + diag / 2.f - x );
	//	cout << x << " " << y << endl;
	//	cout << getTop() << endl;
	//	cout << getLeft() << endl;
	//	cout << (diag / 2.f - x + getLeft()) << endl;
	//	cout << getTop() + (diag / 2.f - x + getLeft()) << endl << endl;
	//	//cout << getLeft() << endl;
	//	//cout << getRight() << endl;
	//	//cout << getTop() << endl;
	//	//cout << getButton() << endl;
	//	//cout << "_x = " << _x << endl << endl;
	//	if ((x > getLeft() && x < getRight() && y>getTop() + (diag/2.f - x + getLeft()) && y < getButton() - (diag/2.f - x + getLeft() ))) {
	//		isChosen = true;
	//		cout << "here" << endl;
	//		return true;
	//	}
	//	
	//	else {
	//		return false;
	//	}
	//}

	bool IsActivated(float x, float y) {
		Additional formula;
		Vector2f a{ getLeft(), getTop() + diag / 2.f };
		Vector2f b{ getLeft() + diag / 2.f,getTop() };
		Vector2f c{ getRight(), getTop() + diag / 2.f };
		Vector2f d{ getLeft() + diag / 2.f, getButton() };
		Vector2f o{ x, y };
		float s1 = formula.CountTriangle(a, o, b);
		float s2 = formula.CountTriangle(a, o, d);
		float s3 = formula.CountTriangle(b, o, c);
		float s4 = formula.CountTriangle(c, o, d);
		float s = s1 + s2 + s3 + s4;
		cout << s << " " << square << endl;
		
		if ((int)s <= (int)square) {
			isChosen = true;
			//shape.setSize({ blockSide + 10.f,blockSide + 10.f });
			return true;
		}
		else {
			return false;
		}

	}

	bool IsChosen() { return isChosen; };

	Container* GetContainer() {
		return container;
	}

	void SetContainer(Container* cont) {
		container = cont;
	}

	void SetState(bool state) {
		isChosen = state;
	}

private:
	float diag = sqrt(2 * blockSide * blockSide);
	bool isChosen;
	float square = diag * diag / 2;
	Container* container;
};
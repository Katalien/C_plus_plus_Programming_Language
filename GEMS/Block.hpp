#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<math.h>
using namespace sf;

constexpr double blockSide{ 85.0 };



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
	Block();
	Block(double _x, double _y) { 
		shape.setPosition(_x, _y); 
		shape.setSize({ blockSide, blockSide });
		shape.setOrigin({ blockSide / 2.f, blockSide / 2.f });
		shape.setFillColor(RandBlockColor());
		shape.setRotation(45.0);
	};
	double getX() { return shape.getPosition().x; };
	double getY() { return shape.getPosition().y; };
	double GetDiag() { return diag; };

private:
	double diag = sqrt(2 * blockSide * blockSide);
};
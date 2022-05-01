#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Window.hpp"

using namespace std;
using namespace sf;

constexpr float bonusWidth{ 20.f }, bonusHeight{ 20.f }, bonusVelocity{ 8.f };

class Bonus{
public:
	RectangleShape shape;
	Vector2f velocity{0, bonusVelocity };

	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; }
	float right() { return getX() + shape.getSize().x / 2.f; }
	float top() { return getY() - shape.getSize().y / 2.f; }
	float bottom() { return getY() + shape.getSize().y / 2.f; }
	Bonus() {};
	Bonus(float _x, float _y) {
		shape.setPosition(_x, _y);
		shape.setFillColor(Color::Green);
		shape.setSize({ bonusWidth, bonusHeight });
		shape.setOrigin(bonusWidth / 2.f, bonusHeight / 2.f);
		
	}
	void update() {
		shape.move(velocity);
	}
};
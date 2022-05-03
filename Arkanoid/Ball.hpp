#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Window.hpp"

using namespace std;
using namespace sf;


constexpr float ballRadius{ 10.f }, ballVelocity{5.f};

class Ball {
public:
	CircleShape shape;
	Vector2f velocity{ -ballVelocity, -ballVelocity };
	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getRadius(); }
	float right() { return getX() + shape.getRadius(); }
	float top() { return getY() - shape.getRadius(); }
	float bottom() { return getY() + shape.getRadius(); }
	
	Ball(float _x, float _y) {
		shape.setRadius(ballRadius);
		shape.setFillColor(Color::White);
		shape.setPosition(_x, _y);
		shape.setOrigin(ballRadius, ballRadius);
	}
	void update() { 
		shape.move(velocity);
		if (left() < 0) {
			velocity.x = ballVelocity;
		}
		else if (right() > windowWidth) {
			velocity.x = -ballVelocity;
		}
		if (top() < 70) {
			velocity.y = ballVelocity;
		}
		else if (bottom() > windowHeight) {
			velocity.y = -ballVelocity;
		}
	};
};
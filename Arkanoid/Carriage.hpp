#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.hpp"


using namespace std;
using namespace sf;

constexpr float carriageWidth{80.f}, carriageHeight{20.f}, carriageVelocity{0.4};

class Carriage {
public:
	RectangleShape shape;
	Carriage(float _x, float _y);
	void update();

	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; }
	float right() { return getX() + shape.getSize().x / 2.f; }
	float top() { return getY() - shape.getSize().y / 2.f; }
	float bottom() { return getY() + shape.getSize().y / 2.f; }

	
	void SetVelocityX(float vel) { velocity.x = vel; };
	void SetVelocityY(float vel) { velocity.y = vel; };
	float GetVelocityX() { return velocity.x; };
	float GetVelocityY() { return velocity.y; };
	Vector2f GetVelocity() { return velocity; };
private:
	Vector2f velocity;
};
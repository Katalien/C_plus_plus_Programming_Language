#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Window.hpp"
#include<iostream>

using namespace std;
using namespace sf;


constexpr float ballRadius{ 10.f }, ballVelocity{ 0.2 }, speedUpBallVelocity{0.5};

class Ball {
public:
	CircleShape shape;
	
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
		velocity.x = -ballVelocity;
		velocity.y = -ballVelocity;
	}
	void update(float _ballVelX, float _ballVelY) {
		velocity.x = _ballVelX;
		velocity.y = _ballVelY;
		shape.move(velocity);
		if (left() < 0) {
			//SetVelocityX(_ballVelocity);
			//velocity.x = ballVelocity;
			//cout << "I'm here" << endl;
			//cout << "x  before "<< velocity.x << endl;
			SetVelocityX ( -GetBallVelocityX());
			//cout << "x  after " << velocity.x << endl;
		}
		else if (right() > windowWidth) {
			//SetVelocityX(-_ballVelocity);
			//velocity.x = -ballVelocity;
			velocity.x = -1*GetBallVelocityX();
		}
		if (top() < 70) {
			//SetVelocityY(_ballVelocity);
			//velocity.y = ballVelocity;
			//cout << "y before   " << velocity.y << endl;
			velocity.y = -GetBallVelocityY();
			//cout << "y after " << velocity.y << endl;
		}
		else if (bottom() >= windowHeight) {
			//SetVelocityY(-_ballVelocity);
			//velocity.y = -ballVelocity;
			velocity.y = -GetBallVelocityY();
		}
	};
	void speedUp(float _ballVelX, float _ballVelY) {
		velocity.x = _ballVelX;

		shape.move(speedUpVelocity);
		if (left() < 0) {
			SetVelocityX(speedUpBallVelocity);
			//velocity.x = ballVelocity;
		}
		else if (right() > windowWidth) {
			SetVelocityX(-speedUpBallVelocity);
			//velocity.x = -ballVelocity;
		}
		if (top() < 70) {
			SetVelocityY(speedUpBallVelocity);
			//velocity.y = ballVelocity;
		}
		else if (bottom() > windowHeight) {
			SetVelocityY(-speedUpBallVelocity);
			//velocity.y = -ballVelocity;
		}
	};

	void SetVelocityX(float x) { velocity.x = x; };
	void SetVelocityY(float y) { velocity.y = y; };
	float GetBallVelocityX() { return velocity.x; };
	float GetBallVelocityY() { return velocity.y; };

private:
	//Vector2f velocity{ -ballVelocity, -ballVelocity };
	Vector2f velocity;
	Vector2f speedUpVelocity{ -speedUpBallVelocity, -speedUpBallVelocity };
};

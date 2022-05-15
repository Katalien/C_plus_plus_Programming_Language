#include "Carriage.hpp"

Carriage::Carriage(float _x, float _y) {
	shape.setPosition(_x, _y);
	shape.setFillColor(Color::Red);
	shape.setSize({ carriageWidth, carriageHeight });
	shape.setOrigin(carriageWidth / 2.f, carriageHeight / 2.f);
}
void Carriage:: update() {
	shape.move(velocity);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
		velocity.x = -carriageVelocity;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) {
		velocity.x = carriageVelocity;
	}
	else {
		velocity.x = 0;
	}
}
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.hpp"

using namespace std;
using namespace sf;

constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr int countBlocksX{ 11 }, countBlockY{ 4 };

class Block {
public:
	RectangleShape shape;
	bool destroyed{ false };

	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; }
	float right() { return getX() + shape.getSize().x / 2.f; }
	float top() { return getY() - shape.getSize().y / 2.f; }
	float bottom() { return getY() + shape.getSize().y / 2.f; }

	Block(float _x, float _y) {
		shape.setFillColor(Color::Yellow);
		shape.setSize({blockWidth, blockHeight});
		shape.setPosition(_x, _y);
		shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	}

};
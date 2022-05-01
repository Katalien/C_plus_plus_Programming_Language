#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.hpp"
#include"Bonus.hpp"

using namespace std;
using namespace sf;

constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr int countBlocksX{ 11 }, countBlockY{ 4 };

typedef enum Type {
	null,
	normal,
	unbreakable,
	withBonus,
	speedUp,
}Type;

class Block {
public:
	
	RectangleShape shape;
	bool destroyed{ false };
	Type type = normal;
	void SetType(Type _type) { type = _type; };
	Type GetType() { return type; };
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

class UnbreakableBlock : public Block {
public:
	UnbreakableBlock(float _x, float _y):Block( _x, _y) {
		shape.setFillColor(Color::Red);
		SetType(unbreakable);
	}
};

class BlockWithBonus : public Block {
public:
	int bonus;
	void SetBonus(int _bonus) { bonus = _bonus; };
	BlockWithBonus(float _x, float _y) :Block(_x, _y) {
		shape.setFillColor(Color::Cyan);
		SetBonus(rand() % 5);
		SetType(withBonus);
	}
};

class SpeedUpBlock : public Block {
public:
	int bonus;
	SpeedUpBlock(float _x, float _y) :Block(_x, _y) {
		shape.setFillColor({ 100, 50, 80, 255 });
		SetType(speedUp);
	}
};
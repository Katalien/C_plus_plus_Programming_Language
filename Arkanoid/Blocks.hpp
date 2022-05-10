#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.hpp"
class Bonus;

using namespace std;
using namespace sf;

constexpr float blockWidth{ 60.f }, blockHeight{ 20.f }, moveBlockVelocity{0.1};
constexpr int countBlocksX{ 11 }, countBlockY{ 4 };

typedef enum Type {
	null,
	normal,
	unbreakable,
	withBonus,
	speedUp,
	movingBlock,
}Type;

class Block {
public:
	
	RectangleShape shape;
	Block(float _x, float _y);
	bool destroyed{ false };
	int getLives() { return lives; }
	void reduceLives() {lives = getLives() - 1;}
	void changeOpacity();
	void SetType(Type _type) { type = _type; };
	Type GetType() { return type; };
	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; }
	float right() { return getX() + shape.getSize().x / 2.f; }
	float top() { return getY() - shape.getSize().y / 2.f; }
	float bottom() { return getY() + shape.getSize().y / 2.f; }

private:
	Type type;
	int lives;
};

class UnbreakableBlock : public Block {
public:
	UnbreakableBlock(float _x, float _y);
};

class BlockWithBonus : public Block {
public:
	int bonus;
	void SetBonus(int _bonus) { bonus = _bonus; };
	BlockWithBonus(float _x, float _y);
};

class SpeedUpBlock : public Block {
public:
	int bonus;
	SpeedUpBlock(float _x, float _y);
};

class MovingBlock : public Block {
public:
	
	MovingBlock(float _x, float _y);
	void update();
private:
	Vector2f velocity;
};
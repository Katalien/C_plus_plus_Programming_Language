#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.hpp"
//#include"Bonus.hpp"
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

	bool destroyed{ false };
	int getLives() { return lives; }
	void reduceLives() {
			lives = getLives() - 1;
	}
	void changeOpacity() {
		if (GetType() != unbreakable) {
			uint8_t transparensy = shape.getFillColor().a + 85;
			Color tmpColor = { 0, 0, 0, transparensy };
			Color newColor = shape.getFillColor() - tmpColor;
			shape.setFillColor(newColor);
		}
	}
	void SetType(Type _type) { type = _type; };
	Type GetType() { return type; };
	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; }
	float right() { return getX() + shape.getSize().x / 2.f; }
	float top() { return getY() - shape.getSize().y / 2.f; }
	float bottom() { return getY() + shape.getSize().y / 2.f; }

	Block(float _x, float _y) {
		SetType(normal);
		shape.setFillColor(Color:: Yellow);
		shape.setSize({blockWidth, blockHeight});
		shape.setPosition(_x, _y);
		shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
		lives = 3;
	}
private:
	Type type;
	int lives;

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
		shape.setFillColor(Color:: Magenta);
		SetType(speedUp);
	}
};

class MovingBlock : public Block {
public:
	
	MovingBlock(float _x, float _y) : Block(_x, _y) {
		shape.setFillColor(Color::Green);
		SetType(movingBlock);
		velocity.x = moveBlockVelocity;
		velocity.y = 0;

	}
	void update() {
		shape.move({ moveBlockVelocity, 0 });
		if ( left() <= 0) {
			//shape.move({ moveBlockVelocity, 0 });
			velocity.x = moveBlockVelocity;
		}
		else if (right() >= windowWidth) {
			//shape.move({ -moveBlockVelocity, 0 });
			velocity.x = -2*moveBlockVelocity;
		}
		shape.move(velocity);
	}
private:
	Vector2f velocity;
};
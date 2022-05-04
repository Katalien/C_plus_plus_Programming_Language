#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Window.hpp"

using namespace std;
using namespace sf;

constexpr float bonusWidth{ 20.f }, bonusHeight{ 20.f }, bonusVelocity{ 8.f };
const Time oneBonusTime = seconds(10);

typedef enum BonusType {
	sizeIncreaseBonus,
	speedDownBonus,
	safeBottomBonus,
	stickCarriageBonus,
	changeWayBonus,
};

class Bonus{
public:
	RectangleShape shape;
	Vector2f velocity{0, bonusVelocity };
	BonusType GetType() { return type; };
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
		SetStartTime(seconds(0));
	}
	void update() {
		shape.move(velocity);
	}
	void SetType(BonusType _type) { type = _type; };
	Time GetStartTime() { return startTime; };
	void SetStartTime(Time _startTime) { startTime = _startTime; };
private:
	BonusType type;
	Clock bonusClock;
	Time startTime;
};

class SizeIncreaseBonus : public Bonus {
public:
	SizeIncreaseBonus(float _x, float _y) : Bonus(_x, _y) {
		SetType(sizeIncreaseBonus);
	}
} ;
class SpeedDownBonus : public Bonus {
public:
	SpeedDownBonus(float _x, float _y) : Bonus(_x, _y) {
		SetType(speedDownBonus);
	}
};
class SafeBottomBonus : public Bonus {
public:
	SafeBottomBonus(float _x, float _y) : Bonus(_x, _y) {
		SetType(safeBottomBonus);
	}
};
class StickCarriageBonus : public Bonus {
public:
	StickCarriageBonus(float _x, float _y) : Bonus(_x, _y) {
		SetType(stickCarriageBonus);
	}
};
class ChangeWayBonus : public Bonus {
public:
	ChangeWayBonus(float _x, float _y) : Bonus(_x, _y) {
		SetType(changeWayBonus);
	}

};
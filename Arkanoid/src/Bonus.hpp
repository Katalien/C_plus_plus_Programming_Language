#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Window.hpp"
#include <vector>
#include "Blocks.hpp"
#include"Player.hpp"
#include"Carriage.hpp"
#include"Blocks.hpp"

class Interaction;

using namespace std;
using namespace sf;
using std::vector;

constexpr float bonusWidth{ 20.f }, bonusHeight{ 20.f }, bonusVelocity{ 0.3 };
const Time oneBonusTime = seconds(10);

typedef enum BonusType {
	sizeIncreaseBonus,
	speedUpBonus,
	safeBottomBonus,
	stickCarriageBonus,
	changeWayBonus,
	newBlockBonus,
};

class Bonus{
public:
	Bonus() {};
	Bonus(float _x, float _y);
	RectangleShape shape;
	Vector2f velocity{0, bonusVelocity };
	BonusType GetType() { return type; };
	float getX() { return shape.getPosition().x; };
	float getY() { return shape.getPosition().y; };
	float left() { return getX() - shape.getSize().x / 2.f; };
	float right() { return getX() + shape.getSize().x / 2.f; };
	float top() { return getY() - shape.getSize().y / 2.f; };
	float bottom() { return getY() + shape.getSize().y / 2.f; };	
	void update();		
	void SetType(BonusType _type) { type = _type; };
	Time GetStartTime() { return startTime; };
	void SetStartTime(Time _startTime) { startTime = _startTime; };
	void SetActivity(bool condition) { isActive = condition; };
	bool IsActive() { return isActive; };
	void StartTime() { Clock bonusClock; };
	Clock GetBonusClock() { return bonusClock; };
	virtual void BonusActivate() {};
	virtual void BonusDeactivate() {};
	void BonusCheck(Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Time gameClock);		
private:
	BonusType type;
	Clock bonusClock;
	Time startTime;
	bool isActive;
};

class SizeIncreaseBonus : public Bonus {
public:
	SizeIncreaseBonus(float _x, float _y, Carriage* _carriage);
	void BonusActivate();
	void BonusDeactivate();
		
private:
	Carriage* carriage;
} ;

class SpeedUpBonus : public Bonus {
public:
	SpeedUpBonus(float _x, float _y, Ball* _ball);
	void BonusActivate();
	void BonusDeactivate();
private:
	Ball* ball;
};

class SafeBottomBonus : public Bonus {
public:
	SafeBottomBonus(float _x, float _y, RenderWindow* _window, Ball* _ball);
	void BonusActivate();
private:
	RenderWindow* window;
	Ball* ball;
};

class StickCarriageBonus : public Bonus {
public:
	StickCarriageBonus(float _x, float _y, Carriage* _carriage, Ball* _ball);
	void BonusActivate();
private:
	Carriage* carriage;
	Ball* ball;
};

class ChangeWayBonus : public Bonus {
public:
	ChangeWayBonus(float _x, float _y, Ball* _ball);
	void SetRandTime() { randTime = rand() % (int)oneBonusTime.asSeconds(); }
	int GetRandTime() { return randTime; };
	void BonusActivate();
	void BonusDeactivate();
private:
	int randTime;
	Ball* ball;
};

class NewBlockBonus : public Bonus {
public:
	NewBlockBonus(float _x, float _y, Ball* _ball, RenderWindow* _window, Player* _player, Interaction* _interaction);
	void BonusActivate();
		
private:
	MovingBlock* block;
	RenderWindow* window;
	Interaction* interaction;
	Ball* ball;
	Player* player;
	vector<MovingBlock*> blocks;
};
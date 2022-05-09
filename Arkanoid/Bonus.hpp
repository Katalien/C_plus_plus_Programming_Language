#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Window.hpp"
#include <vector>
#include "Blocks.hpp"
#include"Player.hpp"
//#include"Interaction.hpp"

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
		SetActivity(false);
	}
	void update() {
		shape.move(velocity);
	}
	void SetType(BonusType _type) { type = _type; };
	Time GetStartTime() { return startTime; };
	void SetStartTime(Time _startTime) { startTime = _startTime; };
	void SetActivity(bool condition) { isActive = condition; };
	bool IsActive() { return isActive; };
	void StartTime() { Clock bonusClock; };
	Clock GetBonusClock() { return bonusClock; };
	virtual void BonusActivate() {};
	virtual void BonusDeactivate() {};
	void BonusCheck( Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Time gameClock) {
		srand(time(0));
		if (IsActive() == false) {
			cout << "OOOOOOPS" << endl;
			return;
		}
		if (GetBonusClock().getElapsedTime() < oneBonusTime) {
			//cout << ball->GetBallVelocityX() << "  " << ball->GetBallVelocityY() << endl;
			BonusActivate();
		}
		if (GetBonusClock().getElapsedTime() > oneBonusTime) {
			SetActivity(false);
			BonusDeactivate();
		}
	}
private:
	BonusType type;
	Clock bonusClock;
	Time startTime;
	bool isActive;
};

class SizeIncreaseBonus : public Bonus {
public:
	SizeIncreaseBonus(float _x, float _y, Carriage* _carriage) : Bonus(_x, _y) {
		SetType(sizeIncreaseBonus);
		carriage = _carriage;
	}
	void BonusActivate() {
		carriage->shape.setSize({ carriageWidth * 3, carriageHeight });
	};
	void BonusDeactivate() {
		carriage->shape.setSize({ carriageWidth, carriageHeight });
	};
private:
	Carriage* carriage;
} ;


class SpeedUpBonus : public Bonus {
public:
	SpeedUpBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
		SetType(speedUpBonus);
		ball = _ball;
	}
	void BonusActivate() {
		if (fabs(ball->GetBallVelocityX()) == ballVelocity) {
			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() > 0) {
				ball->update(ball->GetBallVelocityX() + 0.2, ball->GetBallVelocityY() + 0.2);
			}
			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() < 0) {
				ball->update(ball->GetBallVelocityX() - 0.2, ball->GetBallVelocityY() - 0.2);
			}
			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() < 0) {
				ball->update(ball->GetBallVelocityX() + 0.2, ball->GetBallVelocityY() - 0.2);
			}
			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() > 0) {
				ball->update(ball->GetBallVelocityX() - 0.2, ball->GetBallVelocityY() + 0.2);
			}
		}
	};
	void BonusDeactivate() {
		if (fabs(ball->GetBallVelocityX()) > ballVelocity) {

			if (ball->GetBallVelocityX() >= 0 && ball->GetBallVelocityY() >= 0) {
				ball->update(ball->GetBallVelocityX() - 0.2, ball->GetBallVelocityY() - 0.2);
			}
			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() < 0) {
				ball->update(ball->GetBallVelocityX() + 0.2, ball->GetBallVelocityY() + 0.2);
			}
			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() < 0) {
				ball->update(ball->GetBallVelocityX() - 0.2, ball->GetBallVelocityY() + 0.2);
			}
			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() > 0) {
				ball->update(ball->GetBallVelocityX() + 0.2, ball->GetBallVelocityY() - 0.2);
			}
			//??
			if (ball->GetBallVelocityX() == 0 && ball->GetBallVelocityY() > 0) {
				ball->update(ball->GetBallVelocityY() + 0.2, ball->GetBallVelocityY() - 0.2);
			}
			if (ball->GetBallVelocityX() == 0 && ball->GetBallVelocityY() < 0) {
				ball->update(ball->GetBallVelocityY() - 0.2, ball->GetBallVelocityY() + 0.2);
			}
			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() == 0) {
				ball->update(ball->GetBallVelocityY() + 0.2, ball->GetBallVelocityY() - 0.2);
			}
			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() == 0) {
				ball->update(ball->GetBallVelocityY() - 0.2, ball->GetBallVelocityY() - 0.2);
			}
		}
	};
private:
	Ball* ball;
};

class SafeBottomBonus : public Bonus {
public:
	SafeBottomBonus(float _x, float _y, RenderWindow* _window, Ball* _ball) : Bonus(_x, _y) {
		SetType(safeBottomBonus);
		window = _window;
		ball = _ball;
	}
	void BonusActivate() {
		RectangleShape shape;
		shape.setPosition(0, windowHeight - 5);
		shape.setFillColor(Color::Yellow);
		shape.setSize({ windowWidth, 5 });
		//cout << ball->GetBallVelocityX() << "   " << ball->GetBallVelocityY() << endl;
		window->draw(shape);
		if (ball->bottom() >= windowHeight) {
			SetActivity(false);
		}
	};
private:
	RenderWindow* window;
	Ball* ball;
};

class StickCarriageBonus : public Bonus {
public:
	StickCarriageBonus(float _x, float _y, Carriage* _carriage, Ball* _ball) : Bonus(_x, _y) {
		SetType(stickCarriageBonus);
		carriage = _carriage;
		ball = _ball;
	}

	void BonusActivate() {
		if ((ball->right() >= carriage->left() && ball->left() <= carriage->right() && ball->bottom() >= carriage->top() && ball->top() <= carriage->bottom()) == false) {
			return;
		}
		ball->SetVelocityY(0);
		ball->SetVelocityX(carriage->GetVelocityX());

		float xPlace = ball->getX() - carriage->getX();
		if (xPlace > 0) {
			ball->shape.setPosition({ carriage->getX() + xPlace, windowHeight - 50 - carriageHeight });
		}
		if (xPlace < 0) {
			ball->shape.setPosition({ carriage->getX() - xPlace, windowHeight - 50 - carriageHeight });
		}
		if (xPlace == 0) {
			ball->shape.setPosition({ carriage->getX(), windowHeight - 50 - carriageHeight });
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			carriage->SetVelocityX(-carriageVelocity);
			ball->SetVelocityX(-carriageVelocity);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			carriage->SetVelocityX(carriageVelocity);
			ball->SetVelocityX(carriageVelocity);

		}
	};
	void BonusDeactivate() {};
private:
	Carriage* carriage;
	Ball* ball;
};

class ChangeWayBonus : public Bonus {
public:
	ChangeWayBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
		SetType(changeWayBonus);
		ball = _ball;
		SetRandTime();
	}
	void SetRandTime() { randTime = rand() % (int)oneBonusTime.asSeconds(); }
	int GetRandTime() { return randTime; };
	void BonusActivate() {
		int changeOption = rand() % 3;
		ball->shape.setFillColor(Color::Green);
		if ((int)GetBonusClock().getElapsedTime().asSeconds() == randTime) {
			cout << changeOption << endl;
			if (changeOption == 0) {
				ball->SetVelocityX(-ball->GetBallVelocityX());
				ball->SetVelocityY(-ball->GetBallVelocityY());

			}
			if (changeOption == 1) {
				ball->SetVelocityX(ball->GetBallVelocityX());
				ball->SetVelocityY(-ball->GetBallVelocityY());

			}
			if (changeOption == 2) {
				ball->SetVelocityX(-ball->GetBallVelocityX());
				ball->SetVelocityY(ball->GetBallVelocityY());
			}
			SetActivity(false);
			BonusDeactivate();
		}
	};
	void BonusDeactivate() {
		ball->shape.setFillColor(Color::White);
	};
private:
	int randTime;
	Ball* ball;
};

class NewBlockBonus : public Bonus {
public:
	NewBlockBonus (float _x, float _y, Ball* _ball, RenderWindow* _window, Interaction* _interaction) : Bonus(_x, _y) {
		SetType(newBlockBonus);
		ball = _ball;
		window = _window;
		interaction = _interaction;
		block = new MovingBlock(windowWidth / 2, windowHeight / 2);
		block->shape.setFillColor(Color::Green);
	}
	void BonusActivate() {
		window->draw(block->shape);
		block->update();		
		//interaction->tmpF();
		
	}
private:
	MovingBlock* block;
	RenderWindow* window;
	Interaction* interaction;
	Ball* ball;
};
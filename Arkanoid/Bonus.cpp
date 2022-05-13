#pragma once
#include "Bonus.hpp"
#include "Ball.hpp"
#include"Interaction.hpp"

Bonus:: Bonus(float _x, float _y) {
	shape.setPosition(_x, _y);
	shape.setFillColor(Color::Green);
	shape.setSize({ bonusWidth, bonusHeight });
	shape.setOrigin(bonusWidth / 2.f, bonusHeight / 2.f);
	SetActivity(false);
}
void Bonus:: update() {
	shape.move(velocity);
}

void Bonus:: BonusCheck(Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Time gameClock) {

	if (IsActive() == false) {
		cout << "OOOOOOPS" << endl;
		return;
	}
	if (GetType() == newBlockBonus) {
		BonusActivate();
		return;
	}
	if (GetBonusClock().getElapsedTime() < oneBonusTime) {
		BonusActivate();
	}
	if (GetBonusClock().getElapsedTime() > oneBonusTime) {
		SetActivity(false);
		BonusDeactivate();
	}
}

SizeIncreaseBonus::SizeIncreaseBonus(float _x, float _y, Carriage* _carriage) : Bonus(_x, _y) {
	SetType(sizeIncreaseBonus);
	carriage = _carriage;
}

void SizeIncreaseBonus :: BonusDeactivate() {
	carriage->shape.setSize({ carriageWidth, carriageHeight });
	carriage->shape.setOrigin(carriage->shape.getSize().x / 2.f, carriageHeight / 2.f);
};

void SizeIncreaseBonus:: BonusActivate() {
	carriage->shape.setSize({ carriageWidth * 3, carriageHeight });
	carriage->shape.setOrigin(carriage->shape.getSize().x / 2.f, carriageHeight / 2.f);
};

SpeedUpBonus::SpeedUpBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
	SetType(speedUpBonus);
	ball = _ball;
}

void SpeedUpBonus::BonusActivate() {
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
void SpeedUpBonus::BonusDeactivate() {
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

SafeBottomBonus::SafeBottomBonus(float _x, float _y, RenderWindow* _window, Ball* _ball) : Bonus(_x, _y) {
	SetType(safeBottomBonus);
	window = _window;
	ball = _ball;
}
void SafeBottomBonus:: BonusActivate() {
	RectangleShape shape;
	shape.setPosition(0, windowHeight - 5);
	shape.setFillColor(Color::Yellow);
	shape.setSize({ windowWidth, 5 });
	//cout << ball->GetBallVelocityX() << "   " << ball->GetBallVelocityY() << endl;
	window->draw(shape);
	//ball->update(ball->GetBallVelocityX(), ball->GetBallVelocityY());
	if (ball->bottom() >= windowHeight) {
		SetActivity(false);
	}
};

StickCarriageBonus::StickCarriageBonus(float _x, float _y, Carriage* _carriage, Ball* _ball) : Bonus(_x, _y) {
	SetType(stickCarriageBonus);
	carriage = _carriage;
	ball = _ball;
}

void StickCarriageBonus::BonusActivate() {
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
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) || ball->right() >= windowWidth) {
		ball->SetVelocityX(-carriageVelocity);

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) || ball->left() <= 0) {
		ball->SetVelocityX(carriageVelocity);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		SetActivity(false);
	}
};

ChangeWayBonus::ChangeWayBonus(float _x, float _y, Ball* _ball) : Bonus(_x, _y) {
	SetType(changeWayBonus);
	ball = _ball;
	SetRandTime();
}

void ChangeWayBonus:: BonusActivate() {
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
void ChangeWayBonus:: BonusDeactivate() {
	ball->shape.setFillColor(Color::White);
};

NewBlockBonus::NewBlockBonus(float _x, float _y, Ball* _ball, RenderWindow* _window, Player* _player, Interaction* _interaction) : Bonus(_x, _y) {
	SetType(newBlockBonus);
	ball = _ball;
	window = _window;
	interaction = _interaction;
	player = _player;
	block = new MovingBlock(windowWidth / 2, windowHeight / 4 + (rand() % (windowHeight / 2) + 70));
	block->shape.setFillColor(Color::Green);
}
void NewBlockBonus::BonusActivate() {
	window->draw(block->shape);
	block->update();
	Type blockType = interaction->solveCollision(*ball, *block);
	if (blockType != null) {
		block->reduceLives();
		block->changeOpacity();
		if (block->getLives() == 0) {
			block->destroyed = true;
			SetActivity(false);
		}
		player->SetScore(player->GetScore() + 1);
	}
}
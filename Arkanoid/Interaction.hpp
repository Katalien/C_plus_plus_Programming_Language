#pragma once
#include "Ball.hpp"
#include "Carriage.hpp"
#include "Blocks.hpp"
#include "Bonus.hpp"
#include "Player.hpp"
#include <cmath>
#include "test.hpp"

class Interaction {
public:
	void tmpF() {}

	template<class T1, class T2> bool IsTouch(T1& first, T2& second) {
		return first.right() >= second.left() && first.left() <= second.right() && first.bottom() >= second.top() && first.top() <= second.bottom();
	}

	void solveCollision(Ball& ball, Carriage& carriage) {
		if (!IsTouch(ball, carriage)) {
			return;
		}
		ball.SetVelocityY(-ballVelocity);
		//ball.velocity.y = -ballVelocity;
		if (ball.getX() < carriage.getX()) {
			ball.SetVelocityX(-ballVelocity);
			//ball.velocity.x = -ballVelocity;
		}
		else {
			ball.SetVelocityX(ballVelocity);
			//ball.velocity.x = ballVelocity;
		}
	}

	Type solveCollision(Ball& ball, Block& block) {
		if (!IsTouch(ball, block)) {
			return null;
		}
		if (block.GetType() == normal || block.GetType() == withBonus || block.GetType() == speedUp) {
			block.reduceLives();
			block.changeOpacity();
			if (block.getLives() == 0) {
				block.destroyed = true;
			}
		}
		float hitLeft{ ball.right() - block.left() };
		float hitRight{ block.right() - ball.left() };
		float hitTop{ ball.bottom() - block.top() };
		float hitBottom{ block.bottom() - ball.top() };

		bool hitFromLeft{ fabs(hitLeft) < fabs(hitRight) };
		bool hitFromTop{ fabs(hitTop) < fabs(hitBottom) };

		float minOverlapX, minOverlapY;
		if (hitFromLeft) {
			minOverlapX = hitLeft;
		}
		else {
			minOverlapX = hitRight;
		}
		if (hitFromTop) {
			minOverlapY = hitTop;
		}
		else {
			minOverlapY = hitBottom;
		}

		if (fabs(minOverlapX) < fabs(minOverlapY)) {
			if (hitFromLeft) {
				ball.SetVelocityX(-ballVelocity);
				//ball.velocity.x = -ballVelocity;
			}
			else {
				ball.SetVelocityX(ballVelocity);
				//ball.velocity.x = ballVelocity;
			}
		}
		else {
			if (hitFromTop) {
				ball.SetVelocityY(-ballVelocity);
				//ball.velocity.y = -ballVelocity;
			}
			else {
				ball.SetVelocityY(ballVelocity);
				//ball.velocity.y = ballVelocity;
			}

		}
		return block.GetType();
	}

	bool IsActivated(Bonus* bonus, Carriage* carriage, Time gameTime) {
		if (!IsTouch(*bonus, *carriage)) {
			//bonus->SetActivity(false);
			return false;
		}
		if (IsTouch(*bonus, *carriage)) {
			bonus->GetBonusClock().restart().asSeconds();
			bonus->SetActivity(true);
			return true;
		}

	}

	void BallCarriageMove(Ball* ball, Carriage* carriage) {
		ball->shape.move({ carriage->GetVelocityX(), 0 });
		ball->SetVelocityY(0);
		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			carriage->SetVelocityX(-carriageVelocity);
			ball->SetVelocityX(-carriageVelocity);

		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			carriage->SetVelocityX(carriageVelocity);
			ball->SetVelocityX(carriageVelocity);

		}
		else {
			ball->SetVelocityX(0);
		}


	}

	void BonusCheck(Bonus* bonus, Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Time gameClock) {
		srand(time(0));
		if (bonus->IsActive() == false) {
			cout << "OOOOOOPS" << endl;
			return;
		}
		if (bonus->GetBonusClock().getElapsedTime() < oneBonusTime) {
			//cout << ball->GetBallVelocityX() << "  " << ball->GetBallVelocityY() << endl;
			bonus->BonusActivate();
		}
		if (bonus->GetBonusClock().getElapsedTime() > oneBonusTime) {
			bonus->SetActivity(false);
			bonus->BonusDeactivate();
		}
	}
};

	//void BonusActivate(Bonus* bonus, Carriage* carriage, Ball* ball, RenderWindow* window,Player* player, Time gameClock) {
	//	if (bonus->GetType() == sizeIncreaseBonus) {
	//			carriage->shape.setSize({ carriageWidth * 3, carriageHeight });			
	//	}
	//	if (bonus->GetType() == speedUpBonus) {
	//		if (fabs(ball->GetBallVelocityX()) == ballVelocity) {
	//			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() > 0) {
	//				ball->update(ball->GetBallVelocityX() + 5, ball->GetBallVelocityY() + 5);
	//			}
	//			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() < 0) {
	//				ball->update(ball->GetBallVelocityX() - 5, ball->GetBallVelocityY() - 5);
	//			}
	//			if (ball->GetBallVelocityX() > 0 && ball->GetBallVelocityY() < 0) {
	//				ball->update(ball->GetBallVelocityX() + 5, ball->GetBallVelocityY() - 5);
	//			}
	//			if (ball->GetBallVelocityX() < 0 && ball->GetBallVelocityY() > 0) {
	//				ball->update(ball->GetBallVelocityX() - 5, ball->GetBallVelocityY() + 5);
	//			}
	//		}
	//	}
	//	if (bonus->GetType() == safeBottomBonus) {
	//		RectangleShape shape;
	//		shape.setPosition(0, windowHeight-5);
	//		shape.setFillColor(Color::Yellow);
	//		shape.setSize({ windowWidth, 5 });
	//		window->draw(shape);
	//		if (ball->bottom() == windowHeight) {
	//			bonus->IsActive() == false;
	//		}
	//	}
	//	if (bonus->GetType() == stickCarriageBonus) {
	//		if (!IsTouch(*ball, *carriage)) {
	//			return;
	//		}
	//		ball->SetVelocityY(0);
	//		ball->SetVelocityX(carriage->GetVelocityX());
	//		//ball->shape.move({ carriage->GetVelocityX(), 0 });
	//		
	//		float xPlace = ball->getX() - carriage->getX();
	//		if (xPlace > 0){
	//			ball->shape.setPosition({ carriage->getX() + xPlace, windowHeight - 50 - carriageHeight });
	//		}
	//		if (xPlace < 0) {
	//			ball->shape.setPosition({ carriage->getX() - xPlace, windowHeight - 50 - carriageHeight });
	//		}
	//		if (xPlace == 0) {
	//			ball->shape.setPosition({ carriage->getX(), windowHeight - 50 - carriageHeight });
	//		}
	//		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
	//			carriage->SetVelocityX(-carriageVelocity);
	//			ball->SetVelocityX(-carriageVelocity);

	//		}
	//		else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
	//			carriage->SetVelocityX(carriageVelocity);
	//			ball->SetVelocityX(carriageVelocity);

	//		}
	//	}
	//	if (bonus->GetType() == changeWayBonus) {
	//		const int changeTime = rand() % (int)oneBonusTime.asSeconds();
	//		int chageOption = rand() % 3;
	//		ball->shape.setFillColor(Color::Green);
	//		//cout << changeTime << "  " << (int)oneBonusTime.asSeconds() << endl;
	//		if ((int)bonus->GetBonusClock().getElapsedTime().asSeconds() == changeTime) {
	//			if (chageOption == 0) {
	//				ball->shape.move({ -ball->GetBallVelocityX(), -ball->GetBallVelocityY() });
	//				//ball->SetVelocityX(-ball->GetBallVelocityX());
	//				//ball->SetVelocityY(-ball->GetBallVelocityY());

	//			}
	//			if (chageOption == 1) {
	//				ball->shape.move({ -ball->GetBallVelocityX(), ball->GetBallVelocityY() });
	//				//ball->SetVelocityX(ball->GetBallVelocityX());
	//				//ball->SetVelocityY(-ball->GetBallVelocityY());

	//			}
	//			if (chageOption == 2) {
	//				ball->shape.move({ ball->GetBallVelocityX(), -ball->GetBallVelocityY() });
	//				//ball->SetVelocityX(-ball->GetBallVelocityX());
	//				//ball->SetVelocityY(ball->GetBallVelocityY());
	//			}	
	//			bonus->SetActivity(false);
	//			BonusDeactivate(bonus, carriage, ball, gameClock);
	//		}
	//	}
	//}

	
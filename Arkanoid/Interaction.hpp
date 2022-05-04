#pragma once
#include"Ball.hpp"
#include"Carriage.hpp"
#include"Blocks.hpp"
#include"Bonus.hpp"
#include <cmath>

class Interaction {
public:
	template<class T1, class T2> bool IsTouch(T1& first, T2& second) {
		return first.right() >= second.left() && first.left() <= second.right() && first.bottom() >= second.top() && first.top() <= second.bottom();
	}
	 
	void solveCollision(Ball& ball, Carriage& carriage) {
		if (!IsTouch(ball, carriage)) {
			return;
		}
		ball.velocity.y = -ballVelocity;
		if (ball.getX() < carriage.getX()) {
			ball.velocity.x = -ballVelocity;
		}
		else {
			ball.velocity.x = ballVelocity;
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
				ball.velocity.x = -ballVelocity;
			}
			else {
				ball.velocity.x = ballVelocity;
			}
		}
		else {
			if (hitFromTop) {
				ball.velocity.y = -ballVelocity;
			}
			else {
				ball.velocity.y = ballVelocity;
			}
		
		}		
		return block.GetType();
	}

	bool IsActivated(Bonus& bonus, Carriage& carriage, Time startTime) {
		if (!IsTouch(bonus, carriage)) {
			return false;
		}
		else {
			bonus.SetStartTime(startTime);
			return true;
		}
	}

	void BonusActivate(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {
			if (gameClock > bonus.GetStartTime() + oneBonusTime) {
				return;
			}
			cout << "bonus is activated" << endl;
			if (bonus.GetType() == sizeIncreaseBonus) {
				ActivateSizeIncreaseBonus(bonus, carriage, ball, gameClock);
			}
			if (bonus.GetType() == speedDownBonus) {}
			if (bonus.GetType() == safeBottomBonus) {}
			if (bonus.GetType() == stickCarriageBonus) {}
			if (bonus.GetType() == changeWayBonus) {}
	}

	void ActivateSizeIncreaseBonus(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {	
		if (gameClock <= bonus.GetStartTime() + oneBonusTime) {
			carriage.shape.setSize({ carriageWidth * 3, carriageHeight });
		}
		else {
			carriage.shape.setSize({ carriageWidth, carriageHeight });
		}
	};
	void ActivateSpeedDownBonus(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {};
	void ActivateSafeBottomBonus(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {};
	void ActivateStickCarriageBonus(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {};
	void ActivateChangeWayBonus(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {};
	
	void BonusDeactivate(Bonus bonus, Carriage carriage, Ball ball, Time gameClock) {}
};

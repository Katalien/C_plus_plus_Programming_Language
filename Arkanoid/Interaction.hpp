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
	
};
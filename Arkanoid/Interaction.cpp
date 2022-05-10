#include "Interaction.hpp"

void Interaction:: solveCollision(Ball& ball, Carriage& carriage) {
	if (!IsTouch(ball, carriage)) {
		return;
	}
	ball.SetVelocityY(-ballVelocity);
	if (ball.getX() < carriage.getX()) {
		ball.SetVelocityX(-ballVelocity);
	}
	else {
		ball.SetVelocityX(ballVelocity);
	}
}

Type Interaction::solveCollision(Ball& ball, Block& block) {
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
		}
		else {
			ball.SetVelocityX(ballVelocity);
		}
	}
	else {
		if (hitFromTop) {
			ball.SetVelocityY(-ballVelocity);
		}
		else {
			ball.SetVelocityY(ballVelocity);
		}
	}
	return block.GetType();
}

bool Interaction::IsActivated(Bonus* bonus, Carriage* carriage, Time gameTime) {
	if (!IsTouch(*bonus, *carriage)) {
		return false;
	}
	if (IsTouch(*bonus, *carriage)) {
		bonus->GetBonusClock().restart().asSeconds();
		bonus->SetActivity(true);
		return true;
	}
}

void Interaction::BallCarriageMove(Ball* ball, Carriage* carriage) {
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
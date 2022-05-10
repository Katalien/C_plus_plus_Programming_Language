#pragma once
#include "Ball.hpp"
#include "Carriage.hpp"
#include "Blocks.hpp"
#include "Bonus.hpp"
#include "Player.hpp"
#include <cmath>


class Interaction {
public:
	template<class T1, class T2> bool IsTouch(T1& first, T2& second) {
		return first.right() >= second.left() && first.left() <= second.right() && first.bottom() >= second.top() && first.top() <= second.bottom();
	}

	void solveCollision(Ball& ball, Carriage& carriage);
	Type solveCollision(Ball& ball, Block& block);
	bool IsActivated(Bonus* bonus, Carriage* carriage, Time gameTime);
	void BallCarriageMove(Ball* ball, Carriage* carriage);

};
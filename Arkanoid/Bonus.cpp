#pragma once
#include "Bonus.hpp"
#include"Interaction.hpp"
class Interaction;

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
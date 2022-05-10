#pragma once
#include "Bonus.hpp"
#include"Interaction.hpp"
class Interaction;

void NewBlockBonus::BonusActivate() {
	window->draw(block->shape);
	block->update();
	Type blockType = interaction->solveCollision(*ball, *block);
	if (blockType != null) {
		player->SetScore(player->GetScore() + 1);

	}
}
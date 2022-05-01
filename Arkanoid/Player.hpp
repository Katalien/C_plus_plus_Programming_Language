#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player {
public:
	int score = 0;
	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; };
};
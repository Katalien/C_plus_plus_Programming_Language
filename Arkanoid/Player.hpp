#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player {
public:
	int GetScore() { return score; }
	void SetScore(int _score) { score = _score; };
private:
	int score = 0;
};
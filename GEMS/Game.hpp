#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 800 };

class Game {
public:
	void run();

private:
	RenderWindow window{ {windowWidth, windowHeight}, "Gems" };

};
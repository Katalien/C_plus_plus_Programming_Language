#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>


using namespace sf;
sf::Font font;
sf::Text text;
constexpr int tableWidth{ 800 }, tableHeight{ 100 };
constexpr int windowWidth{ 800 }, windowHeight{ 600 };

class Table {
	RectangleShape shape;
	
	
	
	/*Table(float _x, float _y) {
		shape.setPosition(_x, _y);
		shape.setFillColor(Color::Black);
		shape.setSize({ carriageWidth, carriageHeight });
		shape.setOrigin(carriageWidth / 2.f, carriageHeight / 2.f);
	}*/

};
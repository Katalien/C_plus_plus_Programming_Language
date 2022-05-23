#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<math.h>
#include <iostream>
using namespace sf;

class Additional {
public:
	float CountTriangle(Vector2f x1, Vector2f x2, Vector2f x3) {
		return 0.5 * fabs((x2.x - x1.x) * (x3.y - x1.y) - (x3.x - x1.x) * (x2.y - x1.y));
	}

};
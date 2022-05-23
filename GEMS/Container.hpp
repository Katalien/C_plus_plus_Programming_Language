#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Block.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;

class Container {
public:
	typedef enum State {
		empty,
		filled,
	}State; 

	Container() { isEmpty = empty; };

	State CheckIsEmpty() {
		return isEmpty;
	}

	void SetContent(Block* _block) {
		block = _block;
		isEmpty = filled;
	};

	Block* GetContent() {
		return block;
	}

	void SetState(State s) { isEmpty = s; };

private:
	State isEmpty = empty;
	Block* block;

};

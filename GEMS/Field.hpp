#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Block.hpp"
#include "Game.hpp"

constexpr int blocksInRow{ 6 }, blocksCount{36};

using namespace sf;
using std::vector;


class Field {
public:
	
	void CreateBlocks() {
        srand(time(0));

        Color blockColor;
        for (int i = 0; i < blocksInRow; i++) {
            for (int j = 0; j < blocksInRow; j++) {
                int a = rand() % 4;
                Block* block = new Block(  (2 * i + 1) * (sqrt(blockSide * blockSide / 2) + 7),  (2*j + 1) * (sqrt(blockSide * blockSide / 2) + 5));
                blocks.push_back(block);
            }
		}
	}

    vector<Block*> GetBlocks() { return blocks; };

private:
	vector <Block*> blocks;
    
};
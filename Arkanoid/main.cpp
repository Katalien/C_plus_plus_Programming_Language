#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include"Ball.hpp"
#include "Carriage.hpp"
#include "Interaction.hpp"
#include "Blocks.hpp"

using namespace std;
using namespace sf;

//constexpr int windowWidth{ 800 }, windowHeight{ 600 };

int main() {
    
    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Carriage carriage{ windowWidth / 2, windowHeight - 50 };
    Interaction interaction;
    vector<Block> blocks;

    for (int i = 0; i < countBlocksX; i++) {
        for (int j = 0; j < countBlockY; j++) {
            Block blockTmp{ (i + 1) * (blockWidth + 3) + 22, (j + 2) * (blockHeight + 3) };
            blocks.push_back(blockTmp);
        }
    }

    while (true) {
        vector<Block> destroyedBlocks;
        window.clear(Color::Black);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        window.draw(ball.shape);
        window.draw(carriage.shape);
        ball.update();
        carriage.update();
        interaction.solveCollision(ball, carriage);
        for (int i = 0; i < blocks.size(); i++) {
            interaction.solveCollision(ball, blocks[i]);
       }
        
        blocks.erase(remove_if(begin(blocks), end(blocks), [](const Block& _block) {return _block.destroyed;}), end(blocks));
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].shape);
        }
        window.display();
    }

    return 0;
}
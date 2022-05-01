#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include"Ball.hpp"
#include "Carriage.hpp"
#include "Interaction.hpp"
#include "Blocks.hpp"
#include"Player.hpp"
#include"Bonus.hpp"

using namespace std;
using namespace sf;

vector<Block> CreateBlocks();

int main() {
    srand(time(0));
    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Carriage carriage{ windowWidth / 2, windowHeight - 50 };
    Interaction interaction;
    vector<Block> blocks = CreateBlocks();
    vector <Bonus> bonuses;
    Player player;
    int score = 0;
    Bonus bonus;

    while (true) {
        window.clear(Color::Black);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        window.draw(ball.shape);
        window.draw(carriage.shape);
        ball.update();
        carriage.update();
        interaction.solveCollision(ball, carriage);
        for (int i = 0; i < blocks.size(); i++) {
            Type type = interaction.solveCollision(ball, blocks[i]);
            if (type == withBonus) {
                Bonus bonus = { blocks[i].getX(), blocks[i].getY()};
                bonuses.push_back(bonus);
                player.SetScore(player.GetScore() + 5);
                cout << player.GetScore() << endl;
            }
            if (type == speedUp) {
                ball.velocity.x = ball.velocity.x + 5;
                ball.velocity.y = ball.velocity.y + 5;
            }
       }
        for (int i = 0; i < bonuses.size(); i++) {
            window.draw(bonuses.at(i).shape);
            bonuses.at(i).update();
        }
        if (ball.bottom() >= windowHeight) {
            player.SetScore(player.GetScore() - 5);
            cout << player.GetScore() << endl;
        }
        
        
        blocks.erase(remove_if(begin(blocks), end(blocks), [](const Block& _block) {return _block.destroyed;}), end(blocks));
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].shape);
        }
        window.display();
    }

    return 0;
}

vector<Block> CreateBlocks() {
    vector<Block> blocks;
    for (int i = 0; i < countBlocksX; i++) {
        for (int j = 0; j < countBlockY; j++) {
            int tmp = rand() % 4;
            //int tmp = 2;
            if (tmp == 0) {
                Block blockTmp{ (i + 1) * (blockWidth + 3) + 22, (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 1) {
                UnbreakableBlock blockTmp{ (i + 1) * (blockWidth + 3) + 22, (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 2) {
                BlockWithBonus blockTmp{ (i + 1) * (blockWidth + 3) + 22, (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 3) {
                SpeedUpBlock blockTmp{ (i + 1) * (blockWidth + 3) + 22, (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
        }
    }
    return blocks;
};
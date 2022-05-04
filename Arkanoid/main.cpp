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
#include"Window.hpp"
#include<string>

using namespace std;
using namespace sf;

vector<Block> CreateBlocks();
vector<Bonus> CreateBonuses(Block block);

int main() {
    srand(time(0));
    Clock gameClock;
    Time t2 = seconds(10);
    ResultTable table{0, 60};
    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid"};
    window.setFramerateLimit(60);
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Carriage carriage{ windowWidth / 2, windowHeight - 50 };
    Interaction interaction;
    vector<Block> blocks = CreateBlocks();
    vector <Bonus> bonuses;
    Player player;
    Bonus bonus;
    Font font;
    string score;
    font.loadFromFile("arial.ttf");
    Text resultText("0", font);
    Text text("hello", font);
    text.setCharacterSize(45);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setString("Score:");
    
    resultText.setCharacterSize(45);
    resultText.setStyle(sf::Text::Bold);
    resultText.setColor(sf::Color::White);
    resultText.setPosition(windowWidth / 4.f, 5);

    while (true) {
        window.clear(Color::Black);
        window.draw(table.shape);
        // text
        
       
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        window.draw(ball.shape);
        window.draw(carriage.shape);
        window.draw(text);
        ball.update();
        carriage.update();
        interaction.solveCollision(ball, carriage);
     //   cout << player.GetScore() << endl;
        for (int i = 0; i < blocks.size(); i++) {
            Type type = interaction.solveCollision(ball, blocks[i]);
            if (type != null) {
                player.SetScore(player.GetScore() + 1);
            }
            if (type == withBonus) {
                bonuses = CreateBonuses(blocks[i]);
            }
            if (type == speedUp) {
                ball.velocity.x = ball.velocity.x + 5;
                ball.velocity.y = ball.velocity.y + 5;
            }
       }
        for (int i = 0; i < bonuses.size(); i++) {
            window.draw(bonuses.at(i).shape);
            bonuses.at(i).update();
            if (interaction.IsActivated(bonuses.at(i), carriage, gameClock.getElapsedTime()) == true) {
                bonuses.at(i).shape.setFillColor({ 0, 0, 0, 0 });
            }
            
        }
        if (ball.bottom() == windowHeight) {
            player.SetScore(player.GetScore() - 1);
            
        }       
        blocks.erase(remove_if(begin(blocks), end(blocks), [](const Block& _block) {return _block.destroyed;}), end(blocks));
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].shape);
        }
        score = to_string(player.GetScore());
        resultText.setString(score);
        window.draw(text);
        window.draw(resultText);

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
                Block blockTmp{ (i + 1) * (blockWidth + 3) + 22, 50 + (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 1) {
                UnbreakableBlock blockTmp{ (i + 1) * (blockWidth + 3) + 22, 50 + (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 2) {
                BlockWithBonus blockTmp{ (i + 1) * (blockWidth + 3) + 22, 50 + (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
            if (tmp == 3) {
                SpeedUpBlock blockTmp{ (i + 1) * (blockWidth + 3) + 22, 50 +  (j + 2) * (blockHeight + 3) };
                blocks.push_back(blockTmp);
            }
        }
    }
    return blocks;
};

vector<Bonus> CreateBonuses( Block block) {
    vector <Bonus> bonuses;
    int tmp = rand() % 5;
    if (tmp == 0) {
        SizeIncreaseBonus bonus { block.getX(), block.getY() };
        bonuses.push_back(bonus);
    }
    if (tmp == 1) {
        SpeedDownBonus bonus{ block.getX(), block.getY() };
        bonuses.push_back(bonus);
    }
    if (tmp == 2) {
        SafeBottomBonus bonus{ block.getX(), block.getY() };
        bonuses.push_back(bonus);
    }
    if (tmp == 3) {
        StickCarriageBonus bonus{ block.getX(), block.getY() };
        bonuses.push_back(bonus);
    }
    if (tmp == 4) {
        ChangeWayBonus bonus{ block.getX(), block.getY() };
        bonuses.push_back(bonus);
    }
    return bonuses;
}
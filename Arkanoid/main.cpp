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

class Interaction;

using namespace std;
using namespace sf;

vector<Block> CreateBlocks();
Bonus* CreateBonuses(Block block, Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Interaction* interaction);

int main() {
    srand(time(0));
    Clock gameClock;
    Time t2 = seconds(10);
    ResultTable table{0, 60};
    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid"};
    //window.setFramerateLimit(60);
    Ball ball{ windowWidth / 2, windowHeight / 2 };
    Carriage carriage{ windowWidth / 2, windowHeight - 50 };
    Interaction interaction;
    vector<Block> blocks = CreateBlocks();
    vector <Bonus*> bonuses;
    vector <Bonus*> activeBonuses;
    Player player;
    bool onlyUnbreakable = true;
    Bonus bonus;
    Font font;
    string score;
    bool isSafe = false;
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

    Text finishText("GAME OVER", font);
    finishText.setCharacterSize(100);
    finishText.setStyle(Text::Bold);
    finishText.setColor(Color::White);
    finishText.setPosition(windowWidth/9.f, windowHeight/3.f);
    Text endText;
    endText.setFont(font);
    endText.setCharacterSize(50);
    endText.setStyle(Text::Bold);
    endText.setColor(Color::White);
    endText.setPosition(windowWidth / 3.5,  windowHeight / 2.f);

    Text spaceText("Press Escape to close the window", font);
    spaceText.setCharacterSize(40);
    spaceText.setStyle(Text::Bold);
    spaceText.setColor(Color::Yellow);
    spaceText.setPosition(windowWidth / 7.f, 3.f * windowHeight / 4.f);

    while (true) {
        window.clear(Color::Black);
        window.draw(table.shape);      
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        window.draw(ball.shape);
        window.draw(carriage.shape);
        window.draw(text);
        ball.update(ball.GetBallVelocityX(), ball.GetBallVelocityY());
        carriage.update();
        interaction.solveCollision(ball, carriage);

        for (int i = 0; i < blocks.size(); i++) {
            Type type = interaction.solveCollision(ball, blocks[i]);
            if (type != null && type!=unbreakable) {
                player.SetScore(player.GetScore() + 1);
            }
            if (type == withBonus) {
                Bonus* tmpBonus = CreateBonuses(blocks[i], &carriage, &ball, &window, &player, &interaction);
                bonuses.push_back(tmpBonus);
            }
            if (type == speedUp) {
                ball.SetVelocityX(ballVelocity);
                ball.SetVelocityY(ballVelocity + 0.2);
            }
            if (blocks[i].GetType() != unbreakable) {
                onlyUnbreakable = false;
            }
                //onlyUnbreakable = true;
        }
     
        for (int i = 0; i < bonuses.size(); i++) {
            window.draw(bonuses.at(i)->shape);
            bonuses.at(i)->update();
            if (interaction.IsActivated(bonuses.at(i), &carriage, gameClock.getElapsedTime()) == true ) {
                bonuses.at(i)->shape.setFillColor({ 0, 0, 0, 0 });
                activeBonuses.push_back(bonuses.at(i));
                bonuses.erase(bonuses.begin() + i);
                continue;
            }
            if (interaction.IsActivated(bonuses.at(i), &carriage, gameClock.getElapsedTime()) == false && bonuses.at(i)->getY() >= windowHeight) {
                bonuses.erase(bonuses.begin() + i);
            }
        }
        if (ball.bottom() >= windowHeight) {
            isSafe = false;
            for (int i = 0; i < activeBonuses.size(); i++) {
                if (activeBonuses.at(i)->GetType() == safeBottomBonus) {
                    //activeBonuses.at(i)->SetActivity(false);
                    isSafe = true;
                }
            }
            if (!isSafe) {
                player.SetScore(player.GetScore() - 1);
            }
        }
        for (int i = 0; i < activeBonuses.size(); i++) {
            activeBonuses.at(i)->BonusCheck( &carriage, &ball, &window, &player, gameClock.getElapsedTime());
            if (activeBonuses.at(i)->IsActive() == false) {
                activeBonuses.erase(activeBonuses.begin() + i);
            }
        }
             
        blocks.erase(remove_if(begin(blocks), end(blocks), [](const Block& _block) {return _block.destroyed;}), end(blocks));
        for (int i = 0; i < blocks.size(); i++) {
            window.draw(blocks[i].shape);
        }
        score = to_string(player.GetScore());
        resultText.setString(score);
        window.draw(text);
        window.draw(resultText);
        if (onlyUnbreakable == true) {
            ball.SetVelocityX(0.f);
            ball.SetVelocityY(0.f);
            carriage.SetVelocityX(0.f);
            carriage.SetVelocityY(0.f);

            window.draw(finishText);
            if (player.GetScore() > 0) {
                endText.setString("You've won");
            }
            if (player.GetScore() < 0) {
                endText.setString("You've lose");
            }
            else {
                endText.setString("Your score: 0");
            }
            window.draw(endText);
            window.draw(spaceText);
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
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

Bonus* CreateBonuses( Block block, Carriage* carriage, Ball* ball, RenderWindow* window, Player* player, Interaction* interaction) {
    vector <Bonus*> bonuses;

      int tmp = rand() % 6;
   //  int tmp = 4;
    if (tmp == 0) {
        Bonus* bonus = new SizeIncreaseBonus{ block.getX(), block.getY(), carriage };
        bonuses.push_back(bonus);
        return bonus;
    }
    if (tmp == 1) {
        Bonus* bonus = new SpeedUpBonus{ block.getX(), block.getY(), ball};
        bonuses.push_back(bonus);
        return bonus;
    }
    if (tmp == 2) {
        Bonus* bonus = new SafeBottomBonus{ block.getX(), block.getY(), window, ball };
        bonuses.push_back(bonus);
        return bonus;
    }
    if (tmp == 3) {
        Bonus* bonus = new StickCarriageBonus{ block.getX(), block.getY(), carriage, ball};
        bonuses.push_back(bonus);
        return bonus;
    }
    if (tmp == 4) {
        Bonus* bonus = new ChangeWayBonus { block.getX(), block.getY(), ball };
        bonuses.push_back(bonus);
        return bonus;
    }
    if (tmp == 5) {
        Bonus* bonus = new NewBlockBonus{ block.getX(), block.getY(),ball, window, player, interaction};
        bonuses.push_back(bonus);
        return bonus;
    }
}
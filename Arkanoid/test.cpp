//#pragma once
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include<iostream>
//#include<vector>
//#include"Ball.hpp"
//#include "Carriage.hpp"
//#include "Interaction.hpp"
//#include "Blocks.hpp"
//#include"Player.hpp"
//#include"Bonus.hpp"
//#pragma warning(disable:4996)
//
//using namespace std;
//using namespace sf;
//
//
//int main() {
//    sf::Font font;
//    font.loadFromFile("arial.ttf");
//    // Создаём текст
//    sf::Text text("hello", font);
//    text.setCharacterSize(30);
//    text.setStyle(sf::Text::Bold);
//    text.setColor(sf::Color::Red);
//    text.setString("Score:");//задает строку тексту
//    
//    
//
//
//
//  
//    RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
//    window.setFramerateLimit(60);
//    Ball ball{ windowWidth / 2, windowHeight / 2 };
//    Carriage carriage{ windowWidth / 2, windowHeight - 50 };
//    Interaction interaction;
//    vector <Bonus> bonuses;
//    Player player;
//    int score = 0;
//    Bonus bonus;
//    int i = 3;
//    uint8_t transparensy = 255;
//    while (true) {
//        window.clear(Color::Black);
//        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
//        window.draw(ball.shape);
//        window.draw(carriage.shape);
//        window.draw(text);//рисую этот текст
//        ball.update();
//        carriage.update();
//        interaction.solveCollision(ball, carriage);
//        if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
//            transparensy++;
//            Color tmpColor = { 0, 0, 0, transparensy };
//            Color newColor = carriage.shape.getFillColor() - tmpColor;
//            carriage.shape.setFillColor(newColor);
//            cout << (int)transparensy<< endl;
//            i++;
//        }
//        window.display();
//    }
//
//    return 0;
//}
//

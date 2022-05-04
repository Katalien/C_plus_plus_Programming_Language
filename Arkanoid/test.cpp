//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include<string>
//#include<iostream>
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
//#include"Window.hpp"
//#include<string>
//#pragma warning(disable:4996)
//
//using namespace std;
//using namespace sf;
//using std::string;
//
//
//int main() {
//    srand(time(0));
//
//RenderWindow window{ {windowWidth, windowHeight}, "Arkanoid" };
//window.setFramerateLimit(60);
//Ball ball{ windowWidth / 2, windowHeight / 2 };
//Carriage carriage{ windowWidth / 2, windowHeight - 50 };
//Interaction interaction;
//
//vector <Bonus> bonuses;
//Player player;
//Bonus bonus;
//Font font;
//string score;
//font.loadFromFile("arial.ttf");
//Text resultText("0", font);
//Text text("hello", font);
//text.setCharacterSize(45);
//text.setStyle(sf::Text::Bold);
//text.setColor(sf::Color::White);
//text.setString("Score:");
//vector<Clock> clocks;
//Time t2 = seconds(500);
//Clock clock;
//
//while(true) {
//    window.clear(Color::Black);
//            
//            // text
//            
//           
//            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
//            window.draw(ball.shape);
//            window.draw(carriage.shape);
//            window.draw(text);
//            ball.update();
//            carriage.update();
//            cout << clock.getElapsedTime().asSeconds() << endl;
//            if (clock.getElapsedTime().asSeconds() < 5) {
//                carriage.shape.setSize({ carriageWidth * 2, carriageHeight * 2 });
//            }
//            else {
//                carriage.shape.setSize({ carriageWidth , carriageHeight });
//            }
//            score = to_string(player.GetScore());
//            resultText.setString(score);
//            window.draw(text);
//            window.draw(resultText);
//    
//            window.display();
//    
//    
//    
//        }
//
//return 0;
//}
//

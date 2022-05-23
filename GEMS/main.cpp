#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<math.h>
#include<string>
#include "Game.hpp"
#include "Block.hpp"
#include "Field.hpp"

using namespace sf;
using namespace std;

int main() {
    srand(time(0));
    RenderWindow window{ {windowWidth, windowHeight}, "GEMS" };
    Field field;
    Mouse mouse;
    Event event;
    Block* firstBlock = new Block;
    Block* secondBlock = new Block;
    Block* tmpBlock = new Block;
    Container* firstCont = new Container;
    Container* secondCont = new Container;

    double ballr = 5;
    vector<CircleShape> shapes;

        
  
    Vector2i coord;
    bool isChosen = false;
    while (true) {
        window.clear(Color::Black);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { break; };
        
        
            for (int i = 0; i < blocksCount; ++i) {
                window.draw(field.GetBlockFromContainer(i)->shape);     
            }
        
            //mouse event
            while (window.pollEvent(event)) {
                if (event.type == Event::MouseButtonPressed) {
                    if (event.key.code == Mouse::Left) {
                        // if clicked remember coordinates
                        coord = mouse.getPosition(window);
                        // check blocks
                        for (int i = 0; i < blocksCount; ++i) {
                            isChosen = field.GetBlock(i)->IsActivated(coord.x, coord.y);
                            // choose two blocks to swap
                            if (isChosen) {
                                if (!firstBlock->IsChosen()) {
                                    firstBlock = field.GetBlock(i);
                                    firstBlock->SetState(true);
                                    cout << "YOU'VE CHOSEN 1 BLOCK" << endl;
                                }
                                else {
                                    secondBlock = field.GetBlock(i);
                                    secondBlock->SetState(true);
                                    cout << "YOU'VE CHOSEN 2 BLOCK" << endl;
                                }
                                
                                break;
                            }
                        }
                    }
                }
            }
            // if I've chosen two blocks - swap them
            if (firstBlock->IsChosen() == true && secondBlock->IsChosen() == true  && firstBlock != secondBlock) {
              //  cout << firstBlock << " " << secondBlock << " " << field.GetBlockFromContainer(1) << endl;
              // cout << firstBlock->GetContainer() << " " << secondBlock->GetContainer() << " " << field.GetBlockFromContainer(1)->GetContainer() << endl;
                field.SwapBlocks(firstBlock, secondBlock);   
               
                firstBlock->SetState(false);
                secondBlock->SetState(false);
            }
            
           
            
        window.display();
    }
    return 0;
}
	
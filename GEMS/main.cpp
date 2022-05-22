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
    RenderWindow window{ {windowWidth, windowHeight}, "Gems" };
    Field field;
    Block* block = new Block{ blockSide , blockSide };
    double x = sqrt(blockSide * blockSide / 2);
    cout << x;
    Block* testBlock = new Block(x, x);
    field.CreateBlocks();
    vector <Block*> blocks = field.GetBlocks();
    while (true) {
        window.clear(Color::Black);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { break; };
        
        //window.draw(testBlock->shape);
        for (auto item : blocks) {
            window.draw(item->shape);
        }
        window.display();
    }
    return 0;
}
	
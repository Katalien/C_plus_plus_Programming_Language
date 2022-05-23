#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Block.hpp"
#include "Game.hpp"
#include "Container.hpp"

constexpr int blocksInRow{ 6 }, blocksCount{36};

using namespace sf;
using std::vector;
using std::array;

class Field {
public:
    Field() {
        CreateBlocks();
        for (int i = 0; i < blocksCount; ++i) {
            containers[i].SetContent(blocks.at(i));
            blocks.at(i)->SetContainer(&containers[i]);
        }
    }

	void CreateBlocks() {
        srand(time(0));
        Color blockColor;
        for (int i = 0; i < blocksInRow; i++) {
            for (int j = 0; j < blocksInRow; j++) {
                int a = rand() % 4;
                Block* block = new Block(  (2 * i + 1) * (sqrt(blockSide * blockSide / 2) + 6), 5 + (2*j + 1) * (sqrt(blockSide * blockSide / 2) + 6));
                blocks.push_back(block);
            }
		}
	}

    vector<Block*> GetBlocks() { return blocks; };

    Block* GetBlock(int i) { return blocks.at(i); }

    Block* GetBlockFromContainer(int i) { 
        return containers[i].GetContent(); 
    };


    void SwapBlocks(Block* first, Block* second) {
        if (second == first) {
            return;
        }
        Container* firstCont = first->GetContainer();
        Container* secondCont = second->GetContainer();
        Vector2f firstCoord = first->shape.getPosition();
        Vector2f secondCoord = second->shape.getPosition();
        firstCont->SetContent(second);
        secondCont->SetContent(first);
        first->shape.setPosition(secondCoord);
        second->shape.setPosition(firstCoord);
        first->SetContainer(secondCont);
        second->SetContainer(firstCont);
    }


    bool CheckDownConteiner(int i) {
        if (containers[i + 1].CheckIsEmpty() == Container::State::filled){
            return true; 
        }
        else {
            return false;
        }
    }

    bool CheckUpConteiner(int i) {
        if (containers[i - 1].CheckIsEmpty() == Container::State::filled) {
            return true;
        }
        else {
            return false;
        }
    }

    bool CheckLeftConteiner(int i) {
        if (containers[i - blocksInRow].CheckIsEmpty() == Container::State::filled) {
            return true;
        }
        else {
            return false;
        }
    }

    bool CheckRightConteiner(int i) {
        if (containers[i + blocksInRow].CheckIsEmpty() == Container::State::filled) {
            return true;
        }
        else {
            return false;
        }
    }

private:
	vector <Block*> blocks;
    Container* containers = new Container[blocksCount];
   // vector<Container*> containers;
};
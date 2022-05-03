#pragma once
#pragma warning(disable:4996)

using namespace std;
using namespace sf;

constexpr int lineWidth{ 800 }, lineHeight{ 5 };
constexpr int windowWidth{ 800 }, windowHeight{ 800 };

class ResultTable {
public:
    Font font;
    Text text;
    Text resultText;
    RectangleShape shape;

    ResultTable(float _x, float _y){
        shape.setPosition(_x, _y);
        shape.setFillColor(Color::White);
        shape.setSize({ windowWidth*2, lineHeight });
        shape.setOrigin(lineWidth / 2.f, lineHeight / 2.f);
    }

};
//

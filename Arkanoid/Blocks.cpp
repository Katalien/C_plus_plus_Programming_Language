#include "Blocks.hpp"

Block::Block(float _x, float _y) {
	SetType(normal);
	shape.setFillColor(Color::Yellow);
	shape.setSize({ blockWidth, blockHeight });
	shape.setPosition(_x, _y);
	shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
	lives = 3;
}
void Block::changeOpacity() {
	if (GetType() != unbreakable) {
		uint8_t transparensy = shape.getFillColor().a + 85;
		Color tmpColor = { 0, 0, 0, transparensy };
		Color newColor = shape.getFillColor() - tmpColor;
		shape.setFillColor(newColor);
	}
}

UnbreakableBlock::UnbreakableBlock(float _x, float _y) : Block(_x, _y) {
	shape.setFillColor(Color::Red);
	SetType(unbreakable);
}

BlockWithBonus::BlockWithBonus(float _x, float _y) : Block(_x, _y) {
	shape.setFillColor(Color::Cyan);
	SetBonus(rand() % 5);
	SetType(withBonus);
}

SpeedUpBlock::SpeedUpBlock(float _x, float _y) : Block(_x, _y) {
	shape.setFillColor(Color::Magenta);
	SetType(speedUp);
}


MovingBlock::MovingBlock(float _x, float _y) : Block(_x, _y) {
	shape.setFillColor(Color::Green);
	SetType(movingBlock);
	velocity.x = moveBlockVelocity;
	velocity.y = 0;

}
void MovingBlock:: update() {
	shape.move({ moveBlockVelocity, 0 });
	if (left() <= 0) {
		//shape.move({ moveBlockVelocity, 0 });
		velocity.x = moveBlockVelocity;
	}
	else if (right() >= windowWidth) {
		//shape.move({ -moveBlockVelocity, 0 });
		velocity.x = -2 * moveBlockVelocity;
	}
	shape.move(velocity);
}
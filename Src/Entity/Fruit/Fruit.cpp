#include "Fruit.h"
#include "..\..\Logic\Logic.h"

Fruit::Fruit(int calories, int gridX, int gridY) : Entity()
{
	_calories = calories;
	_tamX = _tamY = calories;
	_color = Color::Amarillo;
	_posX = gridX;
	_posY = gridY;
	
	for (int i = 0; i < _tamX; i++)
		for (int j = 0; j < _tamY; j++)
			Logic::getCEngine()->AddEntity(_posX + i, _posY + j, EntityType::Fruits, this);
}

Fruit::~Fruit()
{
	for (int i = 0; i < _tamX; i++)
		for (int j = 0; j < _tamY; j++)
			Logic::getCEngine()->RemoveEntity(_posX+i,_posY+j);
}


void Fruit::draw(RenderThread* t) {
	for (int i = 0; i < _calories; i++)
		for (int j = 0; j < _calories; j++) {
			t->enqDCell(_posX + i, _posY + j, _color);
		}
}

bool Fruit::update() {
	return false;
}

void Fruit::init() {
}
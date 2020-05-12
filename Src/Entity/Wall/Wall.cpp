#include "Wall.h"
#include "..\..\Logic\Logic.h"

Wall::Wall(int gridX, int gridY,int tamX, int tamY, Color color): Entity()
{
	_color = color;
	_posX = gridX;
	_posY = gridY;
	_tamX = tamX;
	_tamY = tamY;
	for (int i = 0; i < _tamX; i++)
		for (int j = 0; j < _tamY; j++)
			Logic::getCEngine()->AddEntity(_posX+i, _posY+j, EntityType::Dead, this);
}

Wall::~Wall()
{
	Logic::getCEngine()->RemoveEntity(_posX, _posY);
}

void Wall::draw(RenderThread * t)
{
	t->enqDLine(_posX, _posY, _tamY, _tamX, _color);
}

bool Wall::update()
{
	return false;
}

void Wall::init()
{
}
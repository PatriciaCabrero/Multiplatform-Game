#pragma once
#include "..\Entity.h"

//Entidad muro
class Wall: public Entity
{
public:
	Wall(int gridX, int gridY, int tamX, int tamY, Color color);
	~Wall();
	virtual void draw(RenderThread* t);

	virtual bool update();
	virtual void init();
};
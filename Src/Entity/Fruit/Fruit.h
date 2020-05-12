#pragma once
#include "..\Entity.h"

//Entidad fruta
//Su tamañ depende de las calorías que se le asignen
class Fruit :
	public Entity {
public:
	Fruit(int calories, int gridX, int gridY);
	~Fruit();
	
	virtual void init();
	virtual void draw(RenderThread* t);
	virtual bool update();

	int getCal() { return _calories; }

private:
	int _calories;
};
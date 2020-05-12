#pragma once
#include "..\Renderer\Renderer.h"
#include "..\Thread\RenderThread.h"

//Clase virtual de la que heredan todas las entidades del juego
//Lleva su posición (en tablero, no en píxeles), su tamaño, su color
//y las funciones draw(), init() y update()
class Entity {
public:
	Entity(){};
	virtual ~Entity() {};
	virtual void init() = 0;
	virtual void draw(RenderThread* t) {};
	
	//Update de las entidades devuelve true si necesita destruir la entidad
	virtual bool update() = 0;

	int getY() { return _posY; }
	int getX() { return _posX; }

	Color getColor() { return _color; }


	int getTamX() { return _tamX; }
	int getTamY() { return _tamY; }

protected:

	//El renderer de cada entidad encola el comando al renderthread
	void drawRectangle(RenderThread* t){
		t->enqDLine(_posX, _posY, _tamY, _tamX, _color);
	}

	int _posX =0, _posY= 0;
	int _tamX =0, _tamY = 0;
	Color _color;

};

//Clase que necesita Snake para sus celdas
class Cell :
	public Entity {
public:
	Cell(int gridX, int gridY, Color color) : Entity() {
		_posX = gridX; _posY = gridY;
		_color = color;
	}

	virtual ~Cell() {}

	//Cada cell se dibuja individualmente
	virtual void draw(RenderThread* t) {
		t->enqDCell(_posX, _posY, _color);
	}

	virtual bool update() { return true; }
	virtual void init() {}
};

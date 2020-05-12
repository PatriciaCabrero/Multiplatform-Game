#pragma once
#include "..\Entity.h"
#include <list>
#include "..\Scoreboard\Scoreboard.h"

//Estados posibles de cada Snake
enum State{INIT, ACTIVE, DISCONECTED, DESTROY };

//Entidad Snake
class Snake :
	public Entity {
public:
	Snake(int32_t userID);
	~Snake();
	virtual void draw(RenderThread* t);
	virtual bool update();
	virtual void init();
	void setDirection(direction dir) { _dir = dir; };

private:
	//Crece las calorias dadas por la fruta comida
	void grow(int calorias);
	//Hace avanzar a la serpiente
	void moveSnake();

	direction _dir;
	//Lista de celdas que componen a la serpiente
	list<Cell> _cells;
	int _numCells;
	float lastUpdate;
	//Cada serpiente lleva el ID del usuario que la lleva 
	int32_t _userID;
	State _state;

	//Cada serpiente lleva el objeto que pinta su 
	//puntuación en pantalla
	Scoreboard* _score;
};
#pragma once
#include "..\Entity\Entity.h"
#include "..\Config.h"
enum EntityType
{
	Fruits, Dead, Empty
};

//Cada celda del 'tablero' tiene un CollisionInfo
struct CollisionInfo {
	Entity* _entity;
	EntityType _type;
};

//Se instanciará en la lógica y llevará el control del
//'tablero' de juego
class CollisionEngine
{
public:
	CollisionEngine();
	~CollisionEngine();
	void init();
	void AddEntity(int x, int y, EntityType type, Entity* entity);
	void RemoveEntity(int x, int y);
	CollisionInfo GetEntity(int x, int y);
private:
	CollisionInfo _grid[X_CELLS][Y_CELLS];
};

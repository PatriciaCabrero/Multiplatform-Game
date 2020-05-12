#include "CollisionEngine.h"
CollisionEngine::CollisionEngine()
{
}

CollisionEngine::~CollisionEngine()
{
}

void CollisionEngine::init()
{
	for (int i = 0; i < X_CELLS; i++)
	{
		for (int j = 0; j < Y_CELLS; j++)
		{
			_grid[i][j] = CollisionInfo{ nullptr, EntityType::Empty };
		}
	}
}

void CollisionEngine::AddEntity(int x, int y, EntityType type, Entity * entity)
{
	_grid[x][y]._entity = entity;
	_grid[x][y]._type = type;
}

void CollisionEngine::RemoveEntity(int x, int y)
{
	_grid[x][y]._entity = nullptr;
	_grid[x][y]._type = EntityType::Empty;
}

CollisionInfo CollisionEngine::GetEntity(int x, int y)
{
	return _grid[x][y];
}

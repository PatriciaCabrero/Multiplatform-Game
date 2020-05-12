#include "Logic.h"
#include "..\Thread\RenderThread.h"
#include "..\Entity/Fruit/Fruit.h"
#include "..\Entity/Snake/Snake.h"
#include "..\Entity/Wall/Wall.h"
#include "..\Input\UserManager.h"


list<Entity*> Logic::_entitys = list<Entity*>();
list<Entity*> Logic::_addEntitys = list<Entity*>(); 
list<Entity*> Logic::_rmEntitys = list<Entity*>();
bool Logic::_restart;
CollisionEngine Logic::_cEngine;
map<Color, direction> Logic::direcciones;

list<User*>  Logic::_newUsers;

void Logic::Release()
{
	for (std::list<Entity*>::const_iterator it = _entitys.cbegin(); it != _entitys.cend(); ++it) {
		delete *it;
	}
	_entitys.clear();
	_newUsers.clear();
}

void Logic::init()
{
	_restart = false;
	initMandosDirecciones();
	_cEngine.init();
	AddWalls();
	
	pair<int, int>npos = RandomPosTablero(4);

	NewFruit();
}

void Logic::SetRestart(bool restart)
{
	_restart = restart;
}

void Logic::Restart() {
	Release();
	init();
	UserManager::GetCurrentUsers(_newUsers);
	for (std::list<User*>::iterator it = _newUsers.begin(); it != _newUsers.end(); ++it) {
		(*it)->input->setDirInput((int)(*it)->color);
		newSnake(*it);
	}
}

void Logic::Tick()
{
	//Gestión de los nuevos usuarios
	UserManager::GetNewLoggedInUsers(_newUsers);
	for (std::list<User*>::iterator it = _newUsers.begin(); it != _newUsers.end(); ++it){
		newSnake(*it);
	}

	//Update entidades
	for (std::list<Entity*>::const_iterator it = _entitys.cbegin(); it != _entitys.cend(); ++it) {
		if ((*it)->update())
			RemoveEntity((*it));
	}

	//Borra entidades
	for (std::list<Entity*>::const_iterator it = _rmEntitys.cbegin(); it != _rmEntitys.cend(); ++it) {
		_entitys.remove(*it);
		delete *it;
	}
	_rmEntitys.clear();

	//Añade entidades
	for (std::list<Entity*>::const_iterator it = _addEntitys.cbegin(); it != _addEntitys.cend(); ++it) {
		_entitys.push_back(*it);
	}
	_addEntitys.clear();
}

void Logic::Render(RenderThread* rT)
{
	//Clear
	rT->enqClear(Color::Negro);

	//Render
	int i = 0;
	for (std::list<Entity*>::const_iterator it = _entitys.cbegin(); it != _entitys.cend(); ++it) {
		(*it)->draw(rT);
		i++;
	}

	//Present
	rT->enqEndFrame();
}
void Logic::NewFruit(CollisionInfo* cInfo) {
	if(cInfo!=nullptr)
		RemoveEntity(cInfo->_entity);

	int calorias = rand() % CALORIES + 1;
	pair<int, int> npos = RandomPosTablero(calorias);
	AddEntity(new Fruit(calorias, npos.first, npos.second));
}

float Logic::GetDeltaTime()
{
	return (float)clock() / TIME;
}

Snake* Logic::newSnake(User* user)
{
	Snake* snk = new Snake(user->userID);
	AddEntity(snk);
	return snk;
}

void Logic::AddEntity(Entity * entity)
{
	_addEntitys.push_back(entity);
}


void Logic::RemoveEntity(Entity * entity)
{
	_rmEntitys.push_back(entity);
}

bool Logic::GetRestart()
{
	return _restart;
}

void Logic::AddWalls()
{
	//BORDES
	AddEntity(new Wall(2, 2, X_CELLS - 4, 2, Color::Blanco));
	AddEntity(new Wall(2, Y_CELLS - 4, X_CELLS - 4, 2, Color::Blanco));

	AddEntity(new Wall(2, 4, 2, Y_CELLS - 6, Color::Blanco));
	AddEntity(new Wall(X_CELLS - 4, 4, 2, Y_CELLS - 6, Color::Blanco));
}

void Logic::initMandosDirecciones() {
	direcciones.emplace(Color::Azul, direction::LEFT);
	direcciones.emplace(Color::Rojo, direction::UP);
	direcciones.emplace(Color::Verde, direction::RIGHT);
	direcciones.emplace(Color::Rosa, direction::DOWN);
}
pair<int, int> Logic::RandomPosTablero(int tam) {
	pair<int, int> npos;
	bool empty = true;
	do{
		empty = true;
		npos = { (rand() % (X_CELLS-8))+4, (rand() % (Y_CELLS-8))+4 };
		for (int i = 0; i < tam && empty; i++)
			for (int j= 0; j < tam && empty; j++)
				empty = _cEngine.GetEntity(npos.first + i, npos.second + j)._type == EntityType::Empty;
	} while (!empty);

	return npos;
}
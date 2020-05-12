#pragma once
#include "..\Entity\Entity.h"
#include <list>
#include "..\CollisionEngine\CollisionEngine.h"
#include "..\Input\UserManager.h"

#include <map>
using namespace std;
class Snake;

//Clase estática que lleva el tick principal del juego
//Gestiona las entidades y sus colisiones
//Envía el mensaje de dibujado al RenderThread
class Logic
{
public:
	static void init();
	static void Release();
	static void Tick();
	static void Render(RenderThread * rT);
	static float GetDeltaTime();

	static void NewFruit(CollisionInfo * cInfo = nullptr);
	static CollisionEngine* getCEngine() { return &_cEngine; };
	static Snake* newSnake(User* user);
	static void RemoveEntity(Entity * entity);

	static bool GetRestart();
	static void SetRestart(bool restart);
	static void Restart();
	
private:
	static void AddEntity(Entity* entity);
	static void AddWalls();
	static void initMandosDirecciones();

	static pair<int, int> RandomPosTablero(int tam);

	//Entidades activas, entidades a añadir y entidades a borrar
	static list<Entity*> _entitys, _addEntitys, _rmEntitys;

	static map<Color, direction> direcciones; //Asigna a cada color una dirección predeterminada
	static CollisionEngine _cEngine;

	static list<User*> _newUsers;
	static bool _restart;
};
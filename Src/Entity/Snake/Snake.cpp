#include "Snake.h"
#include "..\..\Logic\Logic.h"
#include "..\Fruit\Fruit.h"
#include "..\..\Input\Input.h"
#include <string>


static const pair<int, int> dirs[4] = { make_pair(-1,0),make_pair(0,-1),
	make_pair(1,0),make_pair(0,1) };

Snake::Snake(int32_t userID) : Entity()
{
	_state = INIT;
	_userID = userID;
	_numCells = TAM_SNAKE;

	/*Al construir una serpiente se le asocia el color 
	y la dirección inicial en función del usuario dado*/
	User* u = UserManager::getConnectedUserById(userID);
	_dir = Input::getUserInput(userID)->getDir();
	_color = UserManager::GetUserColor(userID);

	_posX = (X_CELLS / 2) + dirs[_dir].first * DIST_SEG;
	_posY = (Y_CELLS / 2) + dirs[_dir].second * DIST_SEG;

	_score = new Scoreboard(_color);

	//Trata de inicializar la serpiente en una posición segura
	//si no puede hacerlo, espera
	init();

}

Snake::~Snake()
{
	for (std::list<Cell>::iterator it = _cells.begin(); it != _cells.end(); ++it) {
		Logic::getCEngine()->RemoveEntity(it->getX(), it->getY());
	}
	delete _score;
}

//Dibuja la serpiente y su marcador
void Snake::draw(RenderThread* t) {
	for (std::list<Cell>::iterator it = _cells.begin(); it != _cells.end(); ++it) {
		it->draw(t);
	}

	string aux = to_string((_numCells%1000)-TAM_SNAKE);
	for (int i = 0; i < aux.size(); i++)
	{
		_score->setScore(aux[i]-48);
		_score->draw(t,i);
	}

}

//Comprueba colisiones y si su usuario se ha ido y
//actúa en función de ello
bool Snake::update() {
	if (_state == INIT) {
		init();
		return false;
	}
	else if (_state == ACTIVE) {

		//Compruebo si se ha desconectado el mando
		User* _uLogout = UserManager::GetLoggedOutUsersById(_userID);
		if (_uLogout != nullptr) {
			_state = DISCONECTED;
		}
		else {
			//UPDATE
			if (Logic::GetDeltaTime() - lastUpdate >= 1000 / SPEED) { // Se calcula en milisegundos, si pongo speed 10 se moverá 10celdas/s
				_dir = Input::getUserInput(_userID)->getDir();

				lastUpdate = Logic::GetDeltaTime();
				pair <int, int> nPos = { _cells.front().getX() + dirs[_dir].first, _cells.front().getY() + dirs[_dir].second };
				CollisionInfo cInfo = Logic::getCEngine()->GetEntity(nPos.first, nPos.second);

				//Compruebo si puedo avanzar
				switch (cInfo._type)
				{
				case EntityType::Dead:
					Logic::SetRestart(true);
					return true;
					break;
				case EntityType::Fruits:
					grow(((Fruit*)(cInfo._entity))->getCal());
					Logic::NewFruit(&cInfo);
				case EntityType::Empty:
					moveSnake();
					return false;
					break;
				default:
					return false;
					break;
				}
			}
		}
	}
	//Va borrando progresivamente las celdas
	else if (_state == DISCONECTED) {
		if (_cells.empty())
			return true;
		else {
			//Borra la cola para avanzar
			Cell oldCell = _cells.back();
			Logic::getCEngine()->RemoveEntity(oldCell.getX(), oldCell.getY());
			_cells.pop_back();
		}
	}
	return false;
}

void Snake::init() {
	bool empty = true;
	int i = -DIST_SEG;
	int j = -DIST_SEG;
	while (i < DIST_SEG && empty) {
		while (j < DIST_SEG && empty) {
			empty = Logic::getCEngine()->GetEntity(_posX + i, _posY)._type == EntityType::Empty;
			j++;
		}
		i++;
	}
	if (empty) {
		_state = ACTIVE;
		for (int i = 0; i < _numCells; i++)
		{
			_cells.emplace_back(Cell(_posX, _posY, _color));

		}
		Logic::getCEngine()->AddEntity(_posX, _posY, EntityType::Dead, this);
		lastUpdate = Logic::GetDeltaTime();
		_score->init();
	}
}

void Snake::grow(int Calorias) {
	_numCells += Calorias;
	int x, y;
	x = _cells.back().getX();
	y = _cells.back().getY();
	for (int i = 0; i < Calorias; i++)
	{
		_cells.push_back(Cell(x, y, _color));
	}
}

void Snake::moveSnake() {
	//Avanza la cabeza y actualiza el colision engine
	Cell nCell(_cells.front().getX() + dirs[_dir].first, _cells.front().getY() + dirs[_dir].second, _cells.front().getColor());
	_cells.push_front(nCell);

	//Actualizo la posicion de la cabeza de la serpiente
	_posX = _cells.front().getX();
	_posY = _cells.front().getY();
	Logic::getCEngine()->AddEntity(_posX, _posY, EntityType::Dead, &_cells.front());

	//Borra la cola para avanzar
	Cell oldCell = _cells.back();
	Logic::getCEngine()->RemoveEntity(oldCell.getX(), oldCell.getY());
	_cells.pop_back();

	//Si esta creciendo se vuelve a dar de alta en el collision engine con la nueva celda
	Cell colaCell = _cells.back();
	if (oldCell.getX() == colaCell.getX() && oldCell.getY() == colaCell.getY())
		Logic::getCEngine()->AddEntity(colaCell.getX(), colaCell.getY(), EntityType::Dead, &colaCell);
}
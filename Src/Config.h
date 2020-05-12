#pragma once
#include <math.h>

////Variables globales, enums y clases User y User Input////

//////////SNAKE////////////////
#define SPEED 20 //Celdas por segundo
#define TAM_SNAKE 20
//Distancia de seguridad para el spawn de las serpientes
#define DIST_SEG 4 


/////////////FRUTA////////////////
//Numero y tamaño máximo de las frutas
#define CALORIES 10

///////////MARCADOR///////////////
const int SCORE_MARGIN = 15;

#ifdef _ORBIS
//Constante por la que se divide el tiempo para obtenerlo en ms
#define TIME 1000
#define X_CELLS 256 //1280
#define Y_CELLS 144 //720
const int JOYSTICK_DEAD_ZONE = 100;

#else
//Constante por la que se divide el tiempo para obtenerlo en ms
#define TIME 1
#define X_CELLS 216 //1080
#define Y_CELLS 144 //720
const int JOYSTICK_DEAD_ZONE = 25000;
#endif

//Enum de colores
// Los 4 primeros se corresponden con una serpiente y sus direcciones en orden.
enum Color { Azul, Rojo, Verde, Rosa, Amarillo, Blanco, Negro, COUNT = 7 };
enum direction { LEFT, UP, RIGHT, DOWN };

//Clase encargada de procesar las direcciones normalizadas del mando
class UserInput {
public:
	direction getDir() { process = true; return _dir; };
	void setDirInput(int dir) { 
		process = false;
		_dir = (direction)dir; 
	};
	void setUserInput(int x, int y) {
		if (process) {
			//Controles
			if (abs(x) > abs(y)) {
				if (x > 0 && _dir != direction::LEFT) {
					_dir = direction::RIGHT;
					process = false;
				}
				else if (x < 0 && _dir != direction::RIGHT)
					_dir = direction::LEFT;
					process = false;

			}
			else if (abs(x) < abs(y)) {
				if (y < 0 && _dir != direction::DOWN) {
					_dir = direction::UP;
					process = false;
				}
				else if (y > 0 && _dir != direction::UP) {
					_dir = direction::DOWN;
					process = false;
				}
			}
		}
	}
private:
	direction _dir;
	bool process = true;
};

//Struct con las características generales del usuario
struct User {
	int userID;
	int controllerHandle;
	UserInput* input;
	Color color;
	char* name;
};

static bool operator==(const User& a, const User& b) {
	return a.userID == b.userID;
}
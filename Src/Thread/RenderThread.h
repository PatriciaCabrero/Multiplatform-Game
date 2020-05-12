#pragma once
#include "..\Renderer\Renderer.h"
#include "ConcurrentQueue.h"

using namespace std;

enum CommandType { Clear, PutPixel, DrawLine, DrawCell, EndFrame };

//Datos que se env�an en el comando dependiendo de su tipo
struct DataPutPixel {
	int x, y;
	Color color;
};
struct DataClear {
	Color color;
};
struct DataDrawLine {
	int x, y, length, height;
	Color color;
};

struct DataDrawCell {
	int x, y;
	Color color;
};

struct DataEndFrame {
};

//Clase con la instrucci�n que se env�a al RenderThread para que pinte
struct Command
{	
	void init(CommandType type, Color color = Color::Blanco, int x = 0, int y = 0, int len = 0, int h = 0) {
		_type = type;
		switch (_type)
		{
		case CommandType::Clear:
			dClear.color = color;
			break;
		case CommandType::PutPixel:
			dpp.color = color;
			dpp.x = x;
			dpp.y = y;
			break;
		case CommandType::DrawLine:
			dLine.color = color;
			dLine.length = len;
			dLine.height = h;
			dLine.x = x;
			dLine.y = y;
			break;
		case CommandType::DrawCell:
			dCell.color = color;
			dCell.x = x;
			dCell.y = y;
			break;
		default:
			break;
		}
	}

	CommandType _type;
	union {
		DataPutPixel dpp;
		DataClear dClear;
		DataDrawLine dLine;
		DataEndFrame dEndLine;
		DataDrawCell dCell;
	} ;
};

//La clase lanza un thread que recibe instrucciones del thread principal
//y en funci�n de �stas se encarga de pintar en a pantalla
class RenderThread
{
public:
	RenderThread();
	~RenderThread();
	void start();
	void stop();

	int getFrameOffset() { return frameOffset; }

	//M�todos que encolan instrucciones
	//Instrucci�n borrado pantalla
	void enqClear(Color color);
	//Instrucci�n que pinta un pixel en la posicion x, y de la pantalla
	void enqPPixel(int x, int y, Color color);

	//Instrucci�n que pinta una l�nea de celdas en la posicion x, y del grid
	void enqDLine(int x, int y,int h,int w, Color color);

	//Instrucci�n que pinta una celda en la posicion x, y del grid
	void enqDCell(int x, int y, Color color);

	//Instruccion de present
	void enqEndFrame();
	//Interpreta la instrucci�n que le llega y pinta en funci�n a ella
	void render();
	
private:
	Queue<Command> _commands;
	bool _running;
	thread t;
	Command _cmd;
	int TAM_X_CELLS, TAM_Y_CELLS;

	//Si la l�gica va m�s de tres ticks por delante del dibujado, no avanza
	int frameOffset;
};


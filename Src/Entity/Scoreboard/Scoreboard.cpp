#include "Scoreboard.h"
#include "..\..\Input\UserManager.h"
#include "..\..\Config.h"

Segment::Segment(int iniCellX, int inicellY, bool vertical, Color color):Entity()
{
	_posX = iniCellX;
	_posY = inicellY;
	if (vertical) {
		_tamX = 1;
		_tamY = 4;
	}
	else {
		_tamX = 4;
		_tamY = 1;
	}
	_color = color;
}

Segment::~Segment()
{
}

void Segment::draw(RenderThread * t, int offset)
{
	if(_active)
		t->enqDLine(_posX+ offset*5 , _posY, _tamY, _tamX, _color);
}

void Segment::init()
{
}

bool Segment::update()
{
	return false;
}


Scoreboard::Scoreboard(Color color):Entity()
{
	_color = color;
	_score = -1;
	_segments = std::vector<Segment*>();
}

Scoreboard::~Scoreboard()
{
	for (int i = 0; i < _segments.size(); i++) {
		delete _segments[i];
	}
}

void Scoreboard::draw(RenderThread * t, int offset)
{
	for (int i = 0; i < _segments.size(); i++) {
		_segments[i]->draw(t, offset);
	}
}

void Scoreboard::init()
{

	switch (_color)
	{
	case Azul:
		_posX = SCORE_MARGIN;
		_posY = SCORE_MARGIN;
		break;
	case Rojo:
		_posX = X_CELLS - SCORE_MARGIN;
		_posY = SCORE_MARGIN;
		break;
	case Verde:
		_posX = X_CELLS - SCORE_MARGIN;
		_posY = Y_CELLS - SCORE_MARGIN;
		break;
	case Rosa:
		_posX = SCORE_MARGIN;
		_posY = Y_CELLS - SCORE_MARGIN;
		break;
	default:
		break;
	}

	//Segmentos horizontales
	for (int i = 0; i < 3; i++) {
		_segments.push_back(new Segment(_posX, _posY + i * 3, false, _color));
	}

	//Segmentos verticales
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			_segments.push_back(new Segment(_posX + i* 3, _posY + j*3, true, _color));
		}
	}
	setScore();
}

bool Scoreboard::update()
{
	return false;
}

void Scoreboard::setScore(int score)
{

	_score = score;
	switch (_score)
	{
	case 0:
		_segments[0]->setActive(true);
		_segments[1]->setActive(false);
		_segments[2]->setActive(true);
		_segments[3]->setActive(true);
		_segments[4]->setActive(true);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 1:
		_segments[0]->setActive(false);
		_segments[1]->setActive(false);
		_segments[2]->setActive(false);
		_segments[3]->setActive(false);
		_segments[4]->setActive(false);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 2:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(false);
		_segments[4]->setActive(true);
		_segments[5]->setActive(true);
		_segments[6]->setActive(false);
		break;
	case 3:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(false);
		_segments[4]->setActive(false);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 4:
		_segments[0]->setActive(false);
		_segments[1]->setActive(true);
		_segments[2]->setActive(false);
		_segments[3]->setActive(true);
		_segments[4]->setActive(false);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 5:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(true);
		_segments[4]->setActive(false);
		_segments[5]->setActive(false);
		_segments[6]->setActive(true);
		break;
	case 6:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(true);
		_segments[4]->setActive(true);
		_segments[5]->setActive(false);
		_segments[6]->setActive(true);
		break;
	case 7:
		_segments[0]->setActive(true);
		_segments[1]->setActive(false);
		_segments[2]->setActive(false);
		_segments[3]->setActive(false);
		_segments[4]->setActive(false);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 8:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(true);
		_segments[4]->setActive(true);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	case 9:
		_segments[0]->setActive(true);
		_segments[1]->setActive(true);
		_segments[2]->setActive(true);
		_segments[3]->setActive(true);
		_segments[4]->setActive(false);
		_segments[5]->setActive(true);
		_segments[6]->setActive(true);
		break;
	default:
		break;
	}

}

#pragma once
#include "..\Entity.h"
#include <vector>

//Cada uno de los segmentos que componen el marcador (7 segmentos)
class Segment :
	public Entity 
{
public:
	Segment(int iniCellX, int inicellY, bool vertical, Color color);
	~Segment();
	void draw(RenderThread * t, int offset);
	virtual void init();
	virtual bool update();
	void setActive(bool active) { _active = active; }

private:
	bool _active = true;
};

//El scoreboard lleva la puntuación y la pinta encendiendo o apagando
//los segmentos que necesite
class Scoreboard:
	public Entity
{
public:
	Scoreboard(Color color);
	~Scoreboard();
	void draw(RenderThread * t, int offset);
	virtual void init();
	virtual bool update();
	void setScore(int score = 0);

private:
	std::vector<Segment*> _segments;
	int _score;
	int _userID;
};
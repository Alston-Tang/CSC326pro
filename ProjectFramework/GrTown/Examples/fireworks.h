#include "../GrObject.H"
#include "WinFltk/include/GL/glut.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../DrawingState.H"
#include "Cars.H"

class Part
{
public:
	int type;
	bool sta;
	float vx, vy, vz, pox, poy, poz,time;
	Part();
};

class Fireworks :public GrObject,public Part
{
public:
	Part *pt[100];
	bool peng;
	Fireworks();
	virtual void draw(DrawingState* s);
	void drawPart(Part*);
};
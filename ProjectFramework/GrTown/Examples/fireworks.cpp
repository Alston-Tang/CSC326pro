#ifndef _frwk
#define _frwk

#include "../GrObject.H"
#include "WinFltk/include/GL/glut.h"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../DrawingState.H"
#include "Cars.H"
#include "fireworks.h"

Part::Part()
{
	sta = false;
}

void Fireworks::draw(DrawingState* s)
{
	if (!sta) return;
	else if (!peng)
	{
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(pox, poy, poz);
		glutSolidSphere(0.5, 5, 5);
		glPopMatrix();
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			if (pt[i]->sta)
			{
				drawPart(pt[i]);
			}
		}
	}	
}

Fireworks::Fireworks()
{
	sta = false;
	peng = false;
	vx = 0; vy = 0; vz = 0; pox = 0; poy = 0; poz = 0; time = 0;
	for (int i = 0; i < 100; i++)
	pt[i] = new Part;
}

void Fireworks::drawPart(Part* p)
{
	glPushMatrix();
	glTranslatef(p->pox, p->poy, p->poz);
	glutSolidSphere(0.5,5,5);
	glPopMatrix();
}



#endif
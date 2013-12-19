#ifndef _plane
#define _plane

#include "../GrObject.H"
#include "WinFltk/include/GL/glut.h"
//#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../DrawingState.H"

class plane :public GrObject
{
public:
	float dir,v,fbr,lrr,pox,poy,poz;
	bool over;
	plane(float direction, float x, float y, float z) :dir(direction), fbr(0), lrr(0), v(0), pox(x), poy(y), poz(z)
	{
	}
	plane(float direction) :dir(direction),fbr(0), lrr(0), v(0), pox(0), poy(0), poz(0)
	{
		over = false;
	};
	void draw(DrawingState* s)
	{
		glColor3f(1.0, 1.0, 1.0);
		GLUquadricObj* obj;
		obj = gluNewQuadric();
		glPushMatrix();
		glTranslatef(pox, poy, poz);
		glRotatef(dir, 0, 1, 0);
		glRotatef(fbr, 1, 0, 0);
		glRotatef(lrr, 0, 0, 1);
		
		gluCylinder(obj, 2.5, 2.5, 25, 10, 10);
		polygon(-4, 2.5, 0.0, 21.0, 2.5, 0.0, 24.5, 7.5, 0.0, 24.5, 7.5, 0.0, 22.0);
		polygon(-4, 2.5, 0.0, 24.5, 2.5, -0.5, 24.5, 7.5, -0.5, 24.5, 7.5, 0.0, 24.5);
		polygon(-4, 7.5, 0.0, 24.5, 7.5, -0.5, 24.5, 7.5, -0.5, 22.0, 7.5, 0.0, 22.0);
		polygon(-4, 7.5, 0.0, 22.0, 7.5, -0.5, 22.0, 2.5, -0.5, 21.0, 2.5, 0.0, 21.0);
		polygon(4, 2.5, -0.5, 21.0, 2.5, -0.5, 24.5, 7.5, -0.5, 24.5, 7.5, -0.5, 22.0);

		polygon(4, -2.5, 0.0, 21.0, -2.5, 0.0, 24.5, -7.5, 0.0, 24.5, -7.5, 0.0, 22.0);
		polygon(4, -2.5, 0.0, 24.5, -2.5, -0.5, 24.5, -7.5, -0.5, 24.5, -7.5, 0.0, 24.5);
		polygon(4, -7.5, 0.0, 24.5, -7.5, -0.5, 24.5, -7.5, -0.5, 22.0, -7.5, 0.0, 22.0);
		polygon(4, -7.5, 0.0, 22.0, -7.5, -0.5, 22.0, -2.5, -0.5, 21.0, -2.5, 0.0, 21.0);
		polygon(-4, -2.5, -0.5, 21.0, -2.5, -0.5, 24.5, -7.5, -0.5, 24.5, -7.5, -0.5, 22.0);

		glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		
		fetchTexture("plane1.bmp");
		polygon(-4, -0.25, 2.5, 24.5, -0.25, 7.5, 24.5, -0.25, 7.5, 22.0, -0.25, 2.5, 21.0);
		polygon(4, 0.25, 2.5, 24.5, 0.25, 7.5, 24.5, 0.25, 7.5, 22.0, 0.25, 2.5, 21.0);
		glBindTexture(GL_TEXTURE_2D, 0);
		polygon(-4, 0.25, 7.5, 22.0, 0.25, 2.5, 21.0, -0.25, 2.5, 21.0, -0.25, 7.5, 22.0);
		polygon(4, 0.25, 7.5, 24.5, -0.25, 7.5, 24.5, -0.25, 7.5, 22.0, 0.25, 7.5, 22.0);
		polygon(4, 0.25, 7.5, 24.5, 0.25, 2.5, 24.5, -0.25, 2.5, 24.5, -0.25, 7.5, 24.5);
		glPopMatrix();

		polygon(-4, 2.5, 0.0, 12.0, 18.5, 0.0, 14.0, 18.5, 0.0, 9.0, 2.5, 0.0, 6.0);
		polygon(4, 2.5, -0.5, 12.0, 18.5, -0.5, 14.0, 18.5, -0.5, 9.0, 2.5, -0.5, 6.0);
		polygon(-4, 2.5, 0.0, 12.0, 2.5, -0.5, 12.0, 18.5, -0.5, 14.0, 18.5, 0.0, 14.0);
		polygon(-4, 18.5, 0.0, 14.0, 18.5, -0.5, 14.0, 18.5, -0.5, 9.0, 18.5, 0.0, 9.0);
		polygon(-4, 18.5, 0.0, 9.0, 18.5, -0.5, 9.0, 2.5, -0.5, 6.0, 2.5, 0.0, 6.0);
		
		polygon(4, -2.5, 0.0, 12.0, -18.5, 0.0, 14.0, -18.5, 0.0, 9.0, -2.5, 0.0, 6.0);
		polygon(-4, -2.5, -0.5, 12.0, -18.5, -0.5, 14.0, -18.5, -0.5, 9.0, -2.5, -0.5, 6.0);
		polygon(4, -2.5, 0.0, 12.0, -2.5, -0.5, 12.0, -18.5, -0.5, 14.0, -18.5, 0.0, 14.0);
		polygon(4, -18.5, 0.0, 14.0, -18.5, -0.5, 14.0, -18.5, -0.5, 9.0, -18.5, 0.0, 9.0);
		polygon(4, -18.5, 0.0, 9.0, -18.5, -0.5, 9.0, -2.5, -0.5, 6.0, -2.5, 0.0, 6.0);
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, -3.0);
		gluCylinder(obj, 0, 2.5, 3, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, 25);
		gluDisk(obj, 0, 2.5, 10, 1);
		glPopMatrix();
		glPopMatrix();
		if (pox > 3000 || poy > 3000 || poz > 3000 || pox < -3000 || poz < -3000) over = true;
	}
};

#endif
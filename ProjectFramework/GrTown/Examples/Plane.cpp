#ifndef _plane
#define _plane

#include "../GrObject.H"
#include "WinFltk/include/GL/glut.h"
//#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../DrawingState.H"
#include "Cars.H"

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
		GLUquadricObj* obj;
		obj = gluNewQuadric();
		glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glTranslatef(pox, poy, poz);
		glRotatef(dir, 0, 1, 0);
		glRotatef(fbr, 1, 0, 0);
		glRotatef(lrr, 0, 0, 1);
		
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		fetchTexture("plane2.bmp");
		gluQuadricTexture(obj,GL_TRUE);
		gluCylinder(obj, 2.5, 2.5, 25, 10, 10);
		glBindTexture(GL_TEXTURE_2D, 0);
		gluQuadricTexture(obj, GL_FALSE);
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

		if (s->timeOfDay<7 || s->timeOfDay>16)
		{
			glColor3f(1.0, 0.0, 0.0);
			polygon(4, 18.6, 0.0, 13.0, 18.6, 0.0, 10.0, 18.6, -0.5, 10.0, 18.6, -0.5, 13.0);
			polygon(-4, -18.6, 0.0, 13.0, -18.6, 0.0, 10.0, -18.6, -0.5, 10.0, -18.6, -0.5, 13.0);
			
			glColor4d(1, 0, 0, .2);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
			glPushMatrix();
			glTranslatef(-48.6, -0.25, 11.5);
			glRotatef(90, 0, 1, 0);
			gluCylinder(obj, 5, 0, 30, 10, 10);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(48.6, -0.25, 11.5);
			glRotatef(-90, 0, 1, 0);
			gluCylinder(obj, 5, 0, 30, 10, 10);
			glPopMatrix();
			glFrontFace(GL_CW);
			glClearColor(1, 1, 1, 1);
			glDisable(GL_BLEND);
			glColor3f(1.0, 1.0, 1.0);
		}
		glPushMatrix();
		glTranslatef(0.0, 0.0, -3.0);
		gluCylinder(obj, 0, 2.5, 3, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, 25);
		gluDisk(obj, 0, 2.5, 10, 1);
		glPopMatrix();
		glPopMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		if (pox > 3000 || poy > 3000 || poz > 3000 || pox < -3000 || poz < -3000) over = true;
	}
};

#endif
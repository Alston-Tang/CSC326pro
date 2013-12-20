// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2006 - new texture manager, improvements for behaviors

// simple example behaviors - something to learn from
#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include "../GrObject.H"
#include "../Examples/plane.cpp"
#include "../Examples/fireworks.h"

#include "SimpleBehaviors.H"

#include <math.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// a trick - since we don't care much about what the rotation is (only
// the rate), we can tie the rotation to the absolute time
Spin::Spin(GrObject* o, float v) : Behavior(o), vel(v)
{
}
void Spin::simulateUntil(unsigned long t)
{
  // remember position
  float x = owner->transform[3][0];
  float y = owner->transform[3][1];
  float z = owner->transform[3][2];
  // set rotation based on time
  rotMatrix(owner->transform, 'y', vel * static_cast<float>(t));
  // put the position back
  owner->transform[3][0] = x;
  owner->transform[3][1] = y;
  owner->transform[3][2] = z;

  lastV = t;
}

////////////////////////////////////////////////////////////////////////
ForwardAlways::ForwardAlways(GrObject* o, float v)
  : Behavior(o), vel(v)
{
}
void ForwardAlways::simulateUntil(unsigned long t)
{
  unsigned long dt = t - lastV;	// how long since last update
  float secs = ((float) dt) / 1000;	// convert ms to sec
  lastV = t;
  owner->transform[3][0] += owner->transform[2][0] * secs * vel;
  owner->transform[3][1] += owner->transform[2][1] * secs * vel;
  owner->transform[3][2] += owner->transform[2][2] * secs * vel;

  lastV = t;
}

////////////////////////////////////////////////////////////////////////
TurnAlways::TurnAlways(GrObject* o, float v)
  : Behavior(o), vel(v)
{
}
void TurnAlways::simulateUntil(unsigned long t)
{
  unsigned long dt = t - lastV;	// how long since last update
  float secs = ((float) dt) / 1000;	// convert ms to sec
  lastV = t;
  Matrix delta, newT;
  rotMatrix(delta,'Y',secs * vel);
  multMatrix(delta,owner->transform,newT);
  copyMatrix(newT,owner->transform);
  lastV = t;
}
//////////////////////////////////////////////////////////////////////////////
TakeOff::TakeOff(GrObject* owner) :Behavior(owner)
{
	plane *p = static_cast<plane*>(owner);
	p->fbr = 0;
	p->pox = 370.0;
	p->poy = 2.0;
	p->poz = -300.0;
	p->v = 0;
}

Land::Land(GrObject* owner) :Behavior(owner)
{
	plane *p = static_cast<plane*>(owner);
	p->fbr = -10;
	p->pox = -800.0;
	p->poy = 200;
	p->poz = -300;
	p->v = 0.1;
}

void TakeOff::simulateUntil(unsigned long t)
{
	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float)dt) / 1000;	// convert ms to sec
	lastV = t;
	if (dt > 1000) return;
	unsigned long tp = t/1000;
	plane *p=static_cast<plane*>(owner);
	if (p->v <= 0.15)
	{
		p->v += secs * 0.03;  //accleration of plane
	}
	else if (p->fbr<=20.0)
	{
		p->fbr += dt*0.005;
	}
	float tmp = p->fbr * 2 * pi / 360;
	p->poy += dt*p->v*sin(tmp);
	p->pox += dt*p->v*cos(tmp);
}

void Land::simulateUntil(unsigned long t)
{

	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float)dt) / 1000;	// convert ms to sec
	lastV = t;
	if (dt > 1000) return;
	plane *p = static_cast<plane*>(owner);
	float tmp = -10 * 2 * pi / 360;
	if (p->poy <= 6)
	{
		tmp = 0;
		if (p->v > 0.0) p->v -= 0.01*secs;
		else p->v = 0;
		if (p->fbr > 0.0) p->fbr -= 20.0 * secs;
		else p->fbr = 0;
		if (p->poy > 2.0) p->poy -= 8.0 * secs;
		else p->poy = 2;
	}
	else if (p->poy < 10)
	{
		p->fbr = 10.0;
		tmp = -(p->poy - 6)*0.41667;
	}
	else if (p->poy < 30)
	{
		p->fbr = 20-p->poy;
		tmp = -(p->poy - 2)*0.35714;
		tmp = tmp * 2 * pi / 360;
	}
	else
	{
		tmp = -10 * 2 * pi / 360;
	}
	p->poy += dt*p->v*sin(tmp);
	p->pox += dt*p->v*cos(tmp);
	if (p->v == 0) p->over = true;
}

Fly::Fly(GrObject* owner) :Behavior(owner)
{
	plane *p;
	p=static_cast<plane*>(owner);
	p->dir = rand()%361;
	p->pox = rand() % 4001 - 2000;
	p->poz = rand() % 4001 - 2000;
	p->poy = rand() % 100 + 50;
	p->v = 0.2;
	p->fbr = 0;
	p->over = false;
	p->lrr = 0;
}

void Fly::simulateUntil(unsigned long t)
{
	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float)dt) / 1000;	// convert ms to sec
	lastV = t;
	plane *p = static_cast<plane*>(owner);
	if (dt > 1000) return;
	float tmp = p->dir * 2 * pi / 360;
	p->pox += dt*p->v*-sin(tmp);
	p->poz += dt*p->v*-cos(tmp);
}

AirControl::AirControl(GrObject* owner, plane **pList) :Behavior(owner), pl(pList), air(false), ld(NULL), tk(NULL)
{
	for (int i = 0; i < 10; i++) fl[i]=NULL;
}

void AirControl::simulateUntil(unsigned long t)
{
	lastV = t;
	if (tk==NULL && ld==NULL)
	{
		if (rand() % 2 == 0)
		{
			ld = new Land(pl[0]);
			pl[0]->over = false;
		}
		
		else
		{
			tk = new TakeOff(pl[0]);
			pl[0]->over = false;
		}
	}
	else if (tk != NULL)
	{
		if (pl[0]->over)
		{
			delete tk;
			tk = NULL;
		}
	}
	else if (ld != NULL)
	{
		if (pl[0]->over)
		{
			delete ld;
			ld = NULL;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (fl[i] == NULL)
		{
			fl[i] = new Fly(pl[i + 1]);
			pl[i + 1]->over = false;
		}
		else
		{
			if (pl[i + 1]->over)
			{
				delete fl[i];
				fl[i] = new Fly(pl[i + 1]);
				pl[i + 1]->over = false;
			}
		}
	}
}

FireControl::FireControl(GrObject *owner):Behavior(owner)
{

}

void FireControl::simulateUntil(unsigned long t)
{
	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float)dt) / 1000;	// convert ms to sec
	lastV = t;
	Fireworks *f = static_cast<Fireworks*>(owner);
	if (dt > 1000) return;
	printf("%f %f %f %f\n", f->pt[1]->pox, f->pt[1]->poy, f->pt[1]->poz, f->pt[1]->time);
	if (!f->sta)
	{
		f->sta = true;
		f->pox = rand() % 200;
		f->poz = rand() % 200;
		f->poy = 0;
		f->vx = (float)(rand() % 100) / 10;
		if (rand() % 2 == 0) f->vx = -f->vx;
		f->vz = (float)(rand() % 100) / 10;
		if (rand() % 2 == 0)f->vz = -f->vz;
		f->vy = (float)(rand() % 50)+50;
		f->time = rand() % 2000 + 2000;
	}
	else if (f->time > 0)
	{
		f->vy -= 25*secs;
		f->pox += f->vx*secs;
		f->poy += f->vy*secs;
		f->poz += f->vz*secs;
		f->time -= dt;
	}
	else if (!f->peng)
	{
		f->peng = true;
		for (int i = 0; i < 100; i++)
		{
			f->pt[i]->sta = true;
			f->pt[i]->pox = f->pox;
			f->pt[i]->poy = f->poy;
			f->pt[i]->poz = f->poz;
			f->pt[i]->vx = (float)(rand() % 20)-10;
			f->pt[i]->vy = (float)(rand() % 20) - 10;
			f->pt[i]->vz = (float)(rand() % 20) - 10;
			f->pt[i]->time = rand() % 2000+2000;
		}
	}
	else
	{
		bool survive = false;
		for (int i = 0; i < 100; i++)
		{
			if (f->pt[i]->sta)
			{
				survive = true;
				f->pt[i]->vy -= 5*secs;
				f->pt[i]->pox += f->pt[i]->vx*secs;
				f->pt[i]->poy += f->pt[i]->vy*secs;
				f->pt[i]->poz += f->pt[i]->vz*secs;
				f->pt[i]->time -= dt;
				if (f->pt[i]->time <= 0) f->pt[i]->sta = false;
			}
		}
		if (!survive)
		{
			f->sta = false;
			f->peng = false;
		}
	}
}

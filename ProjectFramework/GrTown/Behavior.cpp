// GraphicsTown2006 
// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
//
// Behavior.cpp - base class of behaviors, and a few other simple
//	behaviors - see Behavior.H
//
// support for the base class of behaviors as well as a few test behaviors
// none are particularly interesting

#include "GrTown_PCH.H"

#include "Behavior.H"
#include "GrObject.H"

////////////////////////////////////////////////////////////////////////
Behavior::Behavior(GrObject* o) :
  owner(o), lastV(0)
{
	o->behaviors.push_back(this);
}
void Behavior::simulateUntil(unsigned long t)
{
  lastV = t;
}





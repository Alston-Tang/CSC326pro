#ifndef GrWorld_H
#define GrWorld_H

/// GraphicsTown2006 
// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2008 - convert from linked lists to vectors
#include <vector>

//
// "the world" - framework for stuff to go into
//
class DrawingState;
class GrObject;

// the sky and "earth" are special objects, so we draw them
// differently - they are not GrObjects. 
// they always get drawn before all other objects
// draw sky gets called first, and is responsible for doing the clear
// 
void drawSky(DrawingState*);
void drawEarth(DrawingState*);

// basic lighting...
void setupLights(DrawingState*);

// all of the objects in the world, kept in a big linked list...
// except that now its a big stl vector
// and its defined in GrObject.H



#endif

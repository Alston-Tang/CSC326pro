#ifndef DRAWINGSTATE_H
#define DRAWINGSTATE_H
/// GraphicsTown2006 
// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
//

// "Drawing State" - a structure that tells objects how to draw
// themselves. 
// Objects need lots of info, since they are responsible for a lot
// about drawing themselves. The drawing state gives them as much info
// as possible so they can do things like cull themselves, do fake
// lighting if they want to, ...
class GrObject;

#include "DrawUtils.H"

// the drawing state class itself
class DrawingState {
public:
  DrawingState();				// make a new one
  DrawingState(DrawingState&);	// copy an old one

  // time of day - military time (0 = midnight, 12=noon)
  int timeOfDay;

  // some state
  // draw sky/ground sets these based on time of day
  Color sky;
  Color ground;

  // which object is the camera?
  GrObject* camera;

  float fieldOfView;

  // these are really bools, but since bools generate too many warnings...
  int backCull;
  int drGrTex;		// draw ground textures
};


#endif

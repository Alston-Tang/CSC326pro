#pragma once
// these are example objects - very simple - hopefully yours will be nicer!

// Cars - cars are actually just static, rigid objects
// A driving behavior is added to move them around
//
#include "../GrObject.H"

// keep a pointer to the texture, that way we only look it up the first time
class Texture;

class Car : public GrObject {
 public:
	Texture* sideTexture;
	Texture* frontTexture;

  Car(char* type, int color);
  Color color;

  // this draw the whole car - subclasses just redefine "body"
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);

  virtual void drawBody(DrawingState*);
  
	float lm;       // length of middle part
	float lw;		// length of window
	float lbw;		// length of back window
	float lbr;		// slope of back window
	float bhr;		// slope of back hood
	float w;		// half width
	float f; 		// length of front part
	float r; 		// length of back part
	float h; 		// height of ground
	float m; 		// height of motor
	float t; 		// height of back part
	float s; 		// slope of windshield
	float a; 		// rake of hood
	float sr;		// side rake of upper part
	float br;		// back rake of upper part
};

class SUV : public Car {
public:
  SUV(int color);
};
class HatchBack : public Car {
public:
  HatchBack(int color);
};
class Van : public Car {
public:
  Van(int color);
};




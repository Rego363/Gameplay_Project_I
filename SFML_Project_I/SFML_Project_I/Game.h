#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Matrix3.h"

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	const int primitives;

	Keyboard keyPressed;

	GLuint index;
	Clock clock;
	Time elapsed;

	MyVector3 corner1;
	MyVector3 corner2;
	MyVector3 corner3;
	MyVector3 corner4;
	MyVector3 corner5;
	MyVector3 corner6;
	MyVector3 corner7;
	MyVector3 corner8;
	Matrix3 scale;
	Matrix3 oppoScale;
	Matrix3 rotX;
	Matrix3 oppoRotX;
	Matrix3 rotY;
	Matrix3 oppoRotY;
	Matrix3 rotZ;
	Matrix3 oppoRotZ;
	Matrix3 translate;
	Matrix3 oppoTranslate;
	Matrix3 mold;
	Matrix3 empty;
	float rotationAngle = 0.1f;
};
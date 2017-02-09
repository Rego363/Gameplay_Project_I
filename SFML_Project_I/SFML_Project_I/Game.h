#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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
	sf::RenderWindow window;
	bool isRunning = false;
	bool showVertex(MyVector3 V1, MyVector3 V2, MyVector3 V3);
	void initialize();
	void update();
	void draw();
	void unload();
	void renderFunction(sf::RenderWindow &window);

	const int primitives;

	Keyboard keyPressed;

	GLuint index;
	Clock clock;
	Time elapsed;

	bool safe = true;
	bool jump;
	MyVector3 gravity;
	MyVector3 velocity;
	float timeChange;
	double totalTime;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	MyVector3 corner1;
	MyVector3 corner2;
	MyVector3 corner3;
	MyVector3 corner4;
	MyVector3 corner5;
	MyVector3 corner6;
	MyVector3 corner7;
	MyVector3 corner8;
	MyVector3 cube1[8];
	MyVector3 cube2[8];
	MyVector3 cube3[8];
	MyVector3 cube4[8];
	MyVector3 cube5[8];
	MyVector3 cube6[8];
	MyVector3 cube7[8];
	MyVector3 cube8[8];
	Matrix3 scale;
	Matrix3 oppoScale;
	Matrix3 rotX;
	Matrix3 oppoRotX;
	Matrix3 rotY;
	Matrix3 oppoRotY;
	Matrix3 rotZ;
	Matrix3 oppoRotZ;
	Matrix3 translateX;
	Matrix3 oppoTranslateX;
	Matrix3 translateY;
	Matrix3 oppoTranslateY;
	Matrix3 mold;
	Matrix3 empty;
	sf::Vector2f cameraPos;
	float rotationAngle = 0.2228f;
	float rot;
	float tran;
	bool rotSwitch;
};
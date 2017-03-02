#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "Vector3.h"
#include "Matrix3.h"

#include <fstream>
#include <sstream>

#include <Debug.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <PlayerCube.h>
#include <EnemyCube.h>

using namespace std;
using namespace sf;
using namespace glm;

class PlayerCube;
class EnemyCube;

class Game
{
public:
	Game();
	Game(sf::ContextSettings settings);
	~Game();
	void run();
	
private:
	PlayerCube playerCube;
	//std::vector<EnemyCube> enemyCube;
	EnemyCube enemyCube[2];
	std::ifstream vertexInput;
	std::stringstream vss;
	std::string vsLine;
	std::ifstream fragInput;
	std::stringstream ss;
	std::string line;

	Window window;
	bool isRunning = false;
	bool jump = false;
	bool fall = false;
	int count = 0;
	int fallCount = 0;
	bool rotSwitch;
	MyVector3 gravity;
	MyVector3 velocity;
	glm::vec3 speed;
	sf::Clock clock;
	Matrix3 yTranslate;
	float timeChange;
	double totalTime;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	void initialize();
	void update();
	void render();
	void unload();
	void cubeMaker(mat4 &model);
	bool checkCollision(vec3 player, vec3 enemy);
};

#endif
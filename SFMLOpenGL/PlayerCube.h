#include "Game.h"

#ifndef PLAYERCUBE_H
#define PLAYERCUBE_H

#pragma once

class PlayerCube
{
public:
	PlayerCube();
	~PlayerCube();
	void render();
	void update();
	glm::vec3 getPos();

private:
	glm::vec3 m_position;

};

#endif
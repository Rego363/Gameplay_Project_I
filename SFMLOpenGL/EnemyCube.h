#include "Game.h"

#ifndef ENEMYCUBE_H
#define ENEMYCUBE_H

#pragma once
class EnemyCube
{
public:
	EnemyCube();
	~EnemyCube();
	void update();
	glm::vec3 getPos();

private:
	glm::vec3 m_position;
};

#endif
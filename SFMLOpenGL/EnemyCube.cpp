#include "EnemyCube.h"

EnemyCube::EnemyCube()
{
	m_position = glm::vec3(0, 0, -100);
}

EnemyCube::EnemyCube(glm::vec3 pos)
{
	m_position = pos;
}


EnemyCube::~EnemyCube()
{
}

void EnemyCube::update()
{
	
	if (m_position.z > 6)
	{
		m_position.z = -100;
	}
	else
	{
		m_position.z += 0.02;
	}
}

vec3 EnemyCube::getPos()
{
	return m_position;
}
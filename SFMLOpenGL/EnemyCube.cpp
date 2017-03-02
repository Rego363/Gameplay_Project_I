#include "EnemyCube.h"



EnemyCube::EnemyCube()
{
	m_position = glm::vec3(-5, 0, -100);
}


EnemyCube::~EnemyCube()
{
}

void EnemyCube::update()
{
	m_position.z += 0.02;
	if (m_position.z > -2)
	{
		m_position.z = -100;
	}
}

vec3 EnemyCube::getPos()
{
	return m_position;
}
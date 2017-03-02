#include "PlayerCube.h"



PlayerCube::PlayerCube()
{
	m_position = glm::vec3(0, 0, 0);
}


PlayerCube::~PlayerCube()
{
}

void PlayerCube::render()
{

}

void PlayerCube::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Set Model position
		m_position.x -= 0.1;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Set Model position
		m_position.x += 0.1;
	}

}

vec3 PlayerCube::getPos()
{
	return m_position;
}
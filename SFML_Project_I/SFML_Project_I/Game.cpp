#include "Game.h"

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"), primitives(1)
{
	index = glGenLists(primitives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	
	corner1 = MyVector3(0.5f, 0.5f, -5.0f);
	corner2 = MyVector3(-1.5f, 0.5f, -5.0f);
	corner3 = MyVector3(-1.5f, -1.5f, -5.0f);
	corner4 = MyVector3(0.5f, -1.5f, -5.0f);
	corner5 = MyVector3(0.5f, 0.5f, -15.0f);
	corner6 = MyVector3(-1.5f, 0.5f, -15.0f);
	corner7 = MyVector3(-1.5f, -1.5f, -15.0f);
	corner8 = MyVector3(0.5f, -1.5f, -15.0f);

	corner1 = MyVector3(1.0f, 1.0f, -5.0f);
	corner2 = MyVector3(-1.0f, 1.0f, -5.0f);
	corner3 = MyVector3(-1.0f, -1.0f, -5.0f);
	corner4 = MyVector3(1.0f, -1.0f, -5.0f);
	corner5 = MyVector3(1.0f, 1.0f, -7.0f);
	corner6 = MyVector3(-1.0f, 1.0f, -7.0f);
	corner7 = MyVector3(-1.0f, -1.0f, -7.0f);
	corner8 = MyVector3(1.0f, -1.0f, -7.0f);
	scale = scale.scale(99.9f, 99.9f);
	oppoScale = oppoScale.scale(99.9f, 99.9f);
	oppoScale = oppoScale.inverse();
	translate = translate.translateX(0.0001f, 0.0001f);
	oppoTranslate = oppoTranslate.translateX(-0.0001f, -0.0001f);
	rotX = rotX.rotationX(rotationAngle);
	oppoRotX = oppoRotX.rotationX(-rotationAngle);
	rotY = Matrix3(0.01f, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.0f, 0.0f, 0.01f); //rotY = rotY.rotationY(rotationAngle);
	oppoRotY = Matrix3(-0.01f, 0.0f, 0.0f, 0.0f, -0.01f, 0.0f, 0.0f, 0.0f, -0.01f);  //oppoRotY = oppoRotY.rotationY(-rotationAngle);
	rotZ = rotZ.rotationZ(rotationAngle); 
	oppoRotZ = oppoRotZ.rotationZ(-rotationAngle);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	

	glNewList(index, GL_COMPILE);
	/*glBegin(GL_POINTS);
	{
		glPointSize(50);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
	}*/
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());

		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());

		//Complete the faces of the Cube

	}
	glEnd();
	glEndList();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
			current++;
			if (current > primitives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::W))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(rotationAngle);
		corner1 = rotX * corner1;
		corner2 = rotX * corner2;
		corner3 = rotX * corner3;
		corner4 = rotX * corner4;
		corner5 = rotX * corner5;
		corner6 = rotX * corner6;
		corner7 = rotX * corner7;
		corner8 = rotX * corner8;
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::S))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(-rotationAngle);
		corner1 = oppoRotX * corner1;
		corner2 = oppoRotX * corner2;
		corner3 = oppoRotX * corner3;
		corner4 = oppoRotX * corner4;
		corner5 = oppoRotX * corner5;
		corner6 = oppoRotX * corner6;
		corner7 = oppoRotX * corner7;
		corner8 = oppoRotX * corner8;
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::A))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(rotationAngle);
		corner1 = rotY.row(0) + corner1;
		corner2 = rotY.row(0) + corner2;
		corner3 = rotY.row(0) + corner3;
		corner4 = rotY.row(0) + corner4;
		corner5 = rotY.row(0) + corner5;
		corner6 = rotY.row(0) + corner6;
		corner7 = rotY.row(0) + corner7;
		corner8 = rotY.row(0) + corner8;
		
		corner1 = rotY.row(1) + corner1;
		corner2 = rotY.row(1) + corner2;
		corner3 = rotY.row(1) + corner3;
		corner4 = rotY.row(1) + corner4;
		corner5 = rotY.row(1) + corner5;
		corner6 = rotY.row(1) + corner6;
		corner7 = rotY.row(1) + corner7;
		corner8 = rotY.row(1) + corner8;

		corner1 = rotY.row(2) + corner1;
		corner2 = rotY.row(2) + corner2;
		corner3 = rotY.row(2) + corner3;
		corner4 = rotY.row(2) + corner4;
		corner5 = rotY.row(2) + corner5;
		corner6 = rotY.row(2) + corner6;
		corner7 = rotY.row(2) + corner7;
		corner8 = rotY.row(2) + corner8;



	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::D))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(-rotationAngle);
		corner1 = oppoRotY.row(0) + corner1;
		corner2 = oppoRotY.row(0) + corner2;
		corner3 = oppoRotY.row(0) + corner3;
		corner4 = oppoRotY.row(0) + corner4;
		corner5 = oppoRotY.row(0) + corner5;
		corner6 = oppoRotY.row(0) + corner6;
		corner7 = oppoRotY.row(0) + corner7;
		corner8 = oppoRotY.row(0) + corner8;

		corner1 = oppoRotY.row(1) + corner1;
		corner2 = oppoRotY.row(1) + corner2;
		corner3 = oppoRotY.row(1) + corner3;
		corner4 = oppoRotY.row(1) + corner4;
		corner5 = oppoRotY.row(1) + corner5;
		corner6 = oppoRotY.row(1) + corner6;
		corner7 = oppoRotY.row(1) + corner7;
		corner8 = oppoRotY.row(1) + corner8;

		corner1 = oppoRotY.row(2) + corner1;
		corner2 = oppoRotY.row(2) + corner2;
		corner3 = oppoRotY.row(2) + corner3;
		corner4 = oppoRotY.row(2) + corner4;
		corner5 = oppoRotY.row(2) + corner5;
		corner6 = oppoRotY.row(2) + corner6;
		corner7 = oppoRotY.row(2) + corner7;
		corner8 = oppoRotY.row(2) + corner8;
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::Left))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(rotationAngle);
		corner1 = rotZ * corner1;
		corner2 = rotZ * corner2;
		corner3 = rotZ * corner3;
		corner4 = rotZ * corner4;
		corner5 = rotZ * corner5;
		corner6 = rotZ * corner6;
		corner7 = rotZ * corner7;
		corner8 = rotZ * corner8;
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::Right))
	{
		//rot = Matrix3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		//rot = empty.rotationZ(-rotationAngle);
		corner1 = oppoRotZ * corner1;
		corner2 = oppoRotZ * corner2;
		corner3 = oppoRotZ * corner3;
		corner4 = oppoRotZ * corner4;
		corner5 = oppoRotZ * corner5;
		corner6 = oppoRotZ * corner6;
		corner7 = oppoRotZ * corner7;
		corner8 = oppoRotZ * corner8;
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::Up))
	{
		corner1 = scale * corner1;
		corner2 = scale * corner2;
		corner3 = scale * corner3;
		corner4 = scale * corner4;
		corner5 = scale * corner5;
		corner6 = scale * corner6;
		corner7 = scale * corner7;
		corner8 = scale * corner8;
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::Down))
	{
		corner1 = oppoScale * corner1;
		corner2 = oppoScale * corner2;
		corner3 = oppoScale * corner3;
		corner4 = oppoScale * corner4;
		corner5 = oppoScale * corner5;
		corner6 = oppoScale * corner6;
		corner7 = oppoScale * corner7;
		corner8 = oppoScale * corner8;
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::Z))
	{
		corner1 = translate * corner1;
		corner2 = translate * corner2;
		corner3 = translate * corner3;
		corner4 = translate * corner4;
		corner5 = translate * corner5;
		corner6 = translate * corner6;
		corner7 = translate * corner7;
		corner8 = translate * corner8;
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::X))
	{
		corner1 = oppoTranslate * corner1;
		corner2 = oppoTranslate * corner2;
		corner3 = oppoTranslate * corner3;
		corner4 = oppoTranslate * corner4;
		corner5 = oppoTranslate * corner5;
		corner6 = oppoTranslate * corner6;
		corner7 = oppoTranslate * corner7;
		corner8 = oppoTranslate * corner8;
	}

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << current << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis

	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}


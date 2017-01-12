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
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	gravity = MyVector3(0.0f, -9.8f, 0.0f);
	velocity = MyVector3(0.0f, 6.0f, 0.0f);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml

	corner1 = MyVector3(0.5f, -2.0f, -12.0f);
	corner2 = MyVector3(-0.5f, -2.0f, -12.0f);
	corner3 = MyVector3(-0.5f, -3.0f, -12.0f);
	corner4 = MyVector3(0.5f, -3.0f, -12.0f);
	corner5 = MyVector3(0.5f, -2.0f, -13.0f);
	corner6 = MyVector3(-0.5f, -2.0f, -13.0f);
	corner7 = MyVector3(-0.5f, -3.0f, -13.0f);
	corner8 = MyVector3(0.5f, -3.0f, -13.0f);

	cube1[0] = MyVector3(1.0f, -3.0f, -11.0f);
	cube1[1] = MyVector3(-1.0f, -3.0f, -11.0f);
	cube1[2] = MyVector3(-1.0f, -5.0f, -11.0f);
	cube1[3] = MyVector3(1.0f, -5.0f, -11.0f);
	cube1[4] = MyVector3(1.0f, -3.0f, -13.0f);
	cube1[5] = MyVector3(-1.0f, -3.0f, -13.0f);
	cube1[6] = MyVector3(-1.0f, -5.0f, -13.0f);
	cube1[7] = MyVector3(1.0f, -5.0f, -13.0f);

	cube2[0] = MyVector3(1.0f, -3.0f, -15.0f);
	cube2[1] = MyVector3(-1.0f, -3.0f, -15.0f);
	cube2[2] = MyVector3(-1.0f, -5.0f, -15.0f);
	cube2[3] = MyVector3(1.0f, -5.0f, -15.0f);
	cube2[4] = MyVector3(1.0f, -3.0f, -17.0f);
	cube2[5] = MyVector3(-1.0f, -3.0f, -17.0f);
	cube2[6] = MyVector3(-1.0f, -5.0f, -17.0f);
	cube2[7] = MyVector3(1.0f, -5.0f, -17.0f);

	cube3[0] = MyVector3(1.0f, -3.0f, -21.0f);
	cube3[1] = MyVector3(-1.0f, -3.0f, -21.0f);
	cube3[2] = MyVector3(-1.0f, -5.0f, -21.0f);
	cube3[3] = MyVector3(1.0f, -5.0f, -21.0f);
	cube3[4] = MyVector3(1.0f, -3.0f, -23.0f);
	cube3[5] = MyVector3(-1.0f, -3.0f, -23.0f);
	cube3[6] = MyVector3(-1.0f, -5.0f, -23.0f);
	cube3[7] = MyVector3(1.0f, -5.0f, -23.0f);

	cube4[0] = MyVector3(1.0f, -3.0f, -25.0f);
	cube4[1] = MyVector3(-1.0f, -3.0f, -25.0f);
	cube4[2] = MyVector3(-1.0f, -5.0f, -25.0f);
	cube4[3] = MyVector3(1.0f, -5.0f, -25.0f);
	cube4[4] = MyVector3(1.0f, -3.0f, -27.0f);
	cube4[5] = MyVector3(-1.0f, -3.0f, -27.0f);
	cube4[6] = MyVector3(-1.0f, -5.0f, -27.0f);
	cube4[7] = MyVector3(1.0f, -5.0f, -27.0f);

	cube5[0] = MyVector3(1.0f, -3.0f, -31.0f);
	cube5[1] = MyVector3(-1.0f, -3.0f, -31.0f);
	cube5[2] = MyVector3(-1.0f, -5.0f, -31.0f);
	cube5[3] = MyVector3(1.0f, -5.0f, -31.0f);
	cube5[4] = MyVector3(1.0f, -3.0f, -33.0f);
	cube5[5] = MyVector3(-1.0f, -3.0f, -33.0f);
	cube5[6] = MyVector3(-1.0f, -5.0f, -33.0f);
	cube5[7] = MyVector3(1.0f, -5.0f, -33.0f);

	cube6[0] = MyVector3(1.0f, -3.0f, -35.0f);
	cube6[1] = MyVector3(-1.0f, -3.0f, -35.0f);
	cube6[2] = MyVector3(-1.0f, -5.0f, -35.0f);
	cube6[3] = MyVector3(1.0f, -5.0f, -35.0f);
	cube6[4] = MyVector3(1.0f, -3.0f, -37.0f);
	cube6[5] = MyVector3(-1.0f, -3.0f, -37.0f);
	cube6[6] = MyVector3(-1.0f, -5.0f, -37.0f);
	cube6[7] = MyVector3(1.0f, -5.0f, -37.0f);

	cube7[0] = MyVector3(1.0f, -3.0f, -41.0f);
	cube7[1] = MyVector3(-1.0f, -3.0f, -41.0f);
	cube7[2] = MyVector3(-1.0f, -5.0f, -41.0f);
	cube7[3] = MyVector3(1.0f, -5.0f, -41.0f);
	cube7[4] = MyVector3(1.0f, -3.0f, -43.0f);
	cube7[5] = MyVector3(-1.0f, -3.0f, -43.0f);
	cube7[6] = MyVector3(-1.0f, -5.0f, -43.0f);
	cube7[7] = MyVector3(1.0f, -5.0f, -43.0f);

	cube8[0] = MyVector3(1.0f, -3.0f, -45.0f);
	cube8[1] = MyVector3(-1.0f, -3.0f, -45.0f);
	cube8[2] = MyVector3(-1.0f, -5.0f, -45.0f);
	cube8[3] = MyVector3(1.0f, -5.0f, -45.0f);
	cube8[4] = MyVector3(1.0f, -3.0f, -47.0f);
	cube8[5] = MyVector3(-1.0f, -3.0f, -47.0f);
	cube8[6] = MyVector3(-1.0f, -5.0f, -47.0f);
	cube8[7] = MyVector3(1.0f, -5.0f, -47.0f);


	//corner1 = MyVector3(1.0f, -2.7439f, -11.5331f);
	//corner2 = MyVector3(-1.0f, -2.7439f, -11.5331f);
	//corner3 = MyVector3(-1.0f, -4.7438f, -11.5331f);
	//corner4 = MyVector3(1.0f, -4.7438f, -11.5331f);
	//corner5 = MyVector3(1.0f, -2.7439f, -13.5341f);
	//corner6 = MyVector3(-1.0f, -2.7439f, -13.5341f);
	//corner7 = MyVector3(-1.0f, -4.7438f, -13.5341f);
	//corner8 = MyVector3(1.0f, -4.7438f, -13.5341f);

	scale = scale.scale(99.9f, 99.9f);
	oppoScale = oppoScale.scale(99.9f, 99.9f);
	oppoScale = oppoScale.inverse();
	translateX = translateX.translateX(0.0001f, 0.0001f);
	oppoTranslateX = oppoTranslateX.translateX(-0.0001f, -0.0001f);
	translateY = translateY.translateY(0.0001f, 0.0001f);
	oppoTranslateY = oppoTranslateY.translateY(-0.0001f, -0.0001f);
	rotX = rotX.rotationX(rotationAngle);
	oppoRotX = oppoRotX.rotationX(-rotationAngle);
	rotY = rotY = rotY.rotationY(rotationAngle);
	oppoRotY = oppoRotY = oppoRotY.rotationY(-rotationAngle);
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
		glVertex3f(cube8[2].getX(), cube8[2].getY(), cube8[2].getZ());
		glVertex3f(cube8[3].getX(), cube8[3].getY(), cube8[3].getZ());
		glVertex3f(cube8[0].getX(), cube8[0].getY(), cube8[0].getZ());
		glVertex3f(cube8[1].getX(), cube8[1].getY(), cube8[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube8[5].getX(), cube8[5].getY(), cube8[5].getZ());
		glVertex3f(cube8[4].getX(), cube8[4].getY(), cube8[4].getZ());
		glVertex3f(cube8[7].getX(), cube8[7].getY(), cube8[7].getZ());
		glVertex3f(cube8[6].getX(), cube8[6].getY(), cube8[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube8[1].getX(), cube8[1].getY(), cube8[1].getZ());
		glVertex3f(cube8[0].getX(), cube8[0].getY(), cube8[0].getZ());
		glVertex3f(cube8[4].getX(), cube8[4].getY(), cube8[4].getZ());
		glVertex3f(cube8[5].getX(), cube8[5].getY(), cube8[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube8[6].getX(), cube8[6].getY(), cube8[6].getZ());
		glVertex3f(cube8[7].getX(), cube8[7].getY(), cube8[7].getZ());
		glVertex3f(cube8[3].getX(), cube8[3].getY(), cube8[3].getZ());
		glVertex3f(cube8[2].getX(), cube8[2].getY(), cube8[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube8[1].getX(), cube8[1].getY(), cube8[1].getZ());
		glVertex3f(cube8[5].getX(), cube8[5].getY(), cube8[5].getZ());
		glVertex3f(cube8[6].getX(), cube8[6].getY(), cube8[6].getZ());
		glVertex3f(cube8[2].getX(), cube8[2].getY(), cube8[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube8[7].getX(), cube8[7].getY(), cube8[7].getZ());
		glVertex3f(cube8[4].getX(), cube8[4].getY(), cube8[4].getZ());
		glVertex3f(cube8[0].getX(), cube8[0].getY(), cube8[0].getZ());
		glVertex3f(cube8[3].getX(), cube8[3].getY(), cube8[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube7[2].getX(), cube7[2].getY(), cube7[2].getZ());
		glVertex3f(cube7[3].getX(), cube7[3].getY(), cube7[3].getZ());
		glVertex3f(cube7[0].getX(), cube7[0].getY(), cube7[0].getZ());
		glVertex3f(cube7[1].getX(), cube7[1].getY(), cube7[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube7[5].getX(), cube7[5].getY(), cube7[5].getZ());
		glVertex3f(cube7[4].getX(), cube7[4].getY(), cube7[4].getZ());
		glVertex3f(cube7[7].getX(), cube7[7].getY(), cube7[7].getZ());
		glVertex3f(cube7[6].getX(), cube7[6].getY(), cube7[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube7[1].getX(), cube7[1].getY(), cube7[1].getZ());
		glVertex3f(cube7[0].getX(), cube7[0].getY(), cube7[0].getZ());
		glVertex3f(cube7[4].getX(), cube7[4].getY(), cube7[4].getZ());
		glVertex3f(cube7[5].getX(), cube7[5].getY(), cube7[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube7[6].getX(), cube7[6].getY(), cube7[6].getZ());
		glVertex3f(cube7[7].getX(), cube7[7].getY(), cube7[7].getZ());
		glVertex3f(cube7[3].getX(), cube7[3].getY(), cube7[3].getZ());
		glVertex3f(cube7[2].getX(), cube7[2].getY(), cube7[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube7[1].getX(), cube7[1].getY(), cube7[1].getZ());
		glVertex3f(cube7[5].getX(), cube7[5].getY(), cube7[5].getZ());
		glVertex3f(cube7[6].getX(), cube7[6].getY(), cube7[6].getZ());
		glVertex3f(cube7[2].getX(), cube7[2].getY(), cube7[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube7[7].getX(), cube7[7].getY(), cube7[7].getZ());
		glVertex3f(cube7[4].getX(), cube7[4].getY(), cube7[4].getZ());
		glVertex3f(cube7[0].getX(), cube7[0].getY(), cube7[0].getZ());
		glVertex3f(cube7[3].getX(), cube7[3].getY(), cube7[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube6[2].getX(), cube6[2].getY(), cube6[2].getZ());
		glVertex3f(cube6[3].getX(), cube6[3].getY(), cube6[3].getZ());
		glVertex3f(cube6[0].getX(), cube6[0].getY(), cube6[0].getZ());
		glVertex3f(cube6[1].getX(), cube6[1].getY(), cube6[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube6[5].getX(), cube6[5].getY(), cube6[5].getZ());
		glVertex3f(cube6[4].getX(), cube6[4].getY(), cube6[4].getZ());
		glVertex3f(cube6[7].getX(), cube6[7].getY(), cube6[7].getZ());
		glVertex3f(cube6[6].getX(), cube6[6].getY(), cube6[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube6[1].getX(), cube6[1].getY(), cube6[1].getZ());
		glVertex3f(cube6[0].getX(), cube6[0].getY(), cube6[0].getZ());
		glVertex3f(cube6[4].getX(), cube6[4].getY(), cube6[4].getZ());
		glVertex3f(cube6[5].getX(), cube6[5].getY(), cube6[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube6[6].getX(), cube6[6].getY(), cube6[6].getZ());
		glVertex3f(cube6[7].getX(), cube6[7].getY(), cube6[7].getZ());
		glVertex3f(cube6[3].getX(), cube6[3].getY(), cube6[3].getZ());
		glVertex3f(cube6[2].getX(), cube6[2].getY(), cube6[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube6[1].getX(), cube6[1].getY(), cube6[1].getZ());
		glVertex3f(cube6[5].getX(), cube6[5].getY(), cube6[5].getZ());
		glVertex3f(cube6[6].getX(), cube6[6].getY(), cube6[6].getZ());
		glVertex3f(cube6[2].getX(), cube6[2].getY(), cube6[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube6[7].getX(), cube6[7].getY(), cube6[7].getZ());
		glVertex3f(cube6[4].getX(), cube6[4].getY(), cube6[4].getZ());
		glVertex3f(cube6[0].getX(), cube6[0].getY(), cube6[0].getZ());
		glVertex3f(cube6[3].getX(), cube6[3].getY(), cube6[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube5[2].getX(), cube5[2].getY(), cube5[2].getZ());
		glVertex3f(cube5[3].getX(), cube5[3].getY(), cube5[3].getZ());
		glVertex3f(cube5[0].getX(), cube5[0].getY(), cube5[0].getZ());
		glVertex3f(cube5[1].getX(), cube5[1].getY(), cube5[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube5[5].getX(), cube5[5].getY(), cube5[5].getZ());
		glVertex3f(cube5[4].getX(), cube5[4].getY(), cube5[4].getZ());
		glVertex3f(cube5[7].getX(), cube5[7].getY(), cube5[7].getZ());
		glVertex3f(cube5[6].getX(), cube5[6].getY(), cube5[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube5[1].getX(), cube5[1].getY(), cube5[1].getZ());
		glVertex3f(cube5[0].getX(), cube5[0].getY(), cube5[0].getZ());
		glVertex3f(cube5[4].getX(), cube5[4].getY(), cube5[4].getZ());
		glVertex3f(cube5[5].getX(), cube5[5].getY(), cube5[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube5[6].getX(), cube5[6].getY(), cube5[6].getZ());
		glVertex3f(cube5[7].getX(), cube5[7].getY(), cube5[7].getZ());
		glVertex3f(cube5[3].getX(), cube5[3].getY(), cube5[3].getZ());
		glVertex3f(cube5[2].getX(), cube5[2].getY(), cube5[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube5[1].getX(), cube5[1].getY(), cube5[1].getZ());
		glVertex3f(cube5[5].getX(), cube5[5].getY(), cube5[5].getZ());
		glVertex3f(cube5[6].getX(), cube5[6].getY(), cube5[6].getZ());
		glVertex3f(cube5[2].getX(), cube5[2].getY(), cube5[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube5[7].getX(), cube5[7].getY(), cube5[7].getZ());
		glVertex3f(cube5[4].getX(), cube5[4].getY(), cube5[4].getZ());
		glVertex3f(cube5[0].getX(), cube5[0].getY(), cube5[0].getZ());
		glVertex3f(cube5[3].getX(), cube5[3].getY(), cube5[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube4[2].getX(), cube4[2].getY(), cube4[2].getZ());
		glVertex3f(cube4[3].getX(), cube4[3].getY(), cube4[3].getZ());
		glVertex3f(cube4[0].getX(), cube4[0].getY(), cube4[0].getZ());
		glVertex3f(cube4[1].getX(), cube4[1].getY(), cube4[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube4[5].getX(), cube4[5].getY(), cube4[5].getZ());
		glVertex3f(cube4[4].getX(), cube4[4].getY(), cube4[4].getZ());
		glVertex3f(cube4[7].getX(), cube4[7].getY(), cube4[7].getZ());
		glVertex3f(cube4[6].getX(), cube4[6].getY(), cube4[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube4[1].getX(), cube4[1].getY(), cube4[1].getZ());
		glVertex3f(cube4[0].getX(), cube4[0].getY(), cube4[0].getZ());
		glVertex3f(cube4[4].getX(), cube4[4].getY(), cube4[4].getZ());
		glVertex3f(cube4[5].getX(), cube4[5].getY(), cube4[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube4[6].getX(), cube4[6].getY(), cube4[6].getZ());
		glVertex3f(cube4[7].getX(), cube4[7].getY(), cube4[7].getZ());
		glVertex3f(cube4[3].getX(), cube4[3].getY(), cube4[3].getZ());
		glVertex3f(cube4[2].getX(), cube4[2].getY(), cube4[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube4[1].getX(), cube4[1].getY(), cube4[1].getZ());
		glVertex3f(cube4[5].getX(), cube4[5].getY(), cube4[5].getZ());
		glVertex3f(cube4[6].getX(), cube4[6].getY(), cube4[6].getZ());
		glVertex3f(cube4[2].getX(), cube4[2].getY(), cube4[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube4[7].getX(), cube4[7].getY(), cube4[7].getZ());
		glVertex3f(cube4[4].getX(), cube4[4].getY(), cube4[4].getZ());
		glVertex3f(cube4[0].getX(), cube4[0].getY(), cube4[0].getZ());
		glVertex3f(cube4[3].getX(), cube4[3].getY(), cube4[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube3[2].getX(), cube3[2].getY(), cube3[2].getZ());
		glVertex3f(cube3[3].getX(), cube3[3].getY(), cube3[3].getZ());
		glVertex3f(cube3[0].getX(), cube3[0].getY(), cube3[0].getZ());
		glVertex3f(cube3[1].getX(), cube3[1].getY(), cube3[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube3[5].getX(), cube3[5].getY(), cube3[5].getZ());
		glVertex3f(cube3[4].getX(), cube3[4].getY(), cube3[4].getZ());
		glVertex3f(cube3[7].getX(), cube3[7].getY(), cube3[7].getZ());
		glVertex3f(cube3[6].getX(), cube3[6].getY(), cube3[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube3[1].getX(), cube3[1].getY(), cube3[1].getZ());
		glVertex3f(cube3[0].getX(), cube3[0].getY(), cube3[0].getZ());
		glVertex3f(cube3[4].getX(), cube3[4].getY(), cube3[4].getZ());
		glVertex3f(cube3[5].getX(), cube3[5].getY(), cube3[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube3[6].getX(), cube3[6].getY(), cube3[6].getZ());
		glVertex3f(cube3[7].getX(), cube3[7].getY(), cube3[7].getZ());
		glVertex3f(cube3[3].getX(), cube3[3].getY(), cube3[3].getZ());
		glVertex3f(cube3[2].getX(), cube3[2].getY(), cube3[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube3[1].getX(), cube3[1].getY(), cube3[1].getZ());
		glVertex3f(cube3[5].getX(), cube3[5].getY(), cube3[5].getZ());
		glVertex3f(cube3[6].getX(), cube3[6].getY(), cube3[6].getZ());
		glVertex3f(cube3[2].getX(), cube3[2].getY(), cube3[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube3[7].getX(), cube3[7].getY(), cube3[7].getZ());
		glVertex3f(cube3[4].getX(), cube3[4].getY(), cube3[4].getZ());
		glVertex3f(cube3[0].getX(), cube3[0].getY(), cube3[0].getZ());
		glVertex3f(cube3[3].getX(), cube3[3].getY(), cube3[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube2[2].getX(), cube2[2].getY(), cube2[2].getZ());
		glVertex3f(cube2[3].getX(), cube2[3].getY(), cube2[3].getZ());
		glVertex3f(cube2[0].getX(), cube2[0].getY(), cube2[0].getZ());
		glVertex3f(cube2[1].getX(), cube2[1].getY(), cube2[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube2[5].getX(), cube2[5].getY(), cube2[5].getZ());
		glVertex3f(cube2[4].getX(), cube2[4].getY(), cube2[4].getZ());
		glVertex3f(cube2[7].getX(), cube2[7].getY(), cube2[7].getZ());
		glVertex3f(cube2[6].getX(), cube2[6].getY(), cube2[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube2[1].getX(), cube2[1].getY(), cube2[1].getZ());
		glVertex3f(cube2[0].getX(), cube2[0].getY(), cube2[0].getZ());
		glVertex3f(cube2[4].getX(), cube2[4].getY(), cube2[4].getZ());
		glVertex3f(cube2[5].getX(), cube2[5].getY(), cube2[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube2[6].getX(), cube2[6].getY(), cube2[6].getZ());
		glVertex3f(cube2[7].getX(), cube2[7].getY(), cube2[7].getZ());
		glVertex3f(cube2[3].getX(), cube2[3].getY(), cube2[3].getZ());
		glVertex3f(cube2[2].getX(), cube2[2].getY(), cube2[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube2[1].getX(), cube2[1].getY(), cube2[1].getZ());
		glVertex3f(cube2[5].getX(), cube2[5].getY(), cube2[5].getZ());
		glVertex3f(cube2[6].getX(), cube2[6].getY(), cube2[6].getZ());
		glVertex3f(cube2[2].getX(), cube2[2].getY(), cube2[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube2[7].getX(), cube2[7].getY(), cube2[7].getZ());
		glVertex3f(cube2[4].getX(), cube2[4].getY(), cube2[4].getZ());
		glVertex3f(cube2[0].getX(), cube2[0].getY(), cube2[0].getZ());
		glVertex3f(cube2[3].getX(), cube2[3].getY(), cube2[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cube1[2].getX(), cube1[2].getY(), cube1[2].getZ());
		glVertex3f(cube1[3].getX(), cube1[3].getY(), cube1[3].getZ());
		glVertex3f(cube1[0].getX(), cube1[0].getY(), cube1[0].getZ());
		glVertex3f(cube1[1].getX(), cube1[1].getY(), cube1[1].getZ());

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cube1[5].getX(), cube1[5].getY(), cube1[5].getZ());
		glVertex3f(cube1[4].getX(), cube1[4].getY(), cube1[4].getZ());
		glVertex3f(cube1[7].getX(), cube1[7].getY(), cube1[7].getZ());
		glVertex3f(cube1[6].getX(), cube1[6].getY(), cube1[6].getZ());

		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(cube1[1].getX(), cube1[1].getY(), cube1[1].getZ());
		glVertex3f(cube1[0].getX(), cube1[0].getY(), cube1[0].getZ());
		glVertex3f(cube1[4].getX(), cube1[4].getY(), cube1[4].getZ());
		glVertex3f(cube1[5].getX(), cube1[5].getY(), cube1[5].getZ());

		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(cube1[6].getX(), cube1[6].getY(), cube1[6].getZ());
		glVertex3f(cube1[7].getX(), cube1[7].getY(), cube1[7].getZ());
		glVertex3f(cube1[3].getX(), cube1[3].getY(), cube1[3].getZ());
		glVertex3f(cube1[2].getX(), cube1[2].getY(), cube1[2].getZ());


		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(cube1[1].getX(), cube1[1].getY(), cube1[1].getZ());
		glVertex3f(cube1[5].getX(), cube1[5].getY(), cube1[5].getZ());
		glVertex3f(cube1[6].getX(), cube1[6].getY(), cube1[6].getZ());
		glVertex3f(cube1[2].getX(), cube1[2].getY(), cube1[2].getZ());

		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(cube1[7].getX(), cube1[7].getY(), cube1[7].getZ());
		glVertex3f(cube1[4].getX(), cube1[4].getY(), cube1[4].getZ());
		glVertex3f(cube1[0].getX(), cube1[0].getY(), cube1[0].getZ());
		glVertex3f(cube1[3].getX(), cube1[3].getY(), cube1[3].getZ());

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		
		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		
		//Top Face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		
		//Bottom Face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		
	
		//Left Face
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(corner2.getX(), corner2.getY(), corner2.getZ());
		glVertex3f(corner6.getX(), corner6.getY(), corner6.getZ());
		glVertex3f(corner7.getX(), corner7.getY(), corner7.getZ());
		glVertex3f(corner3.getX(), corner3.getY(), corner3.getZ());
		
		//Right Face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(corner8.getX(), corner8.getY(), corner8.getZ());
		glVertex3f(corner5.getX(), corner5.getY(), corner5.getZ());
		glVertex3f(corner1.getX(), corner1.getY(), corner1.getZ());
		glVertex3f(corner4.getX(), corner4.getY(), corner4.getZ());
		
		//Complete the faces of the Cube
	
	}
	glEnd();

	glEndList();

	glCullFace(GL_BACK);
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

	if (keyPressed.isKeyPressed(sf::Keyboard::P))
	{
		for (int i = 0; i < 8; i++)
		{
			cube1[i] = MyVector3(cube1[i].getX(), cube1[i].getY(), cube1[i].getZ() + 0.01f);
			cube2[i] = MyVector3(cube2[i].getX(), cube2[i].getY(), cube2[i].getZ() + 0.01f);
			cube3[i] = MyVector3(cube3[i].getX(), cube3[i].getY(), cube3[i].getZ() + 0.01f);
			cube4[i] = MyVector3(cube4[i].getX(), cube4[i].getY(), cube4[i].getZ() + 0.01f);
			cube5[i] = MyVector3(cube5[i].getX(), cube5[i].getY(), cube5[i].getZ() + 0.01f);
			cube6[i] = MyVector3(cube6[i].getX(), cube6[i].getY(), cube6[i].getZ() + 0.01f);
			cube7[i] = MyVector3(cube7[i].getX(), cube7[i].getY(), cube7[i].getZ() + 0.01f);
			cube8[i] = MyVector3(cube8[i].getX(), cube8[i].getY(), cube8[i].getZ() + 0.01f);
		}
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::W))
	{
		//Trying to rotate while jumping
		//Fix the origin that it is rotating around
		float yOffset = corner1.getY() - 0.5f;
		float zOffset = 12.5f;
		//float zOffset = -corner1.getZ() - 0.5f;
		corner1.setY(corner1.getY() + yOffset);
		corner2.setY(corner2.getY() + yOffset);
		corner3.setY(corner3.getY() + yOffset);
		corner4.setY(corner4.getY() + yOffset);
		corner5.setY(corner5.getY() + yOffset);
		corner6.setY(corner6.getY() + yOffset);
		corner7.setY(corner7.getY() + yOffset);
		corner8.setY(corner8.getY() + yOffset);
		corner1.setZ(corner1.getZ() + zOffset);
		corner2.setZ(corner2.getZ() + zOffset);
		corner3.setZ(corner3.getZ() + zOffset);
		corner4.setZ(corner4.getZ() + zOffset);
		corner5.setZ(corner5.getZ() + zOffset);
		corner6.setZ(corner6.getZ() + zOffset);
		corner7.setZ(corner7.getZ() + zOffset);
		corner8.setZ(corner8.getZ() + zOffset);
		corner1 = rotX * corner1;
		corner2 = rotX * corner2;
		corner3 = rotX * corner3;
		corner4 = rotX * corner4;
		corner5 = rotX * corner5;
		corner6 = rotX * corner6;
		corner7 = rotX * corner7;
		corner8 = rotX * corner8;
		corner1.setY(corner1.getY() - yOffset);
		corner2.setY(corner2.getY() - yOffset);
		corner3.setY(corner3.getY() - yOffset);
		corner4.setY(corner4.getY() - yOffset);
		corner5.setY(corner5.getY() - yOffset);
		corner6.setY(corner6.getY() - yOffset);
		corner7.setY(corner7.getY() - yOffset);
		corner8.setY(corner8.getY() - yOffset);
		corner1.setZ(corner1.getZ() - zOffset);
		corner2.setZ(corner2.getZ() - zOffset);
		corner3.setZ(corner3.getZ() - zOffset);
		corner4.setZ(corner4.getZ() - zOffset);
		corner5.setZ(corner5.getZ() - zOffset);
		corner6.setZ(corner6.getZ() - zOffset);
		corner7.setZ(corner7.getZ() - zOffset);
		corner8.setZ(corner8.getZ() - zOffset);
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::S))
	{
		corner1.setZ(corner1.getZ() + 6.0f);
		corner2.setZ(corner2.getZ() + 6.0f);
		corner3.setZ(corner3.getZ() + 6.0f);
		corner4.setZ(corner4.getZ() + 6.0f);
		corner5.setZ(corner5.getZ() + 6.0f);
		corner6.setZ(corner6.getZ() + 6.0f);
		corner7.setZ(corner7.getZ() + 6.0f);
		corner8.setZ(corner8.getZ() + 6.0f);
		corner1 = oppoRotX * corner1;
		corner2 = oppoRotX * corner2;
		corner3 = oppoRotX * corner3;
		corner4 = oppoRotX * corner4;
		corner5 = oppoRotX * corner5;
		corner6 = oppoRotX * corner6;
		corner7 = oppoRotX * corner7;
		corner8 = oppoRotX * corner8;
		corner1.setZ(corner1.getZ() - 6.0f);
		corner2.setZ(corner2.getZ() - 6.0f);
		corner3.setZ(corner3.getZ() - 6.0f);
		corner4.setZ(corner4.getZ() - 6.0f);
		corner5.setZ(corner5.getZ() - 6.0f);
		corner6.setZ(corner6.getZ() - 6.0f);
		corner7.setZ(corner7.getZ() - 6.0f);
		corner8.setZ(corner8.getZ() - 6.0f);
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::A))
	{
		corner1.setZ(corner1.getZ() + 6.0f);
		corner2.setZ(corner2.getZ() + 6.0f);
		corner3.setZ(corner3.getZ() + 6.0f);
		corner4.setZ(corner4.getZ() + 6.0f);
		corner5.setZ(corner5.getZ() + 6.0f);
		corner6.setZ(corner6.getZ() + 6.0f);
		corner7.setZ(corner7.getZ() + 6.0f);
		corner8.setZ(corner8.getZ() + 6.0f);
		corner1 = rotY * corner1;
		corner2 = rotY * corner2;
		corner3 = rotY * corner3;
		corner4 = rotY * corner4;
		corner5 = rotY * corner5;
		corner6 = rotY * corner6;
		corner7 = rotY * corner7;
		corner8 = rotY * corner8;
		corner1.setZ(corner1.getZ() - 6.0f);
		corner2.setZ(corner2.getZ() - 6.0f);
		corner3.setZ(corner3.getZ() - 6.0f);
		corner4.setZ(corner4.getZ() - 6.0f);
		corner5.setZ(corner5.getZ() - 6.0f);
		corner6.setZ(corner6.getZ() - 6.0f);
		corner7.setZ(corner7.getZ() - 6.0f);
		corner8.setZ(corner8.getZ() - 6.0f);

 

	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::D))
	{
		corner1.setZ(corner1.getZ() + 6.0f);
		corner2.setZ(corner2.getZ() + 6.0f);
		corner3.setZ(corner3.getZ() + 6.0f);
		corner4.setZ(corner4.getZ() + 6.0f);
		corner5.setZ(corner5.getZ() + 6.0f);
		corner6.setZ(corner6.getZ() + 6.0f);
		corner7.setZ(corner7.getZ() + 6.0f);
		corner8.setZ(corner8.getZ() + 6.0f);
		corner1 = oppoRotY * corner1;
		corner2 = oppoRotY * corner2;
		corner3 = oppoRotY * corner3;
		corner4 = oppoRotY * corner4;
		corner5 = oppoRotY * corner5;
		corner6 = oppoRotY * corner6;
		corner7 = oppoRotY * corner7;
		corner8 = oppoRotY * corner8;
		corner1.setZ(corner1.getZ() - 6.0f);
		corner2.setZ(corner2.getZ() - 6.0f);
		corner3.setZ(corner3.getZ() - 6.0f);
		corner4.setZ(corner4.getZ() - 6.0f);
		corner5.setZ(corner5.getZ() - 6.0f);
		corner6.setZ(corner6.getZ() - 6.0f);
		corner7.setZ(corner7.getZ() - 6.0f);
		corner8.setZ(corner8.getZ() - 6.0f);
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::Q))
	{
		corner1.setZ(corner1.getZ() + 6.0f);
		corner2.setZ(corner2.getZ() + 6.0f);
		corner3.setZ(corner3.getZ() + 6.0f);
		corner4.setZ(corner4.getZ() + 6.0f);
		corner5.setZ(corner5.getZ() + 6.0f);
		corner6.setZ(corner6.getZ() + 6.0f);
		corner7.setZ(corner7.getZ() + 6.0f);
		corner8.setZ(corner8.getZ() + 6.0f);
		corner1 = rotZ * corner1;
		corner2 = rotZ * corner2;
		corner3 = rotZ * corner3;
		corner4 = rotZ * corner4;
		corner5 = rotZ * corner5;
		corner6 = rotZ * corner6;
		corner7 = rotZ * corner7;
		corner8 = rotZ * corner8;
		corner1.setZ(corner1.getZ() - 6.0f);
		corner2.setZ(corner2.getZ() - 6.0f);
		corner3.setZ(corner3.getZ() - 6.0f);
		corner4.setZ(corner4.getZ() - 6.0f);
		corner5.setZ(corner5.getZ() - 6.0f);
		corner6.setZ(corner6.getZ() - 6.0f);
		corner7.setZ(corner7.getZ() - 6.0f);
		corner8.setZ(corner8.getZ() - 6.0f);
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::E))
	{
		corner1.setZ(corner1.getZ() + 6.0f);
		corner2.setZ(corner2.getZ() + 6.0f);
		corner3.setZ(corner3.getZ() + 6.0f);
		corner4.setZ(corner4.getZ() + 6.0f);
		corner5.setZ(corner5.getZ() + 6.0f);
		corner6.setZ(corner6.getZ() + 6.0f);
		corner7.setZ(corner7.getZ() + 6.0f);
		corner8.setZ(corner8.getZ() + 6.0f);
		corner1 = oppoRotZ * corner1;
		corner2 = oppoRotZ * corner2;
		corner3 = oppoRotZ * corner3;
		corner4 = oppoRotZ * corner4;
		corner5 = oppoRotZ * corner5;
		corner6 = oppoRotZ * corner6;
		corner7 = oppoRotZ * corner7;
		corner8 = oppoRotZ * corner8; 
		corner1.setZ(corner1.getZ() - 6.0f);
		corner2.setZ(corner2.getZ() - 6.0f);
		corner3.setZ(corner3.getZ() - 6.0f);
		corner4.setZ(corner4.getZ() - 6.0f);
		corner5.setZ(corner5.getZ() - 6.0f);
		corner6.setZ(corner6.getZ() - 6.0f);
		corner7.setZ(corner7.getZ() - 6.0f);
		corner8.setZ(corner8.getZ() - 6.0f);
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::X))
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
	else if (keyPressed.isKeyPressed(sf::Keyboard::Z))
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

	if (keyPressed.isKeyPressed(sf::Keyboard::Left))
	{
		//corner1.setZ(corner1.getZ() + 6.0f);
		//corner2.setZ(corner2.getZ() + 6.0f);
		//corner3.setZ(corner3.getZ() + 6.0f);
		//corner4.setZ(corner4.getZ() + 6.0f);
		//corner5.setZ(corner5.getZ() + 6.0f);
		//corner6.setZ(corner6.getZ() + 6.0f);
		//corner7.setZ(corner7.getZ() + 6.0f);
		//corner8.setZ(corner8.getZ() + 6.0f);
		//corner1 = translateX * corner1;
		//corner2 = translateX * corner2;
		//corner3 = translateX * corner3;
		//corner4 = translateX * corner4;
		//corner5 = translateX * corner5;
		//corner6 = translateX * corner6;
		//corner7 = translateX * corner7;
		//corner8 = translateX * corner8;
		//corner1.setZ(corner1.getZ() - 6.0f);
		//corner2.setZ(corner2.getZ() - 6.0f);
		//corner3.setZ(corner3.getZ() - 6.0f);
		//corner4.setZ(corner4.getZ() - 6.0f);
		//corner5.setZ(corner5.getZ() - 6.0f);
		//corner6.setZ(corner6.getZ() - 6.0f);
		//corner7.setZ(corner7.getZ() - 6.0f);
		//corner8.setZ(corner8.getZ() - 6.0f);

		corner1 = MyVector3(corner1.getX() - 0.001f, corner1.getY(), corner1.getZ());
		corner2 = MyVector3(corner2.getX() - 0.001f, corner2.getY(), corner2.getZ());
		corner3 = MyVector3(corner3.getX() - 0.001f, corner3.getY(), corner3.getZ());
		corner4 = MyVector3(corner4.getX() - 0.001f, corner4.getY(), corner4.getZ());
		corner5 = MyVector3(corner5.getX() - 0.001f, corner5.getY(), corner5.getZ());
		corner6 = MyVector3(corner6.getX() - 0.001f, corner6.getY(), corner6.getZ());
		corner7 = MyVector3(corner7.getX() - 0.001f, corner7.getY(), corner7.getZ());
		corner8 = MyVector3(corner8.getX() - 0.001f, corner8.getY(), corner8.getZ());

	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::Right))
	{
		//corner1.setZ(corner1.getZ() + 6.0f);
		//corner2.setZ(corner2.getZ() + 6.0f);
		//corner3.setZ(corner3.getZ() + 6.0f);
		//corner4.setZ(corner4.getZ() + 6.0f);
		//corner5.setZ(corner5.getZ() + 6.0f);
		//corner6.setZ(corner6.getZ() + 6.0f);
		//corner7.setZ(corner7.getZ() + 6.0f);
		//corner8.setZ(corner8.getZ() + 6.0f);
		//corner1 = oppoTranslateX * corner1;
		//corner2 = oppoTranslateX * corner2;
		//corner3 = oppoTranslateX * corner3;
		//corner4 = oppoTranslateX * corner4;
		//corner5 = oppoTranslateX * corner5;
		//corner6 = oppoTranslateX * corner6;
		//corner7 = oppoTranslateX * corner7;
		//corner8 = oppoTranslateX * corner8;
		//corner1.setZ(corner1.getZ() - 6.0f);
		//corner2.setZ(corner2.getZ() - 6.0f);
		//corner3.setZ(corner3.getZ() - 6.0f);
		//corner4.setZ(corner4.getZ() - 6.0f);
		//corner5.setZ(corner5.getZ() - 6.0f);
		//corner6.setZ(corner6.getZ() - 6.0f);
		//corner7.setZ(corner7.getZ() - 6.0f);
		//corner8.setZ(corner8.getZ() - 6.0f);

		corner1 = MyVector3(corner1.getX() + 0.001f, corner1.getY(), corner1.getZ());
		corner2 = MyVector3(corner2.getX() + 0.001f, corner2.getY(), corner2.getZ());
		corner3 = MyVector3(corner3.getX() + 0.001f, corner3.getY(), corner3.getZ());
		corner4 = MyVector3(corner4.getX() + 0.001f, corner4.getY(), corner4.getZ());
		corner5 = MyVector3(corner5.getX() + 0.001f, corner5.getY(), corner5.getZ());
		corner6 = MyVector3(corner6.getX() + 0.001f, corner6.getY(), corner6.getZ());
		corner7 = MyVector3(corner7.getX() + 0.001f, corner7.getY(), corner7.getZ());
		corner8 = MyVector3(corner8.getX() + 0.001f, corner8.getY(), corner8.getZ());
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::Up))
	{
		//corner1 = translateY * corner1;
		//corner2 = translateY * corner2;
		//corner3 = translateY * corner3;
		//corner4 = translateY * corner4;
		//corner5 = translateY * corner5;
		//corner6 = translateY * corner6;
		//corner7 = translateY * corner7;
		//corner8 = translateY * corner8;
		corner1 = MyVector3(corner1.getX(), corner1.getY() + 0.001f, corner1.getZ());
		corner2 = MyVector3(corner2.getX(), corner2.getY() + 0.001f, corner2.getZ());
		corner3 = MyVector3(corner3.getX(), corner3.getY() + 0.001f, corner3.getZ());
		corner4 = MyVector3(corner4.getX(), corner4.getY() + 0.001f, corner4.getZ());
		corner5 = MyVector3(corner5.getX(), corner5.getY() + 0.001f, corner5.getZ());
		corner6 = MyVector3(corner6.getX(), corner6.getY() + 0.001f, corner6.getZ());
		corner7 = MyVector3(corner7.getX(), corner7.getY() + 0.001f, corner7.getZ());
		corner8 = MyVector3(corner8.getX(), corner8.getY() + 0.001f, corner8.getZ());
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::Down))
	{
		//corner1 = oppoTranslateY * corner1;
		//corner2 = oppoTranslateY * corner2;
		//corner3 = oppoTranslateY * corner3;
		//corner4 = oppoTranslateY * corner4;
		//corner5 = oppoTranslateY * corner5;
		//corner6 = oppoTranslateY * corner6;
		//corner7 = oppoTranslateY * corner7;
		//corner8 = oppoTranslateY * corner8;
		corner1 = MyVector3(corner1.getX(), corner1.getY() - 0.001f, corner1.getZ());
		corner2 = MyVector3(corner2.getX(), corner2.getY() - 0.001f, corner2.getZ());
		corner3 = MyVector3(corner3.getX(), corner3.getY() - 0.001f, corner3.getZ());
		corner4 = MyVector3(corner4.getX(), corner4.getY() - 0.001f, corner4.getZ());
		corner5 = MyVector3(corner5.getX(), corner5.getY() - 0.001f, corner5.getZ());
		corner6 = MyVector3(corner6.getX(), corner6.getY() - 0.001f, corner6.getZ());
		corner7 = MyVector3(corner7.getX(), corner7.getY() - 0.001f, corner7.getZ());
		corner8 = MyVector3(corner8.getX(), corner8.getY() - 0.001f, corner8.getZ());
	}

	if (keyPressed.isKeyPressed(sf::Keyboard::J))
	{
		//corner1 = translateY * corner1;
		//corner2 = translateY * corner2;
		//corner3 = translateY * corner3;
		//corner4 = translateY * corner4;
		//corner5 = translateY * corner5;
		//corner6 = translateY * corner6;
		//corner7 = translateY * corner7;
		//corner8 = translateY * corner8;
		corner1 = MyVector3(corner1.getX(), corner1.getY() , corner1.getZ()+ 0.001f);
		corner2 = MyVector3(corner2.getX(), corner2.getY() , corner2.getZ()+ 0.001f);
		corner3 = MyVector3(corner3.getX(), corner3.getY() , corner3.getZ()+ 0.001f);
		corner4 = MyVector3(corner4.getX(), corner4.getY() , corner4.getZ()+ 0.001f);
		corner5 = MyVector3(corner5.getX(), corner5.getY() , corner5.getZ()+ 0.001f);
		corner6 = MyVector3(corner6.getX(), corner6.getY() , corner6.getZ()+ 0.001f);
		corner7 = MyVector3(corner7.getX(), corner7.getY() , corner7.getZ()+ 0.001f);
		corner8 = MyVector3(corner8.getX(), corner8.getY() , corner8.getZ()+ 0.001f);
	}
	else if (keyPressed.isKeyPressed(sf::Keyboard::K))
	{
		//corner1 = oppoTranslateY * corner1;
		//corner2 = oppoTranslateY * corner2;
		//corner3 = oppoTranslateY * corner3;
		//corner4 = oppoTranslateY * corner4;
		//corner5 = oppoTranslateY * corner5;
		//corner6 = oppoTranslateY * corner6;
		//corner7 = oppoTranslateY * corner7;
		//corner8 = oppoTranslateY * corner8;
		corner1 = MyVector3(corner1.getX(), corner1.getY() , corner1.getZ()- 0.001f);
		corner2 = MyVector3(corner2.getX(), corner2.getY() , corner2.getZ()- 0.001f);
		corner3 = MyVector3(corner3.getX(), corner3.getY() , corner3.getZ()- 0.001f);
		corner4 = MyVector3(corner4.getX(), corner4.getY() , corner4.getZ()- 0.001f);
		corner5 = MyVector3(corner5.getX(), corner5.getY() , corner5.getZ()- 0.001f);
		corner6 = MyVector3(corner6.getX(), corner6.getY() , corner6.getZ()- 0.001f);
		corner7 = MyVector3(corner7.getX(), corner7.getY() , corner7.getZ()- 0.001f);
		corner8 = MyVector3(corner8.getX(), corner8.getY() , corner8.getZ()- 0.001f);
	}
	
	if (keyPressed.isKeyPressed(sf::Keyboard::Space))
	{
		jump = true;
	}

	//get the time since last update and restart the clock
	timeSinceLastUpdate += clock.restart();

	timeChange = timeSinceLastUpdate.asSeconds();

	if (jump == true)
	{
		float zOffeset = corner1.getZ() - 0.5f;
		corner1.setZ(corner1.getZ() + zOffeset);
		corner2.setZ(corner2.getZ() + zOffeset);
		corner3.setZ(corner3.getZ() + zOffeset);
		corner4.setZ(corner4.getZ() + zOffeset);
		corner5.setZ(corner5.getZ() + zOffeset);
		corner6.setZ(corner6.getZ() + zOffeset);
		corner7.setZ(corner7.getZ() + zOffeset);
		corner8.setZ(corner8.getZ() + zOffeset);
		corner1 = rotX * corner1;
		corner2 = rotX * corner2;
		corner3 = rotX * corner3;
		corner4 = rotX * corner4;
		corner5 = rotX * corner5;
		corner6 = rotX * corner6;
		corner7 = rotX * corner7;
		corner8 = rotX * corner8;
		corner1.setZ(corner1.getZ() - zOffeset);
		corner2.setZ(corner2.getZ() - zOffeset);
		corner3.setZ(corner3.getZ() - zOffeset);
		corner4.setZ(corner4.getZ() - zOffeset);
		corner5.setZ(corner5.getZ() - zOffeset);
		corner6.setZ(corner6.getZ() - zOffeset);
		corner7.setZ(corner7.getZ() - zOffeset);
		corner8.setZ(corner8.getZ() - zOffeset);
		totalTime = totalTime + timeChange;
		corner1.setY(corner1.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner2.setY(corner2.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner3.setY(corner3.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner4.setY(corner4.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner5.setY(corner5.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner6.setY(corner6.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner7.setY(corner7.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		corner8.setY(corner8.getY() + velocity.getY() * timeChange + 0.5 * gravity.getY() * (timeChange* timeChange));
		velocity.setY(velocity.getY() + gravity.getY() * timeChange);
		if (corner8.getY() <= -3.0f && safe == true)
		{
			corner1.setY(-2.0f);
			corner2.setY(-2.0f);
			corner3.setY(-3.0f);
			corner4.setY(-3.0f);
			corner5.setY(-2.0f);
			corner6.setY(-2.0f);
			corner7.setY(-3.0f);
			corner8.setY(-3.0f);
			jump = false;
			velocity.setY(6.0f);
		}
	}

	if (safe == false && corner8.getY() <= -3.0f)
	{
		exit;
	}
	else if (safe == false && jump == false)
	{
		corner1 = MyVector3(corner1.getX(), corner1.getY() - 0.001f, corner1.getZ());
		corner2 = MyVector3(corner2.getX(), corner2.getY() - 0.001f, corner2.getZ());
		corner3 = MyVector3(corner3.getX(), corner3.getY() - 0.001f, corner3.getZ());
		corner4 = MyVector3(corner4.getX(), corner4.getY() - 0.001f, corner4.getZ());
		corner5 = MyVector3(corner5.getX(), corner5.getY() - 0.001f, corner5.getZ());
		corner6 = MyVector3(corner6.getX(), corner6.getY() - 0.001f, corner6.getZ());
		corner7 = MyVector3(corner7.getX(), corner7.getY() - 0.001f, corner7.getZ());
		corner8 = MyVector3(corner8.getX(), corner8.getY() - 0.001f, corner8.getZ());
	}

	if (cube1[0].getZ() < corner8.getZ() || cube1[8].getZ() >  corner1.getZ() && jump != true)
	{
		safe = false;
	}

	timeSinceLastUpdate = sf::Time::Zero;

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

/// <summary>
/// Method to see if a point is facing towards or away from the screen
/// </summary>
/// <param name="sender"></param>
/// <param name="e"></param>
bool Game::showVertex(MyVector3 v1, MyVector3 v2, MyVector3 v3)
{
	v2 = v2 - v1;
	v3 = v3 - v1;
	if ((v2.crossProduct(v3)).getZ() < 0)
	{//Facing screen
		return true;
	}
	else
	{// Facing away from screen
		return false;
	}
}
#include <Game.h>
#include <Cube.h>

GLuint	vsid,		// Vertex Shader ID
		fsid,		// Fragment Shader ID
		progID,		// Program ID
		vao = 0,	// Vertex Array ID
		vbo,		// Vertex Buffer ID
		vib,		// Vertex Index Buffer
		to,			// Texture ID 1 to 32
		positionID,	// Position ID
		colorID,	// Color ID
		textureID,	// Texture ID
		uvID,		// UV ID
		mvpID;		// Model View Projection ID;

//const string filename = "coordinates.tga";
//const string filename = "cube.tga";
//const string filename = "grid.tga";
//const string filename = "grid_wip.tga";
//const string filename = "minecraft.tga";
const string filename = "texture.tga";
//const string filename = "texture_2.tga";
//const string filename = "uvtemplate.tga";


int width;			// Width of texture
int height;			// Height of texture
int comp_count;		// Component of texture

unsigned char* img_data;		// image data

mat4 mvp, projection, view, playerModel;			// Model View Projection

Game::Game() : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing"),
	playerCube()
{
}

Game::Game(sf::ContextSettings settings) : 
	window(VideoMode(800, 600), 
	"Introduction to OpenGL Texturing", 
	sf::Style::Default, 
	settings),
	playerCube()
	//enemyCube()
{
	for (int i = 0; i < S_NUMOFENEMIES; i++)
	{

		rnd = rand() % 4;
		enemyModel[i] = translate(enemyModel[i], glm::vec3(0, 0, -20 * rnd));
		zOffset = -20 * rnd - 100;

		rnd = (rand() % 2) + 1;
		if (rnd == 1)
		{
			sign = false;
		}
		else
		{
			sign = true;
		}
		rnd = rand() % 4;

		if (sign)
		{
			rnd = -rnd;
		}
		
		enemyModel[i] = translate(enemyModel[i], glm::vec3(rnd * 5.0f, 0, -100));
		enemyCube[i] = EnemyCube(glm::vec3(rnd * 5.0f, 0, zOffset));


	}

}

Game::~Game(){}


void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jump && !fall)
			{
				jump = true;
			}

			playerCube.update();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// Set Model Rotation
				//model = rotate(model, 0.01f, glm::vec3(0, 1, 0)); // Rotate
				playerModel = translate(playerModel, glm::vec3(-0.1,0,0));
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// Set Model Rotation
				//model = rotate(model, -0.01f, glm::vec3(0, 1, 0)); // Rotate
				playerModel = translate(playerModel, glm::vec3(0.1, 0, 0));
			}

		}

		update();
		render();
	}

#if (DEBUG >= 2)
	DEBUG_MSG("Calling Cleanup...");
#endif
	unload();

}

void Game::initialize()
{
	gravity = MyVector3(0, 9.8, 0);

	velocity = MyVector3(0, 0, 0);
	totalTime = 0;
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	//Copy UV's to all faces
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	glGenVertexArrays(1, &vao); //Gen Vertex Array
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo); //Gen Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Vertices 3 x,y,z , Colors 4 RGBA, UV/ST 2
	glBufferData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS) + (2 * UVS)) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &vib); //Gen Vertex Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vib);

	//Indices to be drawn
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);

	vertexInput.open("vertexShader.txt");
	vss << vertexInput.rdbuf();
	vsLine = vss.str();
	const char* vs_src = vsLine.c_str();

	//const char* vs_src = 
	//	"#version 400\n\r"
	//	""
	//	//"layout(location = 0) in vec3 sv_position; //Use for individual Buffers"
	//	//"layout(location = 1) in vec4 sv_color; //Use for individual Buffers"
	//	//"layout(location = 2) in vec2 sv_texel; //Use for individual Buffers"
	//	""
	//	"in vec3 sv_position;"
	//	"in vec4 sv_color;"
	//	"in vec2 sv_uv;"
	//	""
	//	"out vec4 color;"
	//	"out vec2 uv;"
	//	""
	//	"uniform mat4 sv_mvp;"
	//	""
	//	"void main() {"
	//	"	color = sv_color;"
	//	"	uv = sv_uv;"
	//	//"	gl_Position = vec4(sv_position, 1);"
	//	"	gl_Position = sv_mvp * vec4(sv_position, 1);"
	//	"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
	glCompileShader(vsid);

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	fragInput.open("fragShader.txt");
	ss << fragInput.rdbuf();
	line = ss.str();
	const char* fs_src = line.c_str();

	//const char* fs_src =
	//	"#version 400\n\r"
	//	""
	//	"uniform sampler2D f_texture;"
	//	""
	//	"in vec4 color;"
	//	"in vec2 uv;"
	//	""
	//	"out vec4 fColor;"
	//	""
	//	"void main() {"
	//	//"	vec4 lightColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); "
	//	//"	fColor = vec4(0.50f, 0.50f, 0.50f, 1.0f);"
	//	//"	fColor = texture2D(f_texture, uv);"
	//	//"	fColor = color * texture2D(f_texture, uv);"
	//	//"	fColor = lightColor * texture2D(f_texture, uv);"
	//	//"	fColor = color + texture2D(f_texture, uv);"
	//	//"	fColor = color - texture2D(f_texture, uv);"
	//	"	fColor = color;"
	//	"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);

	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();
	glAttachShader(progID, vsid);
	glAttachShader(progID, fsid);
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	//Use Progam on GPU
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(
		GL_TEXTURE_2D,		//2D Texture Image
		0,					//Mipmapping Level 
		GL_RGBA,			//GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width,				//Width
		height,				//Height
		0,					//Border
		GL_RGBA,			//Bitmap
		GL_UNSIGNED_BYTE,	//Specifies Data type of image data
		img_data			//Image Data
		);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	uvID = glGetAttribLocation(progID, "sv_uv");
	textureID = glGetUniformLocation(progID, "f_texture");
	mvpID = glGetUniformLocation(progID, "sv_mvp");

	// Projection Matrix 
	projection = perspective(
		45.0f,					// Field of View 45 degrees
		4.0f / 3.0f,			// Aspect ratio
		5.0f,					// Display Range Min : 0.1f unit
		100.0f					// Display Range Max : 100.0f unit
		);

	// Camera Matrix
	view = lookAt(
		vec3(0.0f, 4.0f, 10.0f),	// Camera (x,y,z), in World Space
		vec3(0.0f, 0.0f, 0.0f),	// Camera looking at origin
		vec3(0.0f, 1.0f, 0.0f)	// 0.0f, 1.0f, 0.0f Look Down and 0.0f, -1.0f, 0.0f Look Up
		);

	// Model matrix
	playerModel = mat4(
		1.0f					// Identity Matrix
		);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Updating...");
#endif
	// Update Model View Projection.
	

	for (int i = 0; i < S_NUMOFENEMIES; i++)
	{
		if (enemyCube[i].getPos().z > 6)
		{
			rnd = (rand() % 2) + 1;
			if (rnd == 1)
			{
				sign = false;
			}
			else
			{
				sign = true;
			}
			rnd = rand() % 4;

			if (sign)
			{
				rnd = -rnd;
			}

			//Centering cubes
			enemyModel[i] = translate(enemyModel[i], glm::vec3(-enemyCube[i].getPos().x, 0, 0));

			enemyModel[i] = translate(enemyModel[i], glm::vec3(rnd * 5.0f, 0, -106));
			enemyCube[i] = EnemyCube(glm::vec3(rnd * 5.0f, 0, -100));
		}
		else
		{
			enemyModel[i] = translate(enemyModel[i], glm::vec3(0, 0, 0.02f));
		}
	}
	
	timeSinceLastUpdate += clock.restart();
	timeChange = timeSinceLastUpdate.asSeconds();
	//totalTime = totalTime + timeChange;

	for (int i = 0; i < S_NUMOFENEMIES; i++)
	{
		enemyCube[i].update();
		if (checkCollision(playerCube.getPos(), enemyCube[i].getPos()))
		{
			window.close();
		}
	}

	

	//mvp = projection * view * model1;
}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Render Loop...");
#endif

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(progID);

	cubeMaker(playerModel);
	for (int i = 0; i < S_NUMOFENEMIES; i++)
	{
		cubeMaker(enemyModel[i]);
	}

	window.display();
	
	//Disable Arrays
	glDisableVertexAttribArray(positionID);
	glDisableVertexAttribArray(colorID);
	glDisableVertexAttribArray(uvID);

}

void Game::cubeMaker(mat4 &model)
{
	mvp = projection * view * model;

	//VBO Data....vertices, colors and UV's appended
	glBufferSubData(GL_ARRAY_BUFFER, 0 * VERTICES * sizeof(GLfloat), 3 * VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * VERTICES * sizeof(GLfloat), 4 * COLORS * sizeof(GLfloat), colors);
	glBufferSubData(GL_ARRAY_BUFFER, ((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat), 2 * UVS * sizeof(GLfloat), uvs);

	// Send transformation to shader mvp uniform
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	//Set pointers for each parameter (with appropriate starting positions)
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glVertexAttribPointer.xml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, (VOID*)(3 * VERTICES * sizeof(GLfloat)));
	glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, (VOID*)(((3 * VERTICES) + (4 * COLORS)) * sizeof(GLfloat)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(uvID);

	
	//Draw Element Arrays
	glDrawElements(GL_TRIANGLES, 3 * INDICES, GL_UNSIGNED_INT, NULL);


}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);	//Delete Shader
	glDeleteBuffers(1, &vbo);	//Delete Vertex Buffer
	glDeleteBuffers(1, &vib);	//Delete Vertex Index Buffer
	//stbi_image_free(img_data);		//Free image
}

bool Game::checkCollision(vec3 player, vec3 enemy)
{
	
	if (player.z <= enemy.z + 1.5 && player.x >= enemy.x - 2 && player.x <= enemy.x + 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


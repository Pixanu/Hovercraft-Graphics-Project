#include "Game_Hovecraft.h"

//private functions

void Game_Hovercraft::initGLFW()
{
	//INTI GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INITIALIZATION_FAILED " << "\n";
		glfwTerminate();
	}

}

void Game_Hovercraft::initWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this-> window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);


	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_INITIALIZATION_FAILED" << "\n";
		glfwTerminate();
	}


	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwSetFramebufferSizeCallback(window, Game_Hovercraft::framebuffer_resize_callback);

	//glViewport(0, 0, framebufferWidth, framebufferHeight);


	glfwMakeContextCurrent(this->window);//IMPORTANT 
}

void Game_Hovercraft::initGLEW()
{
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//ERROR
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::Main_Hovercraft.cpp::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game_Hovercraft::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//input
	//DISABLE ON-SCREEN CURSOR
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game_Hovercraft::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->CamFront, this->worldUp);


	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);

}

void Game_Hovercraft::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, "vertex_core.glsl", "fragment_core.glsl"));
}

void Game_Hovercraft::initTextures()
{
	//TESTING TEXTURES//

	//---------------------//
	this->textures.push_back(new Texture("Images/thanos.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/thanos_specular.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("Images/crate.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/crate_specular.png", GL_TEXTURE_2D));
	//---------------------//


	this->textures.push_back(new Texture("Images/grass.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/grass_specular.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("Images/water.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/water_specular.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("Images/wood.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Images/wood_specular.png", GL_TEXTURE_2D));

}



void Game_Hovercraft::initMaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.5f), glm::vec3(1.f), glm::vec3(5.f),
		0, 1));

}

void Game_Hovercraft::initModels()
{
	std::vector<Mesh*>meshes;

	//TESTING WITH MESHES ZONE


	//---------------------//
	/*meshes.push_back(
		new Mesh(&Pyramid(),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	this->models.push_back(new Model(
		glm::vec3(0.f),
		this->materials[0],
		this->textures[TEX_CRATE],
		this->textures[TEX_CRATE_SPECULAR],
		meshes
		)
	);

	this->models.push_back(new Model(
		glm::vec3(0.f, 1.f, 1.f),
		this->materials[0],
		this->textures[TEX_THANOS],
		this->textures[TEX_THANOS_SPECULAR],
		meshes
		)
	);
	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_CRATE],
		this->textures[TEX_CRATE_SPECULAR],
		meshes
		)
	);*/

	//---------------------//

	//PLANE
	this->models.push_back(new Model(
		glm::vec3(0.f, 0.f, 0.f),
		this->materials[0],
		this->textures[TEX_GRASS],
		this->textures[TEX_GRASS_SPECULAR],
		"OBJFiles/plane_final.obj"
		)
	);

	//HOVERCRAFT
	this->models.push_back(new Model(
		glm::vec3(-50.f, -1.f, 0.f),
		this->materials[0],
		this->textures[TEX_WOOD],
		this->textures[TEX_WOOD_SPECULAR],
		"OBJFiles/hover_final.obj"
	)
	);

	//TRACK
	this->models.push_back(new Model(
		glm::vec3(0.f, -6.5f, 0.f),
		this->materials[0],
		this->textures[TEX_WATER],
		this->textures[TEX_WATER_SPECULAR],
		"OBJFiles/track_final.obj"
	)
	);

	

	for (auto*& i : meshes)
		delete i;

}
	
void Game_Hovercraft::initOBJModels()
{
	
}

void Game_Hovercraft::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 0.f));
}

void Game_Hovercraft::initUniforms()
{
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	
}

void Game_Hovercraft::updateUniforms()
{

	//UPDATE VIEW MATRIX
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");

	//UPDATE UNIFORM
	this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

	//UPDATE FRAMEBUFFER SIZE AND PROJECTION MATRIX
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);


	ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}



//CONSTRUCTORS--/--DESTRUCTORS
Game_Hovercraft::Game_Hovercraft(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable)
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),

	//INITIAL CAMERA-----POSITION--/--DIRECTION--/--WORLDUP
	camera(glm::vec3(-50.f, 4.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{

	//INIT VARIABLES
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;


	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->CamFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->deltaTime = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastmouseX = 0.f;
	this->lastmouseY = 0.f;
	this->mouseX = 0.f;
	this->mouseY = 0.f;
	this->mouseOFFsetX = 0.f;
	this->mouseOFFsetY = 0.f;
	this->firstMouse = true;


	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initOBJModels();
	this->initModels();
	this->initLights();
	this->initUniforms();
}

Game_Hovercraft::~Game_Hovercraft()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];

	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];

	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];

	for (auto& i : this->models)
		delete i;

	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}

//ACCESORS
int Game_Hovercraft::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//MODIFIERS
void Game_Hovercraft::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}


//FUNCTIONS

void Game_Hovercraft::updateDeltaTime()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->deltaTime = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

}

void Game_Hovercraft::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastmouseX = this->mouseX;
		this->lastmouseY = this->mouseY;
		this->firstMouse = false;
	}

	//OFFSET CALCULATION
	this->mouseOFFsetX = this->mouseX - this->lastmouseX;
	this->mouseOFFsetY = this->lastmouseY - this->mouseY;

	//STTING LAST X&Y
	this->lastmouseX = this->mouseX;
	this->lastmouseY = this->mouseY;

	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		*this->lights[0] = this->camera.getPosition();
	}

}

void Game_Hovercraft::updateKeyboardInput()
{
	//PROGRAM EXIT
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//CAMERA MOVEMENT
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTime, RIGHT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camPosition.y += 0.05f;
	}
	
}

void Game_Hovercraft::updateInput()
{

	glfwPollEvents();
	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(deltaTime, -1, this->mouseOFFsetX, this->mouseOFFsetY);
}


void Game_Hovercraft::update()
{
	//UPDATE INPUT
	this->updateDeltaTime();
	this->updateInput();

	//MODELS ROTATION TESTING
	//---------------------//

	/*this->models[0]->rotate(glm::vec3(0.f, 0.1f, 0.f));
	this->models[1]->rotate(glm::vec3(0.f, 0.1f, 0.f));
	this->models[2]->rotate(glm::vec3(0.f, 0.1f, 0.f));*/

	//---------------------//


	//DELTATIME CHECKING 

	//std::cout << "DT:" << this->deltaTime << "\n"
		//<< " Mouse offsetX: " << this->mouseOFFsetX << " Mouse offsetY: " << this->mouseOFFsetY << "\n";
	
	
	
	//FUNTION NO LONGER WORKING
	//---------------------//

	//this->updateInput(this->window, *this->meshes[MESH_QUAD]);

	//---------------------//
}

void Game_Hovercraft::render()
{

	//UPDATE

	//updateInput(window);

	//DRAW ---
	//CLEAR
	glClearColor(0.f, 0.5f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	//UPDATE THE UNIFORMS
	this->updateUniforms();

	//RENDER MODELS

	for(auto& i : this->models)
		i -> render(this->shaders[SHADER_CORE_PROGRAM]);

	//END DRAW
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//STATIC FUNCTIONS
void Game_Hovercraft::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
};

/*void Game_Hovercraft::updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void Game_Hovercraft::updateInput(GLFWwindow* window, Mesh& mesh)
{
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
	}
	/*if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(1.f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		mesh.scaleUp(glm::vec3(-1.f));
	}

}*/

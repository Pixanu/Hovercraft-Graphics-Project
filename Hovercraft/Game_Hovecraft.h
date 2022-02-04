#pragma once

#include "libs.h"
#include "Camera.h"


//ENUMERATION
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_THANOS = 0, TEX_THANOS_SPECULAR, TEX_CRATE, TEX_CRATE_SPECULAR, TEX_GRASS, TEX_GRASS_SPECULAR, TEX_WATER, TEX_WATER_SPECULAR, TEX_WOOD, TEX_WOOD_SPECULAR};
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };




class Game_Hovercraft
{
private:
//VARIABLES
	//WINDOW
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;
	
	//OPENGL CONTEXT
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;


	//DELTATIME
	float deltaTime;
	float curTime;
	float lastTime;

	//MOUSE INPUT
	double lastmouseX;
	double lastmouseY;
	double mouseX;
	double mouseY;
	double mouseOFFsetX;
	double mouseOFFsetY;
	bool firstMouse;

	//CAMERA
	Camera camera;


	//MATRICES
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 CamFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;


	//SHADERS
	std::vector<Shader*> shaders;

	//TEXTURES
	std::vector<Texture*> textures;

	//MATERIALS
	std::vector<Material*> materials;

	
	
	//MODELS
	std::vector<Model*> models;

	//LIGHTS
	std::vector<glm::vec3*> lights;

//PRIVATE FUNCTIONS

	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //after context creation
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initOBJModels();
	void initModels();
	void initLights();
	void initUniforms();
	void updateUniforms();

//STATIC VARIABLES
	
public:

	//CONSTRUCTORS / DESTRUCTORS
	Game_Hovercraft(const char* title, const int WINDOWS_WIDTH, const int WINDOWS_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR, bool resizable);
	virtual ~Game_Hovercraft();


	//ACCESORS
	int getWindowShouldClose();
	
	//MODIFIERS
	void setWindowShouldClose();
	//FUNCTIONS
	void updateDeltaTime();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();


	//STATIC FUNCTIONS
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);



	//don t need them 
	/*static void updateInput(GLFWwindow* window);
	static void updateInput(GLFWwindow* window, Mesh& mesh);*/
	//this should not be static
	
	
};


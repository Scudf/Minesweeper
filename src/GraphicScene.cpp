#include "stdafx.h"
#include "GraphicScene.h"

#include <wtypes.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "pngLoader.h"

#include "Game.h"
#include "GameScene.h"


GraphicScene::GraphicScene()
	: m_blockSize(100.0f)
	, m_width(0)
	, m_height(0)
	, m_lightDirection(0.0f, 0.15f, -1.0f)
	, m_lightAmbient(0.2f)
	, m_lightDiffuse(0.5f)
	, m_lightSpecular(0.5f)
	, m_isLightDirty(true)
{

}

GraphicScene::~GraphicScene()
{
	glfwTerminate();
}

bool GraphicScene::initialize()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	m_width = desktop.right;
	m_height = desktop.bottom;

	m_window = glfwCreateWindow(m_width, m_height, "Minesweeper", /*glfwGetPrimaryMonitor()*/nullptr, nullptr);

	if (m_window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	GLint width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	m_camera = Camera::Create();

	loadTexture("Flag.png");
	loadTexture("One.png");
	loadTexture("Two.png");
	loadTexture("Three.png");
	loadTexture("Four.png");
	loadTexture("Five.png");
	loadTexture("Six.png");
	loadTexture("Seven.png");
	loadTexture("Eight.png");
	loadTexture("Bomb.png");
	loadTexture("Unpressed.png");
	loadTexture("Pressed.png");
	loadTexture("LiveSmile.png");
	loadTexture("DeadSmile.png");
	loadTexture("WinnerSmile.png");
	loadTexture("Beginner.png");
	loadTexture("Intermediate.png");
	loadTexture("Expert.png");
	loadTexture("Exit.png");
	loadTexture("TZero.png");
	loadTexture("TOne.png");
	loadTexture("TTwo.png");
	loadTexture("TThree.png");
	loadTexture("TFour.png");
	loadTexture("TFive.png");
	loadTexture("TSix.png");
	loadTexture("TSeven.png");
	loadTexture("TEight.png");
	loadTexture("TNine.png");

	loadShader("simpleShader", "simpleShaderV.glsl", "simpleShaderF.glsl");
	loadShader("normalsShader", "normalsShaderV.glsl", "normalsShaderF.glsl");
	loadShader("texturesShader", "texturesShaderV.glsl", "texturesShaderF.glsl");
	loadShader("mixShader", "texturesShaderV.glsl", "mixShaderF.glsl");

	loadModels();

	return true;
}

bool GraphicScene::update(float dt)
{
	if (glfwWindowShouldClose(m_window))
		return false;

	glfwPollEvents();

	glClearColor(0.0f, 0.5f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GameScene* gs = Game::GetInstancePtr()->getGameScene();

	if(gs->isCameraFree())
		m_matView = m_camera->getFreeViewMatrix();
	else
		m_matView = m_camera->getTargetViewMatrix();

	m_matPersp = glm::perspective(glm::radians(m_camera->getZoom()), (GLfloat)m_width / m_height, 0.1f, 6400.0f);

	for (GraphicObjPtr object : m_objects)
		object->render();

	m_isLightDirty = false;

	glfwSwapBuffers(m_window);

	return true;
}

void GraphicScene::loadTexture(const std::string &imagePath)
{
	std::string prefix = "../res/textures/";

	GLuint textureID;
	glGenTextures(1, &textureID);
	PngTexData texData;
	loadPng((prefix + imagePath).c_str(), texData);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if(texData.alphaChannel)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texData.width, texData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data.get());
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texData.width, texData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData.data.get());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	m_textures[imagePath] = textureID;
}



void GraphicScene::loadModels()
{
	// Line
	ModelPtr lineModel = Model::Create();
	lineModel->createModel2V(glm::vec2(12800.0f, 0.0f));
	m_models["line"] = lineModel;

	// Plane
	ModelPtr normPlaneModel = Model::Create();
	normPlaneModel->createModel4V(NORMALS, glm::vec2(m_blockSize, m_blockSize));
	m_models["normPlane"] = normPlaneModel;

	ModelPtr texPlaneModel = Model::Create();
	texPlaneModel->createModel4V(TEXTURES, glm::vec2(m_blockSize, m_blockSize));
	m_models["texPlane"] = texPlaneModel;

	// Cube
	ModelPtr simpCubeModel = Model::Create();
	simpCubeModel->createModel36V(SIMPLE, glm::vec3(m_blockSize, m_blockSize, m_blockSize));
	m_models["simpCube"] = simpCubeModel;

	ModelPtr normCubeModel = Model::Create();
	normCubeModel->createModel36V(NORMALS, glm::vec3(m_blockSize, m_blockSize, m_blockSize));
	m_models["normCube"] = normCubeModel;

	ModelPtr texCubeModel = Model::Create();
	texCubeModel->createModel36V(TEXTURES, glm::vec3(m_blockSize, m_blockSize, m_blockSize));
	m_models["texCube"] = texCubeModel;

	// Cell
	ModelPtr simpCellModel = Model::Create();
	simpCellModel->createModel36V(SIMPLE, glm::vec3(90.0f, 90.0f, 60.0f), glm::vec3(0.5f, 0.5f, 0.0f));
	m_models["simpCell"] = simpCellModel;

	ModelPtr normCellModel = Model::Create();
	normCellModel->createModel36V(NORMALS, glm::vec3(90.0f, 90.0f, 60.0f), glm::vec3(0.5f, 0.5f, 0.0f));
	m_models["normCell"] = normCellModel;

	ModelPtr texCellModel = Model::Create();
	texCellModel->createModel36V(TEXTURES, glm::vec3(90.0f, 90.0f, 60.0f), glm::vec3(0.5f, 0.5f, 0.0f));
	m_models["texCell"] = texCellModel;

	// Number
	ModelPtr texNumberModel = Model::Create();
	texNumberModel->createModel36V(TEXTURES, glm::vec3(30.0f, 90.0f, 60.0f), glm::vec3(0.5f, 0.5f, 0.0f));
	m_models["texNumber"] = texNumberModel;
}

void GraphicScene::loadShader(
	const std::string& shaderName,
	const std::string& vertexFileName,
	const std::string& fragmentFileName)
{
	std::string prefix = "../res/shaders/";
	ShaderPtr shader = Shader::Create((prefix + vertexFileName).c_str(), (prefix + fragmentFileName).c_str());
	m_shaders[shaderName] = shader;
}

void GraphicScene::addObject(const GraphicObjPtr& object)
{
	m_objects.push_back(object);
}

void GraphicScene::removeObject(const GraphicObjPtr& object)
{
	removeObject(object.get());
}

void GraphicScene::removeObject(GraphicObj* object)
{
	for (std::vector<GraphicObjPtr>::iterator	it = m_objects.begin(),
												end = m_objects.end();
												it != end;
												++it)
	{
		if ((*it).get() == object)
		{
			m_objects.erase(it);
			return;
		}
	}
}
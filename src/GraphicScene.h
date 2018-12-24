#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "GraphicObj.h"


class GraphicScene
{
public:
	GraphicScene();
	~GraphicScene();

	bool initialize();
	bool update(float dt);

	void loadTexture(const std::string& imagePath);
	void loadShader(
		const std::string& shaderName,
		const std::string& vertexFileName,
		const std::string& fragmentFileName);

	void addObject(const GraphicObjPtr& object);
	void removeObject(const GraphicObjPtr& object);
	void removeObject(GraphicObj* object);

	inline float getBlockSize() const { return m_blockSize; }

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	
	inline GLFWwindow* getWindow() const { return m_window; }
	inline const CameraPtr&	getCamera() const { return m_camera; }
	
	inline GLuint getGLTexture(const std::string &imagePath) const { return m_textures.at(imagePath); }
	inline const ShaderPtr& getGLShader(const std::string &shaderName) const { return m_shaders.at(shaderName); }
	inline const ModelPtr& getModel(const std::string &modelName) const { return m_models.at(modelName); }
	
	inline const glm::mat4& getMatView() const { return m_matView; }
	inline const glm::mat4& getMatPersp() const { return m_matPersp; }
	
	inline const glm::vec3& getLightDirection() const { return m_lightDirection; }

	inline const glm::vec3& getLightAmbient() const { return m_lightAmbient; }
	inline const glm::vec3& getLightDiffuse() const { return m_lightDiffuse; }
	inline const glm::vec3& getLightSpecular() const { return m_lightSpecular; }

	inline bool isLightDirty() const { return m_isLightDirty; }
	
	inline void setBlockSize(float blockSize) { m_blockSize = blockSize; }

	inline void setWidth(int width) { m_width = width; }
	inline void setHeight(int height) { m_height = height; }

	inline void setLightDirection(const glm::vec3 &lightDir)
	{
		m_lightDirection = lightDir;

		m_isLightDirty = true;
	}

	inline void setLightDirection(float x, float y, float z)
	{
		m_lightDirection.x = x;
		m_lightDirection.y = y;
		m_lightDirection.z = z;

		m_isLightDirty = true;
	}

	inline void setLightAmbient(const glm::vec3 &lightAmb)
	{
		m_lightAmbient = lightAmb;

		m_isLightDirty = true;
	}

	inline void setLightAmbient(float x, float y, float z)
	{
		m_lightAmbient.x = x;
		m_lightAmbient.y = y;
		m_lightAmbient.z = z;

		m_isLightDirty = true;
	}

	inline void setLightDiffuse(const glm::vec3 &lightDiff)
	{
		m_lightDiffuse = lightDiff;

		m_isLightDirty = true;
	}

	inline void setLightDiffuse(float x, float y, float z)
	{
		m_lightDiffuse.x = x;
		m_lightDiffuse.y = y;
		m_lightDiffuse.z = z;

		m_isLightDirty = true;
	}

	inline void setLightSpecular(const glm::vec3 &lightSpec)
	{
		m_lightSpecular = lightSpec;

		m_isLightDirty = true;
	}

	inline void setLightSpecular(float x, float y, float z)
	{
		m_lightSpecular.x = x;
		m_lightSpecular.y = y;
		m_lightSpecular.z = z;

		m_isLightDirty = true;
	}

	inline void setLightDirty(bool isLightDirty) { m_isLightDirty = isLightDirty; }

private:
	void loadModels();

private:
	float m_blockSize;

	int m_width;
	int m_height;

	GLFWwindow* m_window;
	CameraPtr m_camera;

	std::map<std::string, GLuint> m_textures;
	std::map<std::string, ShaderPtr> m_shaders;
	std::map<std::string, ModelPtr> m_models;

	glm::mat4 m_matView;
	glm::mat4 m_matPersp;

	glm::vec3 m_lightDirection;

	glm::vec3 m_lightAmbient;
	glm::vec3 m_lightDiffuse;
	glm::vec3 m_lightSpecular;

	bool m_isLightDirty;

	std::vector<GraphicObjPtr> m_objects;
};


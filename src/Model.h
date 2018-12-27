#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>


using ModelPtr = std::shared_ptr<class Model>;

enum VAOconfig
{
	SIMPLE = 2,
	NORMALS = 5,
	TEXTURES = 7
};

enum class ModelType
{
	V2,
	V4,
	V36
};

enum Metric
{
	METRIC_2D,
	METRIC_3D
};

struct TexCoords
{
	glm::vec4 topUV;
	glm::vec4 bottomUV;
	glm::vec4 rightUV;
	glm::vec4 leftUV;
	glm::vec4 frontUV;
	glm::vec4 backUV;

	TexCoords()
		: topUV(0.0f, 0.0f, 1.0f, 1.0f)
		, bottomUV(0.0f, 0.0f, 1.0f, 1.0f)
		, rightUV(0.0f, 0.0f, 1.0f, 1.0f)
		, leftUV(0.0f, 0.0f, 1.0f, 1.0f)
		, frontUV(0.0f, 0.0f, 1.0f, 1.0f)
		, backUV(0.0f, 0.0f, 1.0f, 1.0f)
	{}
};

struct Bounds
{
	glm::vec2 xAxis;
	glm::vec2 yAxis;
	glm::vec2 zAxis;

	Bounds()
		: xAxis(0)
		, yAxis(0)
		, zAxis(0)
	{}
};

class Model
{
public:
	static ModelPtr Create() { return std::make_shared<Model>(); }

	Model();
	
	bool createModel2V(
		const glm::vec2& lineLenght = glm::vec2(1.0f, 1.0f),
		const glm::vec2& anchorPoint = glm::vec2(0.0f, 0.0f));

	bool createModel4V(
		VAOconfig vaoConfig = TEXTURES,
		const glm::vec2& planeSize = glm::vec2(1.0f, 1.0f),
		const glm::vec2& anchorPoint = glm::vec2(0.0f, 0.0f),
		const TexCoords& texCoords = TexCoords());

	bool createModel36V(
		VAOconfig vaoConfig = TEXTURES,
		const glm::vec3& cubeSize = glm::vec3(1.0f, 1.0f, 1.0f),
		const glm::vec3& anchorPoint = glm::vec3(0.5f, 0.5f, 0.5f),
		const TexCoords& texCoords = TexCoords());

	inline GLuint getVAO() const { return m_VAO; }
	inline GLuint getVBO() const { return m_VAO; }

	inline VAOconfig getVAOConfig() const { return m_vaoConfig; }
	inline ModelType getModelType() const { return m_modelType; }

	inline Bounds getBounds() const { return m_bounds; }

private:
	void createVAO(
		const std::vector<GLfloat> &vector,
		int vectorSize,
		VAOconfig vaoConfig,
		int metric);

private:
	GLuint m_VAO;
	GLuint m_VBO;

	VAOconfig m_vaoConfig;
	ModelType m_modelType;

	Bounds m_bounds;
};


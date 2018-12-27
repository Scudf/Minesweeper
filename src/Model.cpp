#include "stdafx.h"
#include "Model.h"


Model::Model()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
}

bool Model::createModel2V(
	const glm::vec2& lineLenght,
	const glm::vec2& anchorPoint)
{
	std::vector<GLfloat> lineVertices;

	float x1 = -(anchorPoint.x * lineLenght.x);
	float y1 = -(anchorPoint.y * lineLenght.y);

	float x2 = (1.0f - anchorPoint.x) * lineLenght.x;
	float y2 = (1.0f - anchorPoint.y) * lineLenght.y;

	m_bounds.xAxis = glm::vec2(x1, x2);
	m_bounds.yAxis = glm::vec2(y1, y2);

	lineVertices = {
		x1,	y1,
		x2,	y2
	};

	createVAO(lineVertices, lineVertices.size(), SIMPLE, METRIC_2D);
	m_vaoConfig = SIMPLE;
	m_modelType = ModelType::V2;

	return true;
}

bool Model::createModel4V(
	VAOconfig vaoConfig,
	const glm::vec2& planeSize,
	const glm::vec2& anchorPoint,
	const TexCoords& texCoords)
{
	std::vector<GLfloat> planeVertices;
	
	float x1 = -(anchorPoint.x * planeSize.x);
	float y1 = -(anchorPoint.y * planeSize.y);

	float x2 = (1.0f - anchorPoint.x) * planeSize.x;
	float y2 = (1.0f - anchorPoint.y) * planeSize.y;

	m_bounds.xAxis = glm::vec2(x1, x2);
	m_bounds.yAxis = glm::vec2(y1, y2);

	switch (vaoConfig)
	{
	case TEXTURES:
		planeVertices = {
			x1,	y1,	0.0f, 0.0f, 1.0f,	texCoords.frontUV.x, texCoords.frontUV.z,
			x2,	y1,	0.0f, 0.0f, 1.0f,	texCoords.frontUV.z, texCoords.frontUV.z,
			x1,	y2,	0.0f, 0.0f, 1.0f,	texCoords.frontUV.x, texCoords.frontUV.y,
			x2,	y2,	0.0f, 0.0f, 1.0f,	texCoords.frontUV.z, texCoords.frontUV.y
		};
		break;

	case NORMALS:
		planeVertices = {
			x1,	y1,	0.0f, 0.0f, 1.0f,
			x2,	y1,	0.0f, 0.0f, 1.0f,
			x1,	y2,	0.0f, 0.0f, 1.0f,
			x2,	y2,	0.0f, 0.0f, 1.0f
		};
		break;

	case SIMPLE:
		planeVertices = {
			x1,	y1,
			x2,	y1,
			x1,	y2,
			x2,	y2
		};
		break;

	}

	createVAO(planeVertices, planeVertices.size(), vaoConfig, METRIC_2D);
	m_vaoConfig = vaoConfig;
	m_modelType = ModelType::V4;

	return true;
}

bool Model::createModel36V(
	VAOconfig vaoConfig,
	const glm::vec3& cubeSize,
	const glm::vec3& anchorPoint,
	const TexCoords& texCoords)
{
	std::vector<GLfloat> cubeVertices;

	float x1 = -(anchorPoint.x * cubeSize.x);
	float y1 = -(anchorPoint.y * cubeSize.y);
	float z1 = -(anchorPoint.z * cubeSize.z);

	float x2 = (1.0f - anchorPoint.x) * cubeSize.x;
	float y2 = (1.0f - anchorPoint.y) * cubeSize.y;
	float z2 = (1.0f - anchorPoint.z) * cubeSize.z;

	m_bounds.xAxis = glm::vec2(x1, x2);
	m_bounds.yAxis = glm::vec2(y1, y2);
	m_bounds.zAxis = glm::vec2(z1, z2);

	switch (vaoConfig)
	{
	case TEXTURES:
		/*
				1---------------2
			   /|		       /|
			  / |		      / |
			 /  |			 /  |
			3---------------4   |
			|   |			|   |
			|   |			|   |
			|   5-----------|---6
			|  /			|  /
			| /				| /
			|/				|/
			7---------------8
		*/

		cubeVertices = {
			// 1243 Top side
	/*1*/	x1, y2, z1,  0.0f,  1.0f,  0.0f,  texCoords.topUV.z, texCoords.topUV.w,
	/*2*/	x2, y2, z1,  0.0f,  1.0f,  0.0f,  texCoords.topUV.x, texCoords.topUV.w,
	/*4*/	x2, y2, z2,  0.0f,  1.0f,  0.0f,  texCoords.topUV.x, texCoords.topUV.y,
	/*4*/	x2, y2, z2,  0.0f,  1.0f,  0.0f,  texCoords.topUV.x, texCoords.topUV.y,
	/*3*/	x1, y2, z2,  0.0f,  1.0f,  0.0f,  texCoords.topUV.z, texCoords.topUV.y,
	/*1*/	x1, y2, z1,  0.0f,  1.0f,  0.0f,  texCoords.topUV.z, texCoords.topUV.w,

			// 6578 Bottom side
	/*5*/	x1, y1, z1,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.x, texCoords.bottomUV.w,
	/*6*/	x2, y1, z1,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.z, texCoords.bottomUV.w,
	/*8*/	x2, y1, z2,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.z, texCoords.bottomUV.y,
	/*8*/	x2, y1, z2,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.z, texCoords.bottomUV.y,
	/*7*/	x1, y1, z2,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.x, texCoords.bottomUV.y,
	/*5*/	x1, y1, z1,  0.0f, -1.0f,  0.0f,  texCoords.bottomUV.x, texCoords.bottomUV.w,

			// 4268 Right side
	/*4*/	x2, y2, z2,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.z, texCoords.rightUV.y,
	/*2*/	x2, y2, z1,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.z, texCoords.rightUV.w,
	/*6*/	x2, y1, z1,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.x, texCoords.rightUV.w,
	/*6*/	x2, y1, z1,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.x, texCoords.rightUV.w,
	/*8*/	x2, y1, z2,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.x, texCoords.rightUV.y,
	/*4*/	x2, y2, z2,  1.0f,  0.0f,  0.0f,  texCoords.rightUV.z, texCoords.rightUV.y,

			// 1375 Left side
	/*3*/	x1, y2, z2, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.x, texCoords.leftUV.y,
	/*1*/	x1, y2, z1, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.x, texCoords.leftUV.w,
	/*5*/	x1, y1, z1, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.z, texCoords.leftUV.w,
	/*5*/	x1, y1, z1, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.z, texCoords.leftUV.w,
	/*7*/	x1, y1, z2, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.z, texCoords.leftUV.y,
	/*3*/	x1, y2, z2, -1.0f,  0.0f,  0.0f,  texCoords.leftUV.x, texCoords.leftUV.y,

			// 3487 Front side
	/*7*/	x1, y1, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.x, texCoords.frontUV.w,
	/*8*/	x2, y1, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.z, texCoords.frontUV.w,
	/*4*/	x2, y2, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.z, texCoords.frontUV.y,
	/*4*/	x2, y2, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.z, texCoords.frontUV.y,
	/*3*/	x1, y2, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.x, texCoords.frontUV.y,
	/*7*/	x1, y1, z2,  0.0f,  0.0f,  1.0f,  texCoords.frontUV.x, texCoords.frontUV.w,

			// 2156 Back side
	/*5*/	x1, y1, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.z, texCoords.backUV.w,
	/*6*/	x2, y1, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.x, texCoords.backUV.w,
	/*2*/	x2, y2, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.x, texCoords.backUV.y,
	/*2*/	x2, y2, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.x, texCoords.backUV.y,
	/*1*/	x1, y2, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.z, texCoords.backUV.y,
	/*5*/	x1, y1, z1,  0.0f,  0.0f, -1.0f,  texCoords.backUV.z, texCoords.backUV.w
		};

		break;

	case NORMALS:
		/*
				1---------------2
			   /|		       /|
			  / |		      / |
			 /  |			 /  |
			3---------------4   |
			|   |			|   |
			|   |			|   |
			|   5-----------|---6
			|  /			|  /
			| /				| /
			|/				|/
			7---------------8
		*/

		cubeVertices = {
			// 1243 Top side
	/*1*/	x1, y2, z1,  0.0f,  1.0f,  0.0f,
	/*2*/	x2, y2, z1,  0.0f,  1.0f,  0.0f,
	/*4*/	x2, y2, z2,  0.0f,  1.0f,  0.0f,
	/*4*/	x2, y2, z2,  0.0f,  1.0f,  0.0f,
	/*3*/	x1, y2, z2,  0.0f,  1.0f,  0.0f,
	/*1*/	x1, y2, z1,  0.0f,  1.0f,  0.0f,

			// 6578 Bottom side
	/*5*/	x1, y1, z1,  0.0f, -1.0f,  0.0f,
	/*6*/	x2, y1, z1,  0.0f, -1.0f,  0.0f,
	/*8*/	x2, y1, z2,  0.0f, -1.0f,  0.0f,
	/*8*/	x2, y1, z2,  0.0f, -1.0f,  0.0f,
	/*7*/	x1, y1, z2,  0.0f, -1.0f,  0.0f,
	/*5*/	x1, y1, z1,  0.0f, -1.0f,  0.0f,
		
			// 4268 Right side
	/*4*/	x2, y2, z2,  1.0f,  0.0f,  0.0f,
	/*2*/	x2, y2, z1,  1.0f,  0.0f,  0.0f,
	/*6*/	x2, y1, z1,  1.0f,  0.0f,  0.0f,
	/*6*/	x2, y1, z1,  1.0f,  0.0f,  0.0f,
	/*8*/	x2, y1, z2,  1.0f,  0.0f,  0.0f,
	/*4*/	x2, y2, z2,  1.0f,  0.0f,  0.0f,
		
			// 1375 Left side
	/*3*/	x1, y2, z2, -1.0f,  0.0f,  0.0f,
	/*1*/	x1, y2, z1, -1.0f,  0.0f,  0.0f,
	/*5*/	x1, y1, z1, -1.0f,  0.0f,  0.0f,
	/*5*/	x1, y1, z1, -1.0f,  0.0f,  0.0f,
	/*7*/	x1, y1, z2, -1.0f,  0.0f,  0.0f,
	/*3*/	x1, y2, z2, -1.0f,  0.0f,  0.0f,
		
			// 3487 Front side
	/*7*/	x1, y1, z2,  0.0f,  0.0f,  1.0f,
	/*8*/	x2, y1, z2,  0.0f,  0.0f,  1.0f,
	/*4*/	x2, y2, z2,  0.0f,  0.0f,  1.0f,
	/*4*/	x2, y2, z2,  0.0f,  0.0f,  1.0f,
	/*3*/	x1, y2, z2,  0.0f,  0.0f,  1.0f,
	/*7*/	x1, y1, z2,  0.0f,  0.0f,  1.0f,
		
			// 2156 Back side
	/*5*/	x1, y1, z1,  0.0f,  0.0f, -1.0f,
	/*6*/	x2, y1, z1,  0.0f,  0.0f, -1.0f,
	/*2*/	x2, y2, z1,  0.0f,  0.0f, -1.0f,
	/*2*/	x2, y2, z1,  0.0f,  0.0f, -1.0f,
	/*1*/	x1, y2, z1,  0.0f,  0.0f, -1.0f,
	/*5*/	x1, y1, z1,  0.0f,  0.0f, -1.0f	  
		};

		break;

	case SIMPLE:
		/*
				1---------------2
			   /|		       /|
			  / |		      / |
			 /  |			 /  |
			3---------------4   |
			|   |			|   |
			|   |			|   |
			|   5-----------|---6
			|  /			|  /
			| /				| /
			|/				|/
			7---------------8
		*/

		cubeVertices = {
			// 1243 Top side
	/*1*/	x1, y2, z1,
	/*2*/	x2, y2, z1,
	/*4*/	x2, y2, z2,
	/*4*/	x2, y2, z2,
	/*3*/	x1, y2, z2,
	/*1*/	x1, y2, z1,

			// 6578 Bottom side
	/*5*/	x1, y1, z1,
	/*6*/	x2, y1, z1,
	/*8*/	x2, y1, z2,
	/*8*/	x2, y1, z2,
	/*7*/	x1, y1, z2,
	/*5*/	x1, y1, z1,

			// 4268 Right side
	/*4*/	x2, y2, z2,
	/*2*/	x2, y2, z1,
	/*6*/	x2, y1, z1,
	/*6*/	x2, y1, z1,
	/*8*/	x2, y1, z2,
	/*4*/	x2, y2, z2,

			// 1375 Left side
	/*3*/	x1, y2, z2,
	/*1*/	x1, y2, z1,
	/*5*/	x1, y1, z1,
	/*5*/	x1, y1, z1,
	/*7*/	x1, y1, z2,
	/*3*/	x1, y2, z2,

			// 3487 Front side
	/*7*/	x1, y1, z2,
	/*8*/	x2, y1, z2,
	/*4*/	x2, y2, z2,
	/*4*/	x2, y2, z2,
	/*3*/	x1, y2, z2,
	/*7*/	x1, y1, z2,

			// 2156 Back side
	/*5*/	x1, y1, z1,
	/*6*/	x2, y1, z1,
	/*2*/	x2, y2, z1,
	/*2*/	x2, y2, z1,
	/*1*/	x1, y2, z1,
	/*5*/	x1, y1, z1
		};

		break;
	}

	createVAO(cubeVertices, cubeVertices.size(), vaoConfig, METRIC_3D);
	m_vaoConfig = vaoConfig;
	m_modelType = ModelType::V36;

	return true;
}

void Model::createVAO(
	const std::vector<GLfloat>& vector,
	int vectorSize,
	VAOconfig vaoConfig,
	int metric)
{
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vectorSize, vector.data(), GL_STATIC_DRAW);

	GLvoid* offset;

	switch (vaoConfig)
	{
	case VAOconfig::TEXTURES:
		offset = (GLvoid*)(sizeof(GLfloat) * (5 + metric));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (vaoConfig + metric) * sizeof(GLfloat), offset);
		glEnableVertexAttribArray(2);

	case VAOconfig::NORMALS:
		offset = (GLvoid*)(sizeof(GLfloat) * (2 + metric));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (vaoConfig + metric) * sizeof(GLfloat), offset);
		glEnableVertexAttribArray(1);

	case VAOconfig::SIMPLE:
		glVertexAttribPointer(0, 2 + metric, GL_FLOAT, GL_FALSE, (vaoConfig + metric) * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
}
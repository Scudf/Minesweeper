#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

#include "Model.h"
#include "Shader.h"

using GraphicObjPtr = std::shared_ptr<class GraphicObj>;

class GraphicObj
{
public:
	static GraphicObjPtr Create(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) { return std::make_shared<GraphicObj>(model, shader, position, rotation, scale); }

	GraphicObj(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

	void render();

	inline const glm::vec3& getPosition() const { return m_position; }
	inline const glm::vec3& getRotation() const { return m_rotation; }
	inline const glm::vec3& getScale() const { return m_scale; }

	inline const glm::vec3& getColor() const { return m_color; }

	inline const glm::vec3& getAmbientColor() const { return m_ambientColor; }
	inline const glm::vec3& getDiffuseColor() const { return m_diffuseColor; }
	inline const glm::vec3& getSpecularColor() const { return m_specularColor; }

	inline int getDiffuseTexture() const { return m_diffuseTexInd; }
	inline int getSpecularTexture() const { return m_specularTexInd; }

	inline float getShininess() const { return m_shininess; }
	inline float getSaturation() const { return m_saturation; }
	inline float getBrightness() const { return m_brightness; }

	inline float getMixCoeff() const { return m_mixCoeff; }

	inline void setPosition(const glm::vec3& position)
	{
		m_position = position;

		m_matModelIsDirty = true;
	}

	inline void setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;

		m_matModelIsDirty = true;
	}

	inline void setOffset(const glm::vec3& position)
	{
		m_position += position;

		m_matModelIsDirty = true;
	}

	inline void setOffset(float x, float y, float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;

		m_matModelIsDirty = true;
	}

	inline void setRotation(const glm::vec3& rotation)
	{
		m_rotation = rotation;

		m_matModelIsDirty = true;
	}

	inline void setRotation(float x, float y, float z)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;

		m_matModelIsDirty = true;
	}

	inline void setScale(const glm::vec3& scale)
	{
		m_scale = scale;

		m_matModelIsDirty = true;
	}

	inline void setScale(float x, float y, float z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;

		m_matModelIsDirty = true;
	}

	inline void setColor(const glm::vec3& color) { m_color = color; }
	inline void setColor(float x, float y, float z)
	{
		m_color.x = x;
		m_color.y = y;
		m_color.z = z;
	}

	inline void setAmbientColor(const glm::vec3& ambientColor) { m_ambientColor = ambientColor; }
	inline void setAmbientColor(float x, float y, float z)
	{
		m_ambientColor.x = x;
		m_ambientColor.y = y;
		m_ambientColor.z = z;
	}

	inline void setDiffuseColor(const glm::vec3& diffuseColor) { m_diffuseColor = diffuseColor; }
	inline void setDiffuseColor(float x, float y, float z)
	{
		m_diffuseColor.x = x;
		m_diffuseColor.y = y;
		m_diffuseColor.z = z;
	}

	inline void setSpecularColor(const glm::vec3& specularColor) { m_specularColor = specularColor; }
	inline void setSpecularColor(float x, float y, float z)
	{
		m_specularColor.x = x;
		m_specularColor.y = y;
		m_specularColor.z = z;
	}

	inline void setDiffuseTexture(int diffuseTexInd) { m_diffuseTexInd = diffuseTexInd; }
	inline void setSpecularTexture(int specularTexInd) { m_specularTexInd = specularTexInd; }

	inline void setShininess(float shininess) { m_shininess = shininess; }
	inline void setSaturation(float saturation) { m_saturation = saturation; }
	inline void setBrightness(float brightness) { m_brightness = brightness; }

	inline void setMixCoeff(float mixCoeff) { m_mixCoeff = mixCoeff; }

	void setMaterialColor(
		const glm::vec3& ambientColor,
		const glm::vec3& diffuseColor,
		const glm::vec3& specularColor,
		float shininess = 32.0f,
		float saturation = 1.0f,
		float brightness = 1.0f);

	void setMaterialTexture(
		int diffuseTexInd,
		int specularTexInd,
		float shininess = 32.0f,
		float saturation = 1.0f,
		float brightness = 1.0f);
	
private:
	ModelPtr m_model;
	ShaderPtr m_shader;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::vec3 m_color;

	glm::vec3 m_ambientColor;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;

	int m_diffuseTexInd;
	int m_specularTexInd;

	float m_shininess;
	float m_saturation;
	float m_brightness;

	float m_mixCoeff;

	glm::mat4 m_matModel;
	bool m_matModelIsDirty;
};


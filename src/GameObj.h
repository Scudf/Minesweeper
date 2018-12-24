#pragma once

#include <memory>

#include "Model.h"
#include "Shader.h"
#include "GraphicObj.h"


using GameObjPtr = std::shared_ptr<class GameObj>;

class GameObj
{
public:
	static GameObjPtr Create(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3& position) { return std::make_shared<GameObj>(model, shader, position); }

	GameObj(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3& position);

	virtual ~GameObj();

	virtual void update(float dt);

	virtual void press(float animationDelay = 0.0f)
	{
		m_isPressed = true;
		m_isPressAnimated = false;
		m_animationDelay = animationDelay;
	}

	virtual void unpress(float animationDelay = 0.0f)
	{
		m_isPressed = false;
		m_isPressAnimated = false;
		m_animationDelay = animationDelay;
	}

	const GraphicObjPtr& getGraphicObj() const { return m_graphicObj; }

	inline float getPressingSpeed() const { return m_pressingSpeed; }
	inline float getMinScale() const { return m_minScale; }
	inline float getMaxScale() const { return m_maxScale; }

	inline bool isPressed() const { return m_isPressed; }
	inline bool isPressAnimated() const { return m_isPressAnimated; }

	inline void setPressingSpeed(float pressingSpeed) { m_pressingSpeed = pressingSpeed; }
	inline void setMinScale(float minScale) { m_minScale = minScale; }
	inline void setMaxScale(float maxScale) { m_maxScale = maxScale; }

protected:
	virtual void changeTexture();
	virtual void pressing(float dt);

protected:
	GraphicObjPtr m_graphicObj;

	float m_animationDelay;
	float m_pressingSpeed;
	float m_minScale;
	float m_maxScale;

	bool m_isPressed;
	bool m_isPressAnimated;

private:
};


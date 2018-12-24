#pragma once

#include "GameObj.h"


using ButtonPtr = std::shared_ptr<class Button>;

enum class ButtonType
{
	START,
	BEGINNER,
	INTERMEDIATE,
	EXPERT,
	EXIT
};

class Button :
	public GameObj
{
public:
	static ButtonPtr Create(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3 &position,
		ButtonType buttonType) { return std::make_shared<Button>(model, shader, position, buttonType); }

	Button(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3 &position,
		ButtonType buttonType);

	void update(float dt) override;

	inline void press(float animationDelay = 0.0f) override
	{
		GameObj::press(animationDelay);
		m_graphicObj->setBrightness(2.0f);
	}

	inline void unpress(float animationDelay = 0.0f) override
	{
		GameObj::unpress(animationDelay);
		m_graphicObj->setBrightness(1.0f);
	}

	ButtonType getButtonType() const { return m_buttonType; }

private:
	ButtonType m_buttonType;
};


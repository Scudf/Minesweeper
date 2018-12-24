#include "stdafx.h"
#include "Button.h"


Button::Button(
const ModelPtr& model,
const ShaderPtr& shader,
const glm::vec3 &position,
ButtonType buttonType)
	: GameObj(
		model,
		shader,
		position)
	, m_buttonType(buttonType)
{

}

void Button::update(float dt)
{
	GameObj::update(dt);
}



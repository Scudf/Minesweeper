#include "stdafx.h"
#include "GameObj.h"
#include "Game.h"
#include "GameScene.h"


GameObj::GameObj(
	const ModelPtr& model,
	const ShaderPtr& shader,
	const glm::vec3 &position)
	: m_animationDelay(0.0f)
	, m_pressingSpeed(1.5f)
	, m_minScale(0.1f)
	, m_maxScale(1.0f)
	, m_isPressed(false)
	, m_isPressAnimated(false)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	m_graphicObj = GraphicObj::Create(model, shader, position);
	m_graphicObj->setMaterialTexture(gs->getGLTexture("cells/cell_c.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_graphicObj);
}

GameObj::~GameObj()
{
	Game::GetInstancePtr()->getGraphicScene()->removeObject(m_graphicObj);
}

void GameObj::update(float dt)
{
	pressing(dt);
}

void GameObj::pressing(float dt)
{
	if (m_animationDelay > 0)
		m_animationDelay -= dt;
	else
	{
		m_animationDelay = 0;

		if (!m_isPressAnimated)
		{
			float targetScale;

			if (m_isPressed)
				targetScale = m_minScale;
			else
				targetScale = m_maxScale;

			float scale = m_graphicObj->getScale().z;
			float totalScaleOffset = targetScale - scale;

			float deltaScale = dt * m_pressingSpeed;

			if (deltaScale >= abs(totalScaleOffset))
			{
				scale = targetScale;
				m_isPressAnimated = true;
			}
			else if (totalScaleOffset > 0)
				scale += deltaScale;
			else
				scale -= deltaScale;

			m_graphicObj->setScale(1.0f, 1.0f, scale);
		}
	}
}

void GameObj::changeTexture()
{

}
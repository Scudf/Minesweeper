#include "stdafx.h"
#include "Cell.h"
#include "Game.h"
#include "GraphicScene.h"


Cell::Cell(
	const ModelPtr& model,
	const ShaderPtr& shader,
	const glm::vec3 &position,
	CellType cellType)
	: GameObj(
		model,
		shader,
		position)
	, m_cellType(cellType)
	, m_flag(false)
	, m_isTexDirty(false)
{
	changeTexture();
}

void Cell::update(float dt)
{
	GameObj::update(dt);

	if (m_animationDelay == 0)
	{
		float mixCoeff = 0.0f;

		changeTexture();

		if (!m_flag)
			mixCoeff = m_graphicObj->getScale().z;
		else
			mixCoeff = 0.0f;
		
		m_graphicObj->setMixCoeff(mixCoeff);
	}
}

void Cell::changeTexture()
{
	if (m_isTexDirty)
	{
		GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

		if (!m_isPressed)
		{
			if (m_flag)
				m_graphicObj->setDiffuseTexture(gs->getGLTexture("Flag.png"));
			else
				m_graphicObj->setDiffuseTexture(gs->getGLTexture("Unpressed.png"));
		}
		else
		{
			switch (m_cellType)
			{
			case CellType::ONE:		m_graphicObj->setDiffuseTexture(gs->getGLTexture("One.png"));		break;
			case CellType::TWO:		m_graphicObj->setDiffuseTexture(gs->getGLTexture("Two.png"));		break;
			case CellType::THREE:	m_graphicObj->setDiffuseTexture(gs->getGLTexture("Three.png"));		break;
			case CellType::FOR:		m_graphicObj->setDiffuseTexture(gs->getGLTexture("Four.png"));		break;
			case CellType::FIVE:	m_graphicObj->setDiffuseTexture(gs->getGLTexture("Five.png"));		break;
			case CellType::SIX:		m_graphicObj->setDiffuseTexture(gs->getGLTexture("Six.png"));		break;
			case CellType::SEVEN:	m_graphicObj->setDiffuseTexture(gs->getGLTexture("Seven.png"));		break;
			case CellType::EIGHT:	m_graphicObj->setDiffuseTexture(gs->getGLTexture("Eight.png"));		break;
			case CellType::BOMB:	m_graphicObj->setDiffuseTexture(gs->getGLTexture("Bomb.png"));		break;
			default:				m_graphicObj->setDiffuseTexture(gs->getGLTexture("Pressed.png"));	break;
			}
		}

		m_isTexDirty = false;
	}
}

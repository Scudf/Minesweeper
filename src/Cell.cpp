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
				m_graphicObj->setDiffuseTexture(gs->getGLTexture("cells/cell_f.png"));
			else
				m_graphicObj->setDiffuseTexture(gs->getGLTexture("cells/cell_c.png"));
		}
		else
			std::string name = "cells/cell_" + std::to_string(m_cellType) + ".png";

		m_isTexDirty = false;
	}
}

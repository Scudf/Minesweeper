#pragma once

#include "GameObj.h"


using CellPtr = std::shared_ptr<class Cell>;

enum CellType
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	BOMB,
	MAX
};

class Cell :
	public GameObj
{
public:
	static CellPtr Create(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3 &position,
		CellType cellType = CellType::ZERO) { return std::make_shared<Cell>(model, shader, position, cellType); }

	Cell(
		const ModelPtr& model,
		const ShaderPtr& shader,
		const glm::vec3 &position,
		CellType cellType = CellType::ZERO);

	void update(float dt) override;
	
	inline void press(float animationDelay = 0.0f) override
	{
		GameObj::press(animationDelay);
		m_isTexDirty = true;
	}

	inline void unpress(float animationDelay = 0.0f) override
	{
		GameObj::unpress(animationDelay);
		m_isTexDirty = true;
	}

	inline CellType getCellType() const { return m_cellType; }

	inline bool getFlag() const { return m_flag; }

	inline void setCellType(CellType cellType) { m_cellType = cellType; }

	inline void incCellType()
	{
		if (m_cellType < CellType::MAX - 1)
		{
			m_cellType = (CellType)(m_cellType + 1);
			m_isTexDirty = true;
		}
	}

	inline void decCellType()
	{
		if (m_cellType > 0)
		{
			m_cellType = (CellType)(m_cellType - 1);
			m_isTexDirty = true;
		}
	}

	inline void setFlag(bool flag)
	{
		m_flag = flag;
		m_isTexDirty = true;
	}

	inline void switchFlag()
	{
		m_flag = !m_flag;
		m_isTexDirty = true;
	}

private:
	void changeTexture() override;

private:
	CellType m_cellType;

	bool m_flag;
	bool m_isTexDirty;
};


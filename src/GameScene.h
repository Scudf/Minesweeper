#pragma once

#include <GLFW/glfw3.h>

#include "GraphicObj.h"
#include "GameObj.h"
#include "Cell.h"
#include "Button.h"


enum class Difficult
{
	BEGINNER,
	INTERMEDIATE,
	EXPERT,
};

struct DifficultDef
{
	Difficult m_difficult;

	int m_rows;
	int m_columns;
	int m_maxBombs;

	DifficultDef()
		: m_difficult(Difficult::BEGINNER)
		, m_rows(9)
		, m_columns(9)
		, m_maxBombs(10)
		{}

	DifficultDef(Difficult difficult)
	{
		m_difficult = difficult;

		switch (difficult)
		{
		case Difficult::BEGINNER:
			m_rows = 9;
			m_columns = 9;
			m_maxBombs = 10;
			break;

		case Difficult::INTERMEDIATE:
			m_rows = 16;
			m_columns = 16;
			m_maxBombs = 40;
			break;

		case Difficult::EXPERT:
			m_rows = 16;
			m_columns = 30;
			m_maxBombs = 99;
			break;
		}
	}
};

class GameScene
{
public:
	GameScene();

	bool initialize();
	bool update(float dt);

	bool isCell(int r, int c);
	bool isEmpty(int r, int c);
	void flagCounter(int r, int c);

	void selectCameraTarget();
	void updateCameraPosition(float dt);

	void generateCells();
	void resetLevel();
	void generateLevel(int row, int column);
	bool processGameButtons(int r, int c);
	void clean(int r, int c, int startR, int startC);
	void cleanBlock(int r, int c);
	void markBombs();
	void showBombs();
	
	void solveTimeCounter();
	void solveMineCounter();

	void processKeyCallback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods);

	void processCursorPosCallback(
		GLFWwindow*	window,
		double xpos,
		double ypos);

	void processPressMouseButton(int button);

	void processMouseButtonCallback(
		GLFWwindow* window,
		int button,
		int action,
		int mode);

	void processScrollCallback(
		GLFWwindow* window,
		double xoffset,
		double yoffset);

	void addObject(const GameObjPtr& object);
	void removeObject(const GameObjPtr& object);
	void removeObject(GameObj* object);

	inline bool getKey(int key) const { return m_keys[key]; }

	inline bool isCameraFree() const {return m_isCameraFree; }

private:
	GraphicObjPtr m_plane;

	ButtonPtr m_startButton;
	ButtonPtr m_beginnerButton;
	ButtonPtr m_intermedButton;
	ButtonPtr m_expertButton;
	ButtonPtr m_exitButton;

	GraphicObjPtr m_firstTimerNumber;
	GraphicObjPtr m_secondTimerNumber;
	GraphicObjPtr m_thirdTimerNumber;

	GraphicObjPtr m_firstMinesNumber;
	GraphicObjPtr m_secondMinesNumber;
	GraphicObjPtr m_thirdMinesNumber;

	DifficultDef m_difficultDef;

	int m_bombsCount;
	int m_emptyCount;
	int m_flagsCount;

	bool m_keys[1024];
	bool m_buttons[16];
	
	bool m_firstMousePos;
	bool m_isCameraFree;
	bool m_firstLeftClick;

	bool m_pause;

	float m_stopwatch;
	int m_seconds;
	float m_animationDelay;

	float m_lastX;
	float m_lastY;

	float m_cameraSpeed;
	float m_mouseSensitivity;

	glm::vec3 m_worldMousePosition;

	glm::vec3 m_cameraAnchor;
	glm::vec3 m_cameraTarget;
	
	std::vector<GameObjPtr> m_objects;
	std::vector<GameObjPtr> m_garbageCollector;

	std::vector<std::vector<CellPtr>> m_cells;
};


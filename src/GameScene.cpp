#include "stdafx.h"
#include <GL/glew.h>

#include "Cell.h"
#include "Button.h"
#include "GameScene.h"
#include "Game.h"
#include "GraphicScene.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Game::GetInstancePtr()->getGameScene()->processKeyCallback(window, key, scancode, action, mode);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game::GetInstancePtr()->getGameScene()->processCursorPosCallback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Game::GetInstancePtr()->getGameScene()->processMouseButtonCallback(window, button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::GetInstancePtr()->getGameScene()->processScrollCallback(window, xoffset, yoffset);
}

GameScene::GameScene()
	: m_difficultDef(Difficult::BEGINNER)
	, m_bombsCount(0)
	, m_emptyCount(0)
	, m_flagsCount(0)
	, m_pause(true)
	, m_firstMousePos(true)
	, m_isCameraFree(false)
	, m_firstLeftClick(true)
	, m_stopwatch(0.0f)
	, m_seconds(0)
	, m_animationDelay(0.1f)
	, m_cameraSpeed(1000.0f)
	, m_mouseSensitivity(0.15f)
	, m_worldMousePosition(0)
	, m_cameraAnchor(0)
	, m_cameraTarget(0)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	m_lastX = (float)(gs->getWidth() / 2.0f);
	m_lastY = (float)(gs->getHeight() / 2.0f);
}

bool GameScene::initialize()
{
	GLFWwindow* window = Game::GetInstancePtr()->getGraphicScene()->getWindow();
	GraphicScene*	gs = Game::GetInstancePtr()->getGraphicScene();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	m_plane = GraphicObj::Create(gs->getModel("normPlane"), gs->getGLShader("normalsShader"));
	m_plane->setPosition(0.0f, 0.0f, -1.0f);
	m_plane->setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
	gs->addObject(m_plane);

	m_firstTimerNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_firstTimerNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_firstTimerNumber);

	m_secondTimerNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_secondTimerNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_secondTimerNumber);

	m_thirdTimerNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_thirdTimerNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_thirdTimerNumber);

	m_firstMinesNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_firstMinesNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_firstMinesNumber);

	m_secondMinesNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_secondMinesNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_secondMinesNumber);

	m_thirdMinesNumber = GraphicObj::Create(gs->getModel("texNumber"), gs->getGLShader("texturesShader"));
	m_thirdMinesNumber->setMaterialTexture(gs->getGLTexture("numbers/number_0.png"), gs->getGLTexture("cells/cell_c.png"));
	gs->addObject(m_thirdMinesNumber);

	m_startButton = Button::Create(
		gs->getModel("texCell"),
		gs->getGLShader("texturesShader"),
		glm::vec3(
		(m_difficultDef.m_columns - 1) / 2.0f * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			0.0f),
		ButtonType::START);
	m_startButton->getGraphicObj()->setDiffuseTexture(gs->getGLTexture("buttons/button_start.png"));
	m_startButton->setMinScale(0.5f);
	addObject(m_startButton);

	m_beginnerButton = Button::Create(
		gs->getModel("texCell"),
		gs->getGLShader("texturesShader"),
		glm::vec3(
			gs->getBlockSize() / 2.0f,
			m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			0.0f),
		ButtonType::BEGINNER);
	m_beginnerButton->getGraphicObj()->setDiffuseTexture(gs->getGLTexture("buttons/button_beginner.png"));
	m_beginnerButton->setMinScale(0.5f);
	addObject(m_beginnerButton);

	m_intermedButton = Button::Create(
		gs->getModel("texCell"),
		gs->getGLShader("texturesShader"),
		glm::vec3(
			gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			0.0f),
		ButtonType::INTERMEDIATE);
	m_intermedButton->getGraphicObj()->setDiffuseTexture(gs->getGLTexture("buttons/button_intermediate.png"));
	m_intermedButton->setMinScale(0.5f);
	addObject(m_intermedButton);

	m_expertButton = Button::Create(
		gs->getModel("texCell"),
		gs->getGLShader("texturesShader"),
		glm::vec3(
			gs->getBlockSize() * 2.0f + gs->getBlockSize() / 2.0f,
			m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			0.0f),
		ButtonType::EXPERT);
	m_expertButton->getGraphicObj()->setDiffuseTexture(gs->getGLTexture("buttons/button_expert.png"));
	m_expertButton->setMinScale(0.5f);
	addObject(m_expertButton);

	m_exitButton = Button::Create(
		gs->getModel("texCell"),
		gs->getGLShader("texturesShader"),
		glm::vec3(
		(m_difficultDef.m_columns - 1) * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
			0.0f),
		ButtonType::EXIT);
	m_exitButton->getGraphicObj()->setDiffuseTexture(gs->getGLTexture("buttons/button_exit.png"));
	m_exitButton->setMinScale(0.5f);
	addObject(m_exitButton);

	Difficult diff = m_difficultDef.m_difficult;

	switch (diff)
	{
	case Difficult::BEGINNER: m_beginnerButton->press(); break;
	case Difficult::INTERMEDIATE: m_intermedButton->press(); break;
	case Difficult::EXPERT: m_expertButton->press(); break;
	}

	generateCells();

	return true;
}

bool GameScene::update(float dt)
{
	if (!m_firstLeftClick && !m_pause)
		m_stopwatch += dt;

	if (m_stopwatch >= 1.0f)
	{
		++m_seconds;
		m_stopwatch -= 1.0f;
		solveTimeCounter();
	}

	if(m_exitButton->isPressAnimated() && m_exitButton->isPressed())
		glfwSetWindowShouldClose(Game::GetInstancePtr()->getGraphicScene()->getWindow(), GL_TRUE);

	m_garbageCollector.clear();

	GLFWwindow* window = Game::GetInstancePtr()->getGraphicScene()->getWindow();

	if (!m_isCameraFree)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		selectCameraTarget();
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		updateCameraPosition(dt);
	}

	for (GameObjPtr object : m_objects)
		object->update(dt);

	for (int r = 0; r < m_difficultDef.m_rows; ++r)
		for (int c = 0; c < m_difficultDef.m_columns; ++c)
			m_cells[r][c]->update(dt);

	return true;
}

bool GameScene::isCell(int r, int c)
{
	if (r >= 0 && r < m_difficultDef.m_rows && c >= 0 && c < m_difficultDef.m_columns)
		return true;
	else
		return false;
}

bool GameScene::isEmpty(int r, int c)
{
	if (isCell(r, c))
		if (m_cells[r][c]->getCellType() != CellType::BOMB)
			return true;

	return false;
}

void GameScene::flagCounter(int r, int c)
{
	if (isCell(r, c))
		if (m_cells[r][c]->getFlag())
			++m_flagsCount;
}

void GameScene::selectCameraTarget()
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	int rows = m_difficultDef.m_rows + 1;
	int columns = m_difficultDef.m_columns;

	float h = (float)gs->getHeight();
	float w = (float)gs->getWidth();

	float a = (rows >= columns
		? (rows / h)
		: (columns / w));

	a *= ((h + w) / 2.0f + 100.0f);

	float x = columns * gs->getBlockSize() / 2.0f;
	float y = rows * gs->getBlockSize() / 2.0f;

	m_cameraAnchor = glm::vec3(x, y, a * gs->getBlockSize());
	m_cameraTarget = glm::vec3(x, y, 0.0f);

	gs->getCamera()->updateTarget(m_cameraAnchor, m_cameraTarget);
}

void GameScene::updateCameraPosition(float dt)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();
	CameraPtr camera = gs->getCamera();

	float velocity = m_cameraSpeed * dt;

	if (m_keys[GLFW_KEY_W])
		camera->setPosition(camera->getPosition() + camera->getFront() * velocity);
	if (m_keys[GLFW_KEY_S])
		camera->setPosition(camera->getPosition() - camera->getFront() * velocity);
	if (m_keys[GLFW_KEY_A])
		camera->setPosition(camera->getPosition() - camera->getRight() * velocity);
	if (m_keys[GLFW_KEY_D])
		camera->setPosition(camera->getPosition() + camera->getRight() * velocity);
}

void GameScene::generateCells()
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	m_plane->setScale(glm::vec3(m_difficultDef.m_columns, m_difficultDef.m_rows + 1, 1.0f));

	m_firstTimerNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 2) * gs->getBlockSize() + gs->getBlockSize() / 2.0f + 30.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_secondTimerNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 2) * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_thirdTimerNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 2) * gs->getBlockSize() + gs->getBlockSize() / 2.0f - 30.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_firstMinesNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 3) * gs->getBlockSize() + gs->getBlockSize() / 2.0f + 30.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_secondMinesNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 3) * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_thirdMinesNumber->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 3) * gs->getBlockSize() + gs->getBlockSize() / 2.0f - 30.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_startButton->getGraphicObj()->setPosition(glm::vec3(
		(int)((m_difficultDef.m_columns - 1) / 2.0f) * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_beginnerButton->getGraphicObj()->setPosition(glm::vec3(
		gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_intermedButton->getGraphicObj()->setPosition(glm::vec3(
		gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_expertButton->getGraphicObj()->setPosition(glm::vec3(
		gs->getBlockSize() * 2.0f + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_exitButton->getGraphicObj()->setPosition(glm::vec3(
		(m_difficultDef.m_columns - 1) * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		m_difficultDef.m_rows * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
		0.0f));

	m_cells.clear();

	m_cells.resize(m_difficultDef.m_rows);

	for (int r = 0; r < m_difficultDef.m_rows; ++r)
	{
		m_cells[r].resize(m_difficultDef.m_columns);

		for (int c = 0; c < m_difficultDef.m_columns; ++c)
		{
			CellPtr cell = Cell::Create(
				gs->getModel("texCell"),
				gs->getGLShader("mixShader"),
				glm::vec3(
					c * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
					r * gs->getBlockSize() + gs->getBlockSize() / 2.0f,
					0.0f));

			m_cells[r][c] = cell;
			m_garbageCollector.push_back(cell);
		}
	}

	resetLevel();
}

void GameScene::resetLevel()
{
	m_stopwatch = 0.0f;
	m_seconds = 0;
	m_bombsCount = 0;
	m_emptyCount = 0;
	
	for (int r = 0; r < m_difficultDef.m_rows; ++r)
		for (int c = 0; c < m_difficultDef.m_columns; ++c)
		{
			m_cells[r][c]->unpress(m_animationDelay);
			m_cells[r][c]->setCellType(CellType::ZERO);

			if (!m_firstLeftClick)
				m_cells[r][c]->setFlag(false);
		}

	m_firstLeftClick = true;
	m_pause = true;

	solveTimeCounter();
	solveMineCounter();
}

void GameScene::generateLevel(int row, int column)
{
	resetLevel();

	while (m_bombsCount < m_difficultDef.m_maxBombs)
	{
		int r = rand() % m_difficultDef.m_rows;
		int c = rand() % m_difficultDef.m_columns;

		if (m_cells[r][c]->getCellType() != CellType::BOMB && (r != row || c != column))
		{
			m_cells[r][c]->setCellType(CellType::BOMB);
			++m_bombsCount;

			if (isEmpty(r - 1, c - 1))
				m_cells[r - 1][c - 1]->incCellType();

			if (isEmpty(r - 1, c))
				m_cells[r - 1][c]->incCellType();

			if (isEmpty(r - 1, c + 1))
				m_cells[r - 1][c + 1]->incCellType();

			if (isEmpty(r, c - 1))
				m_cells[r][c - 1]->incCellType();

			if (isEmpty(r, c + 1))
				m_cells[r][c + 1]->incCellType();

			if (isEmpty(r + 1, c - 1))
				m_cells[r + 1][c - 1]->incCellType();

			if (isEmpty(r + 1, c))
				m_cells[r + 1][c]->incCellType();

			if (isEmpty(r + 1, c + 1))
				m_cells[r + 1][c + 1]->incCellType();
		}
	}

	solveMineCounter();
}

void GameScene::solveTimeCounter()
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	int seconds = m_seconds;
	int d = 0;

	for (int i = 0; i < 3; ++i)
	{
		d = seconds % 10;

		GraphicObjPtr object;

		switch (i)
		{
			case 0: object = m_firstTimerNumber; break;
			case 1: object = m_secondTimerNumber; break;
			case 2: object = m_thirdTimerNumber; break;
		}

		switch (d)
		{
			case 0: object->setDiffuseTexture(gs->getGLTexture("numbers/number_0.png")); break;
			case 1: object->setDiffuseTexture(gs->getGLTexture("numbers/number_1.png")); break;
			case 2: object->setDiffuseTexture(gs->getGLTexture("numbers/number_2.png")); break;
			case 3: object->setDiffuseTexture(gs->getGLTexture("numbers/number_3.png")); break;
			case 4: object->setDiffuseTexture(gs->getGLTexture("numbers/number_4.png")); break;
			case 5: object->setDiffuseTexture(gs->getGLTexture("numbers/number_5.png")); break;
			case 6: object->setDiffuseTexture(gs->getGLTexture("numbers/number_6.png")); break;
			case 7: object->setDiffuseTexture(gs->getGLTexture("numbers/number_7.png")); break;
			case 8: object->setDiffuseTexture(gs->getGLTexture("numbers/number_8.png")); break;
			case 9: object->setDiffuseTexture(gs->getGLTexture("numbers/number_9.png")); break;
		}

		seconds /= 10;
	}
}

void GameScene::solveMineCounter()
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	int bombs = m_bombsCount;
	int d = 0;

	for (int i = 0; i < 3; ++i)
	{
		d = bombs % 10;

		GraphicObjPtr object;

		switch (i)
		{
			case 0: object = m_firstMinesNumber; break;
			case 1: object = m_secondMinesNumber; break;
			case 2: object = m_thirdMinesNumber; break;
		}

		switch (d)
		{
			case 0: object->setDiffuseTexture(gs->getGLTexture("numbers/number_0.png")); break;
			case 1: object->setDiffuseTexture(gs->getGLTexture("numbers/number_1.png")); break;
			case 2: object->setDiffuseTexture(gs->getGLTexture("numbers/number_2.png")); break;
			case 3: object->setDiffuseTexture(gs->getGLTexture("numbers/number_3.png")); break;
			case 4: object->setDiffuseTexture(gs->getGLTexture("numbers/number_4.png")); break;
			case 5: object->setDiffuseTexture(gs->getGLTexture("numbers/number_5.png")); break;
			case 6: object->setDiffuseTexture(gs->getGLTexture("numbers/number_6.png")); break;
			case 7: object->setDiffuseTexture(gs->getGLTexture("numbers/number_7.png")); break;
			case 8: object->setDiffuseTexture(gs->getGLTexture("numbers/number_8.png")); break;
			case 9: object->setDiffuseTexture(gs->getGLTexture("numbers/number_9.png")); break;
		}

		bombs /= 10;
	}
}

bool GameScene::processGameButtons(int r, int c)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	for (GameObjPtr object : m_objects)
	{
		int column = (int)(object->getGraphicObj()->getPosition().x / gs->getBlockSize());
		int row = (int)(object->getGraphicObj()->getPosition().y / gs->getBlockSize());

		if (r == row && c == column)
			if (!object->isPressed())
			{
				ButtonType buttonType = std::static_pointer_cast<Button>(object)->getButtonType();

				object->press();

				switch (buttonType)
				{
				case ButtonType::START:
					resetLevel();
					object->getGraphicObj()->setDiffuseTexture(Game::GetInstancePtr()->getGraphicScene()->getGLTexture("buttons/button_win.png"));
					break;

				case ButtonType::BEGINNER:
					m_difficultDef = DifficultDef(Difficult::BEGINNER);
					generateCells();
					m_plane->setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
					m_intermedButton->unpress();
					m_expertButton->unpress();
					break;

				case ButtonType::INTERMEDIATE:
					m_difficultDef = DifficultDef(Difficult::INTERMEDIATE);
					generateCells();
					m_plane->setDiffuseColor(glm::vec3(1.0f, 1.0f, 0.0f));
					m_beginnerButton->unpress();
					m_expertButton->unpress();
					break;

				case ButtonType::EXPERT:
					m_difficultDef = DifficultDef(Difficult::EXPERT);
					generateCells();
					m_plane->setDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
					m_beginnerButton->unpress();
					m_intermedButton->unpress();
					break;
				}

				return true;
			}
	}

	return false;
}

void GameScene::clean(int r, int c, int startR, int startC)
{
	if (isCell(r, c))
	{
		if (!m_cells[r][c]->isPressed() && !m_cells[r][c]->getFlag())
		{
			int distToStart = abs(r - startR) + abs(c - startC);
			m_cells[r][c]->press(m_animationDelay * distToStart);
			++m_emptyCount;

			if (m_emptyCount + m_difficultDef.m_maxBombs == m_difficultDef.m_rows * m_difficultDef.m_columns)
			{
				markBombs();
				m_pause = true;
			}

			if (m_cells[r][c]->getCellType() == CellType::ZERO)
			{
				clean(r - 1, c - 1, startR, startC);
				clean(r - 1, c, startR, startC);
				clean(r - 1, c + 1, startR, startC);
				clean(r, c - 1, startR, startC);
				clean(r, c + 1, startR, startC);
				clean(r + 1, c - 1, startR, startC);
				clean(r + 1, c, startR, startC);
				clean(r + 1, c + 1, startR, startC);
			}
			else if (m_cells[r][c]->getCellType() == CellType::BOMB)
			{
				showBombs();
				m_pause = true;
			}
		}
	}
}

void GameScene::cleanBlock(int r, int c)
{
	m_flagsCount = 0;

	if (isEmpty(r, c))
	{
		if (m_cells[r][c]->isPressed())
		{
			flagCounter(r - 1, c - 1);
			flagCounter(r - 1, c);
			flagCounter(r - 1, c + 1);
			flagCounter(r, c - 1);
			flagCounter(r, c + 1);
			flagCounter(r + 1, c - 1);
			flagCounter(r + 1, c);
			flagCounter(r + 1, c + 1);
		}

		if (m_flagsCount == m_cells[r][c]->getCellType())
		{
			clean(r - 1, c - 1, r, c);
			clean(r - 1, c, r, c);
			clean(r - 1, c + 1, r, c);
			clean(r, c - 1, r, c);
			clean(r, c + 1, r, c);
			clean(r + 1, c - 1, r, c);
			clean(r + 1, c, r, c);
			clean(r + 1, c + 1, r, c);
		}
	}
}

void GameScene::markBombs()
{
	Game::GetInstancePtr()->getSoundManager()->playSound3D("res/sounds/win.mp3");

	m_startButton->getGraphicObj()->setDiffuseTexture(Game::GetInstancePtr()->getGraphicScene()->getGLTexture("buttons/button_win.png"));

	for (int r = 0; r < m_difficultDef.m_rows; ++r)
		for (int c = 0; c < m_difficultDef.m_columns; ++c)
			if (m_cells[r][c]->getCellType() == CellType::BOMB)
			{
				m_cells[r][c]->setFlag(true);
				m_bombsCount = 0;
			}
				
}

void GameScene::showBombs()
{
	Game::GetInstancePtr()->getSoundManager()->playSound3D("res/sounds/explosion.mp3");

	m_startButton->getGraphicObj()->setDiffuseTexture(Game::GetInstancePtr()->getGraphicScene()->getGLTexture("buttons/button_start.png"));

	for (int r = 0; r < m_difficultDef.m_rows; ++r)
		for (int c = 0; c < m_difficultDef.m_columns; ++c)
			if (m_cells[r][c]->getCellType() == CellType::BOMB && !m_cells[r][c]->getFlag())
				m_cells[r][c]->press();
}

void GameScene::processKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			m_keys[key] = true;

			if(key == GLFW_KEY_C)
				m_isCameraFree = !m_isCameraFree;
		}
		else if (action == GLFW_RELEASE)
			m_keys[key] = false;
	}
}

void GameScene::processCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	CameraPtr camera = Game::GetInstancePtr()->getGraphicScene()->getCamera();

	if (m_isCameraFree)
	{
		if (m_firstMousePos)
		{
			m_lastX = (float)xpos;
			m_lastY = (float)ypos;
			m_firstMousePos = false;
		}

		float xoffset = (float)xpos - m_lastX;
		float yoffset = m_lastY - (float)ypos;

		m_lastX = (float)xpos;
		m_lastY = (float)ypos;

		xoffset *= m_mouseSensitivity;
		yoffset *= m_mouseSensitivity;

		camera->setYaw(camera->getYaw() + xoffset);
		camera->setPitch(camera->getPitch() + yoffset);

		if (camera->getPitch() > 89.0f)
			camera->setPitch(89.0f);
		if (camera->getPitch() < -89.0f)
			camera->setPitch(-89.0f);

		camera->updateCameraVectors();
	}
	else
	{
		GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

		m_firstMousePos = true;

		glm::vec4 tmp(2.0f * (float)xpos / (float)gs->getWidth() - 1.0f, -2.0f * (float)ypos / (float)gs->getHeight() + 1.0f, -1.0f, 1.0f);
		glm::vec4 iTmp(glm::vec2(glm::inverse(gs->getMatPersp()) * tmp), -1.0f, 0.0f);
		glm::vec3 dir(glm::normalize(glm::inverse(gs->getMatView()) * iTmp));

		glm::vec3 N(0.0f, 0.0f, -1.0f);
		float t = -glm::dot(camera->getPosition(), N) / glm::dot(dir, N);
		m_worldMousePosition = glm::vec3(camera->getPosition() + dir * t);
	}
}

void GameScene::processPressMouseButton(int button)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	int r = (int)(m_worldMousePosition.y / gs->getBlockSize());
	int c = (int)(m_worldMousePosition.x / gs->getBlockSize());

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		m_buttons[button] = true;

		if (isCell(r, c) && m_firstLeftClick)
			if (!m_cells[r][c]->getFlag())
			{
				generateLevel(r, c);
				m_firstLeftClick = false;
				m_pause = false;

				m_startButton->unpress();
			}

		if (!processGameButtons(r, c) && !m_pause)
		{
			clean(r, c, r, c);
			cleanBlock(r, c);
		}

	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_buttons[button] = false;

		if (isCell(r, c))
			if (m_cells[r][c]->isPressAnimated() && !m_cells[r][c]->isPressed() && !m_firstLeftClick && !m_pause)
			{
				m_cells[r][c]->switchFlag();

				if (m_cells[r][c]->getFlag())
					--m_bombsCount;
				else
					++m_bombsCount;

				solveMineCounter();
			}	
	}
}

void GameScene::processMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 16)
	{
		if (action == GLFW_PRESS)
		{
			m_buttons[button] = true;

			if(!m_isCameraFree)
				processPressMouseButton(button);
		}
		else if (action == GLFW_RELEASE)
		{
			m_buttons[button] = false;
		}
	}
}

void GameScene::processScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	CameraPtr camera = Game::GetInstancePtr()->getGraphicScene()->getCamera();

	if (camera->getZoom() >= 1.0f && camera->getZoom() <= 45.0f)
		camera->setZoom(camera->getZoom() - (float)yoffset);
	if (camera->getZoom() <= 1.0f)
		camera->setZoom(1.0f);
	if (camera->getZoom() >= 45.0f)
		camera->setZoom(45.0f);
}

void GameScene::addObject(const GameObjPtr& object)
{
	m_objects.push_back(object);
}

void GameScene::removeObject(const GameObjPtr& object)
{
	removeObject(object.get());
}

void GameScene::removeObject(GameObj* object)
{

	for (std::vector<GameObjPtr>::iterator	it = m_objects.begin(),
		end = m_objects.end();
		it != end;
		++it)
	{
		if ((*it).get() == object)
		{
			m_garbageCollector.push_back(*it);
			m_objects.erase(it);
			return;
		}
	}
}
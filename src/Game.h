#pragma once

#include "GameScene.h"
#include "GraphicScene.h"
#include "SoundManager.h"


class Game
{
public:
	Game();
	~Game();

	bool initialize();
	bool update();

	GameScene* getGameScene() const { return m_gameScene; }
	GraphicScene* getGraphicScene() const { return m_graphicScene; }
	SoundManager* getSoundManager() const { return m_soundManager; }

	static Game* GetInstancePtr() { return s_instance; }

private:
	GameScene* m_gameScene;
	GraphicScene* m_graphicScene;
	SoundManager* m_soundManager;

	static Game* s_instance;

	float m_lastFrameTime;
	float m_timer;
	int m_framesCount;
};

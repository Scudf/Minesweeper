#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>


class SoundManager
{
public:
	SoundManager();

	bool initialize();
	bool update(float dt);

	void playSound3D(std::string sSound);

private:
	int m_musicSample;
	int m_musicChannel;

	int m_soundSample;
	int m_soundChannel;
};


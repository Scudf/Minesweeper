#include "stdafx.h"
#include "SoundManager.h"

#include "squall.h"
#include "Game.h"


SoundManager::SoundManager()
{

}

bool SoundManager::initialize()
{
	if (SQUALL_Init(0) < 0)
	{
		SQUALL_Free();
		return false;
	}

	float tfPos[3] = { 0.0f, 0.0f, 0.0f };
	SQUALL_Listener_SetPosition(tfPos);

	m_musicSample = SQUALL_Sample_LoadFile((char*)"res/sounds/main.mp3", 1, 0);
	m_musicChannel = SQUALL_Sample_Play(m_musicSample, 1, 0, 0);
	SQUALL_Channel_Start(m_musicChannel);
	SQUALL_Channel_SetVolume(m_musicChannel, 80);
	SQUALL_Channel_SetVolume(m_soundChannel, 100);

	return true;
}

bool SoundManager::update(float dt)
{
	return true;
}

void SoundManager::playSound3D(std::string sSound)
{
	float tfPos[3] = { 0.0f, 0.0f, 0.0f };
	m_soundSample = SQUALL_Sample_LoadFile((char*)sSound.c_str(), 1, 0);
	m_soundChannel = SQUALL_Sample_Play3D(m_soundSample, 0, 0, 0, tfPos, 0);
	SQUALL_Channel_Start(m_soundChannel);
}

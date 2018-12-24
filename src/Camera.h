#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>


using CameraPtr = std::shared_ptr<class Camera>;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f,
		float zoom = 45.0f);

	Camera(
		float posX,
		float posY,
		float posZ,
		float upX,
		float upY,
		float upZ,
		float yaw,
		float pitch,
		float zoom = 45.0f);

	static CameraPtr Create(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f,
		float zoom = 45.0f) { return std::make_shared<Camera>(position, up, yaw, pitch, zoom); }

	static CameraPtr Create(
		float posX,
		float posY,
		float posZ,
		float upX,
		float upY,
		float upZ,
		float yaw,
		float pitch,
		float zoom = 45.0f) { return std::make_shared<Camera>(posX, posY, posZ, upX, upY, upZ, yaw, pitch, zoom); }

	void updateCameraVectors();
	void updateTarget(const glm::vec3 &position, const glm::vec3 &target);

	inline glm::mat4 getFreeViewMatrix() const { return glm::lookAt(m_position, m_position + m_front, m_up); }
	inline glm::mat4 getTargetViewMatrix() const { return glm::lookAt(m_position, m_target, m_up); }

	inline const glm::vec3& getPosition() const { return m_position; }
	inline const glm::vec3& getFront() const { return m_front; }
	inline const glm::vec3& getUp() const { return m_up; }
	inline const glm::vec3& getRight() const { return m_right; }
	inline const glm::vec3& getWorldUp() const { return m_worldUp; }
	
	inline float getYaw() const { return m_yaw; }
	inline float getPitch() const { return m_pitch; }
	inline float getZoom() const { return m_zoom; }

	inline void setPosition(const glm::vec3& position) { m_position = position; }
	inline void setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	inline void setOffset(const glm::vec3& position) { m_position += position; }
	inline void setOffset(float x, float y, float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	inline void setFront(const glm::vec3& front) { m_front = front; }
	inline void setFront(float x, float y, float z)
	{
		m_front.x = x;
		m_front.y = y;
		m_front.z = z;
	}

	inline void setWorldUp(const glm::vec3& worldUp) { m_worldUp = worldUp; }
	inline void setWorldUp(float x, float y, float z)
	{
		m_worldUp.x = x;
		m_worldUp.y = y;
		m_worldUp.z = z;
	}

	inline void setYaw(float yaw) { m_yaw = yaw; }
	inline void setPitch(float pitch) { m_pitch = pitch; }
	inline void setZoom(float zoom)	{ m_zoom = zoom; }

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;
	glm::vec3 m_target;

	float m_yaw;
	float m_pitch;
	float m_zoom;
};


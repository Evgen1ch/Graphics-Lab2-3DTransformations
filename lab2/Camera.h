#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum class CameraMovement: uint8_t
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

//dafault camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera
{
public:	
	//constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
	       float yaw = YAW, float pitch = PITCH);
	// constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


	glm::mat4 getViewMatrix() const {return LookAt(Position, Position + Front, Up); }
	void ProcessKeyboard(CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

	static glm::mat4 LookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);

private:
	void updateCameraVectors();

public:
	//camera attributes
	glm::vec3 Position{};
	glm::vec3 Front;
	glm::vec3 Up{};
	glm::vec3 Right{};
	glm::vec3 WorldUp{};
	
	//euler angles
	float Yaw;
	float Pitch;
	
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Fov{};
};

#endif


#pragma once
#include <cstdint>

#include "Model.h"
#include "transtormations.h"

enum class RotationDirection : uint8_t
{
	Up,
	Down,
	Left,
	Right,
	RollLeft,
	RollRight,
};

enum class MovementDirection : uint8_t
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	BACKWARD,
	FORWARD
};

//dafault camera values
const float MOVEMENT_SPEED = 2.5f;
const float ROTATION_SPEED = 2.0f;

class LabTransformator
{
public:
	LabTransformator();
	void reset();
	void processRotation(RotationDirection dir, float deltaTime);
	void processTranslation(MovementDirection dir, float deltaTime);
	
	glm::mat4 getTransformationMatrix() const;
private:
	float movementSpeed;
	float rotationSpeed;
	glm::mat4 rotationMatrix{1.0f};
	glm::mat4 translationMatrix{1.0f};
	glm::mat4 transform{ 1.0f };
};


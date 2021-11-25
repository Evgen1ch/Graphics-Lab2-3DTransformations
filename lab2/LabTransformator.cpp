#include "LabTransformator.h"

LabTransformator::LabTransformator()
	:movementSpeed(MOVEMENT_SPEED), rotationSpeed(ROTATION_SPEED)
{
}

void LabTransformator::reset()
{
	translationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::mat4(1.0f);
}

void LabTransformator::processRotation(RotationDirection dir, float deltaTime)
{
	float rotation = this->rotationSpeed * deltaTime;
	if (dir == RotationDirection::Up)
		transform = mt::rotate(transform, rotation, glm::vec3(-1.0f, 0.0f, 0.0f));
	if (dir == RotationDirection::Down)
		transform = mt::rotate(transform, rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	if (dir == RotationDirection::Left)
		transform = mt::rotate(transform, rotation, glm::vec3(0.0f, -1.0f, 0.0f));
	if (dir == RotationDirection::Right)
		transform = mt::rotate(transform, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	if (dir == RotationDirection::RollLeft)
		transform = mt::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	if (dir == RotationDirection::RollRight)
		transform = mt::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, -1.0f));
}

void LabTransformator::processTranslation(MovementDirection dir, float deltaTime)
{
	float velocity = this->movementSpeed * deltaTime;
	if (dir == MovementDirection::UP)
		transform = mt::translate(transform, glm::vec3(0.0f, velocity, 0.0f));
	if (dir == MovementDirection::DOWN)
		transform = mt::translate(transform, glm::vec3(0.0f, -velocity, 0.0f));
	if (dir == MovementDirection::RIGHT)
		transform = mt::translate(transform, glm::vec3(-velocity, 0.0f, 0.0f));
	if (dir == MovementDirection::LEFT)
		transform = mt::translate(transform, glm::vec3(velocity, 0.0f, 0.0f));
	if (dir == MovementDirection::FORWARD)
		transform = mt::translate(transform, glm::vec3(0.0f, 0.0f, -velocity));
	if (dir == MovementDirection::BACKWARD)
		transform = mt::translate(transform, glm::vec3(0.0f, 0.0f, velocity));
}

glm::mat4 LabTransformator::getTransformationMatrix() const
{
	return transform;
}



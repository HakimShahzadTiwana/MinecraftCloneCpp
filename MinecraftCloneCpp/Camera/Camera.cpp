#include "Camera.h"
#include "Debugging/Logger.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	LOG_FUNC();

	// Set Camera position a bit behind the world origin
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	// Point the camera towards the origin 
	// This is the direction vector 
	// (technically its the negative direction vector since its pointing away from the direction the camera is looking at)
	cameraTarget = glm::vec3(0.0f);
	cameraFront = glm::normalize(cameraTarget - cameraPos);

	// Get the right vector in camera space
	cameraRight = glm::normalize(glm::cross(worldUp, cameraFront));

	// Get the up vector in camera space
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));

	updateViewMat();
}

void Camera::setPos(glm::vec3 newPos)
{
	LOG_FUNC();

	cameraPos = newPos;
	updateViewMat();
}

void Camera::setTarget(glm::vec3 newTarget)
{
	LOG_FUNC();

	cameraTarget = newTarget;

	// Update direction vectors based on target
	cameraFront = glm::normalize(cameraTarget - cameraPos);
	cameraRight = glm::normalize(glm::cross(worldUp, cameraFront));
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));

	updateViewMat();
}

void Camera::moveForward(float deltaTime)
{
	LOG_FUNC();

	cameraPos += (cameraSpeed * cameraFront) * deltaTime;
	updateViewMat();
}

void Camera::moveRight(float deltaTime)
{
	LOG_FUNC();

	cameraPos -= (glm::normalize(glm::cross(cameraFront, cameraUp))* cameraSpeed) * deltaTime;
	updateViewMat();
}

void Camera::onCursorMoved(double xOffset, double yOffset)
{
	LOG_FUNC();

	yaw += xOffset;
	pitch += yOffset;

	// Constraints for pitch
	pitch = glm::clamp(pitch, minPitch, maxPitch);

	// update direction vectors
	cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	cameraFront = glm::normalize(cameraFront);
	cameraRight = glm::normalize(glm::cross(worldUp, cameraFront));
	cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));

	updateViewMat();
}

void Camera::onMouseScroll(double xOffset, double yOffset)
{
	LOG_FUNC();

	fov -= (float)yOffset;

	// Constraint for FOV
	fov = glm::clamp(fov, minFOV, maxFOV);
	
	updateViewMat();
		
}

void Camera::updateViewMat()
{
	LOG_FUNC();

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
}


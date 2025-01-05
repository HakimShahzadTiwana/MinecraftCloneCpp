#pragma once
#include <glm/glm.hpp>


class Camera 
{
public:

	Camera();
	~Camera() {};

	// Setters 
	void setPos(glm::vec3 newPos);
	void setTarget(glm::vec3 newTarget);

	// Getters
	float getYaw() { return yaw; };
	float getPitch() { return pitch; };

	float getFOV() { return fov; };

	glm::vec3 getPos() { return cameraPos; };
	glm::vec3 getTarget() { return cameraTarget; };

	glm::vec3 getFrontVec() { return cameraFront; };
	glm::vec3 getRightVec() { return cameraRight; };
	glm::vec3 getUpVec() { return cameraUp; };

	glm::mat4 getViewMat() { return view; };
	

	void moveForward(float deltaTime);
	void moveRight(float deltaTime);

	// Move the camera with the cursor
	void onCursorMoved(double offsetX, double offsetY);

	// Zoom in and zoom out when scrolling
	void onMouseScroll(double offsetX, double offsetY);



private:

	float yaw = -90.0f;
	
	float pitch = 0.0f;
	float minPitch = -89.0f;
	float maxPitch = 89.0f;

	float fov = 45.0f;
	float minFOV = 1.0f;
	float maxFOV = 45.0f;

	float cameraSpeed = 2.5f;

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;

	glm::vec3 cameraFront;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;

	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	

	void updateViewMat();

};
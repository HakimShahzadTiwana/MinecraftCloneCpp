#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "openGL/shader/Shader.h"

#include "openGL/buffer/VBO.h"
#include "openGL/buffer/EBO.h"
#include "openGL/buffer/VAO.h"

#include "Camera/Camera.h"

#include "GlobalProperties.h"

class Window 
{

	GLFWwindow* window;

public:

	Window(int width, int height, const std::string& windowName);
	~Window();

	// Initialize window 
	bool initWindow(int width, int height, const std::string& windowName);

	// Returns the reference of glfw Window
	 GLFWwindow* getGlfwWindow() { return window; };

	// Starts the render loop 
	// TODO Make an application class and a render class
	 void run();


	// Terminate proccesses and cleanup
	 void cleanUp();

	// Handle Callback events
	void handleResizeCallback(int width, int height);
	void handleMouseCallback(double xpos, double ypos);
	void handleScrollCallback(double xOffset, double yOffset);
private:

	Camera camera;

	float deltaTime = 0.0;
	float lastFrame = 0.0;

	float lastCursorX;
	float lastCursorY;

	void handleKeyBoardEvents();
	 

};
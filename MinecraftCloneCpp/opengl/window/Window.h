#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "GlobalProperties.h"

class Window 
{
	static std::unique_ptr<Window> instance;
	static GLFWwindow* window;

public:

	Window() {};
	~Window() { cleanUp(); };

	// Returns the instance of the singleton window object
	static Window& GetInstance();

	// Initialize window 
	 bool initWindow();

	// Returns the reference of glfw Window
	 GLFWwindow* getGlfwWindow() { return window; };

	// Starts the render loop 
	 void runWindow();

	// Terminate proccesses and cleanup
	 void cleanUp();

	
private:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static void HandleKeyBoardEvents();

};
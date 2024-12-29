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

	// Initialize window 
	static bool initWindow();

	// Returns the reference of glfw Window
	 static GLFWwindow* getGlfwWindow() { return window; };

	// Starts the render loop 
	 static void runWindow();

	// Terminate proccesses and cleanup
	static void cleanUp();

	
private:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static void HandleKeyBoardEvents();

};
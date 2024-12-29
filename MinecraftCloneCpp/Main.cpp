#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Main.h"
#include "Debug/Logger.h"
#include "openGL/window/Window.h"



int main()
{	
	if (!Window::initWindow())
	{
		LOG(Error, "Could not init Window!");
		return 0;
	}

	Window::runWindow();

	return 0;
}

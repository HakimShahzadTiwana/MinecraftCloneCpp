#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Main.h"
#include "Debug/Logger.h"
#include "openGL/window/Window.h"



int main()
{	
	if (!Window::GetInstance().initWindow())
	{
		LOG(Error, "Could not init Window!");
		return 0;
	}

	Window::GetInstance().runWindow();

	return 0;
}

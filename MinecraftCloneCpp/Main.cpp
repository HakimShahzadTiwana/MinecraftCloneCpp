#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Main.h"
#include "Debugging/Logger.h"
#include "openGL/window/Window.h"



int main()
{	
	Window window(WindowProperties::width, WindowProperties::height, "MinecraftClone");
	window.run();

	
	return 0;
}

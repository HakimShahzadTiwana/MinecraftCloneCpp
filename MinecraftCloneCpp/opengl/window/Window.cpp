#include "Window.h"
#include "Debug/Logger.h"


std::unique_ptr<Window> Window::instance;
GLFWwindow* Window::window = nullptr;

Window& Window::GetInstance()
{
	if (!instance) 
	{
		instance = std::make_unique<Window>();
	}
	return *instance;
}

bool Window::initWindow()
{
	LOG_FUNC();

	// Init the GLFW module
	glfwInit();

	// Configure GLWF with the current openGL version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLProperties::majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLProperties::minorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, OpenGLProperties::profileType);

	// Create window object
	window = glfwCreateWindow(WindowProperties::width, WindowProperties::height, "MinceCraftClone", NULL, NULL);

	if (!window)
	{
		LOG(Error, "Failed to create GLFW window");
		cleanUp();
		return false;
	}

	// Set window object as current context
	glfwMakeContextCurrent(window);

	// Init Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG(Error, "Failed to initialize GLAD");
		cleanUp();
		return false;
	}

	// Set viewport
	glViewport(0, 0, WindowProperties::width, WindowProperties::height);

	// Bind callback
	glfwSetFramebufferSizeCallback(window, [](auto window, int width, int height)
	{
		LOG(Verbose, "FrameBuffer Size callback called");
		glViewport(0, 0, width, height);
	});

	return true;
}

void Window::runWindow()
{
	LOG_FUNC();

	while (!glfwWindowShouldClose(window))
	{
		HandleKeyBoardEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render here

		// Swap to display updated buffer
		glfwSwapBuffers(window);

		// Check for events that have been triggered
		glfwPollEvents();
	}
}


void Window::cleanUp()
{
	LOG_FUNC();

	if (window)
	{
		glfwDestroyWindow (window);
		window = nullptr;
	}

	glfwTerminate();
}

void Window::HandleKeyBoardEvents()
{
	// Keyboard events
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}





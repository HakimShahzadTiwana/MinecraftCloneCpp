#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Debugging/Logger.h"
#include "openGL/Texture/Texture.h"

#include "App/src/World/WorldChunks.h"


Window::Window(int width, int height, const std::string& windowName)
{
	LOG_FUNC();

	initWindow(width,height,windowName);
}

Window::~Window()
{
	LOG_FUNC();

	cleanUp();
}

bool Window::initWindow(int width, int height, const std::string& windowName)
{
	LOG_FUNC();

	// Init the GLFW module
	glfwInit();

	// Configure GLWF with the current openGL version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLProperties::majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLProperties::minorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, OpenGLProperties::profileType);

	// Create window object
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!window)
	{
		LOG(Error, "Failed to create GLFW window");
		cleanUp();
		return false;
	}


	// Set window object as current context
	glfwMakeContextCurrent(window);

	// Associates any type of pointer (in this case the this pointer) to a window
	glfwSetWindowUserPointer(window, this);

	// Init Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG(Error, "Failed to initialize GLAD");
		cleanUp();
		return false;
	}

	// Set viewport
	glViewport(0, 0, width, height);

	lastCursorX = width / 2;
	lastCursorY = height / 2;

	// Bind callbacks
	glfwSetFramebufferSizeCallback(window, [](auto window, int width, int height)
	{
			auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

			thisWindow->handleResizeCallback(width,height);
	});

	glfwSetCursorPosCallback(window, [](auto window, double xPos, double yPos) 
	{
		auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		thisWindow->handleMouseCallback(xPos, yPos);
		
	});

	glfwSetScrollCallback(window, [](auto window, double xOffset, double yOffset) 
	{
		auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		thisWindow->handleScrollCallback(xOffset, yOffset);
	});
	

	return true;
}

void Window::run()
{
	LOG_FUNC();

	WorldChunks wc;
	wc.generateChunks();

	if (RenderProperties::wireFrameMode) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader("Shaders/basic.vert", "Shaders/basic.frag");
	shader.activate();

	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		handleKeyBoardEvents();

		CameraProperties::fov = camera.getFOV();
		CameraProperties::viewMatrix = camera.getViewMat();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4f("model", model);
		shader.setMat4f("view", camera.getViewMat());
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(CameraProperties::fov), (float) WindowProperties::width / WindowProperties::height, 0.1f, 100.0f);
		shader.setMat4f("projection", projection);

		wc.draw();
		
		
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

void Window::handleKeyBoardEvents()
{
	LOG_FUNC();

	// Keyboard events
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		camera.moveForward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
	{
		camera.moveForward(-deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.moveRight(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.moveRight(-deltaTime);
	}


}

void Window::handleResizeCallback(int width, int height)
{
	LOG_FUNC();

	glViewport(0, 0, width, height);
}

void Window::handleMouseCallback(double xPos, double yPos)
{
	LOG_FUNC();

	static bool firstMouse = true;

	if (firstMouse)
	{
		lastCursorX = xPos;
		lastCursorY = yPos;
		firstMouse = false;
	}


	float xoffset = xPos - lastCursorX;
	float yoffset = lastCursorY - yPos; // reversed since y-coordinates range from bottom to top
	lastCursorX = xPos;
	lastCursorY = yPos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// Move the camera
	camera.onCursorMoved(xoffset, yoffset);

}

void Window::handleScrollCallback(double xOffset, double yOffset)
{
	LOG_FUNC();

	camera.onMouseScroll(xOffset, yOffset);
}





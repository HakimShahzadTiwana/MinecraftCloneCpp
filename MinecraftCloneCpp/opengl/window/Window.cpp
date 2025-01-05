#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Debugging/Logger.h"
#include "openGL/Texture/Texture.h"


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

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};



	Shader shader("Shaders/basic.vert", "Shaders/basic.frag");

	// Create buffers
	VAO vao;
	VBO vbo;
	//EBO ebo;

	// Bind buffers
	vao.bind();
	vbo.bind();
	//ebo.bind();

	// upload data to buffers
	vbo.uploadData(vertices, sizeof(vertices));
	//ebo.uploadData(indices, sizeof(indices));

	// Link buffers to vao
	vao.LinkVBO(vbo, 0, 5 * sizeof(float), 0);
	vao.LinkVBO(vbo, 2, 5 * sizeof(float), 3 * sizeof(float));
	//vao.LinkVBO(vbo, 2, 8 * sizeof(float), 6 * sizeof(float));
	// Unbind buffers
	vao.unBind();
	vbo.unBind();
	//ebo.unBind();	


	Texture tex1("Textures/container.jpg");
	Texture tex2("Textures/wall.jpg");
	
	shader.activate();
	shader.setInt("texSampler1", 0);
	shader.setInt("texSampler2", 1);




	if (RenderProperties::wireFrameMode) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);





	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		handleKeyBoardEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render here
		// Activate the shader program
		
		//LOG_FUNC();
		float timeValue = glfwGetTime();
		float normalizedTimeValue = 0.5f + 0.5f * std::sin(timeValue);
		// Calculate RGB offsets based on time
		
		// Rodate the model so that it lies flat on the floor
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(50.0f)*timeValue, glm::vec3(1, 0, 0));
		shader.setMat4f("model", model);

		shader.setMat4f("view", camera.getViewMat());

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMat4f("projection", projection);

		
		// Send the color offset to the shader
		shader.setFloat("alpha", normalizedTimeValue);

		tex1.bind();
		tex1.setActiveTexture(0);

		tex2.bind();
		tex2.setActiveTexture(1);

		vao.bind();
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4f("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		

		// Swap to display updated buffer
		glfwSwapBuffers(window);

		// Check for events that have been triggered
		glfwPollEvents();
	}

	shader.cleanUp();
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





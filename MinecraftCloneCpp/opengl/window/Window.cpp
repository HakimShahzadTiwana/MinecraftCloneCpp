#include "Window.h"
#include "Debug/Logger.h"


std::unique_ptr<Window> Window::instance;
GLFWwindow* Window::window = nullptr;


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

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	Shader shader("Shaders/basic.vert", "Shaders/basic.frag");

	// Create buffers
	VAO vao;
	VBO vbo;
	EBO ebo;

	// Bind buffers
	vao.bind();
	vbo.bind();
	ebo.bind();

	// upload data to buffers
	vbo.uploadData(vertices, sizeof(vertices));
	ebo.uploadData(indices, sizeof(indices));

	// Link buffers to vao
	vao.LinkVBO(vbo, 0);

	// Unbind buffers
	vao.unBind();
	vbo.unBind();
	ebo.unBind();


	if (RenderProperties::wireFrameMode) 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	

	while (!glfwWindowShouldClose(window))
	{
		HandleKeyBoardEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render here
		// Activate the shader program
		shader.activate();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		

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

void Window::HandleKeyBoardEvents()
{
	// Keyboard events
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}





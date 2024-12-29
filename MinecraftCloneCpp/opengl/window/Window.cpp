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


	const char* vertexShaderSource = "#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// Create a Vertex Shader 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Inject the source code of the shader 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compile the shader
	glCompileShader(vertexShader);

	// Check for errors in compilation
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOG(Error, " Vertex Shader failed to compile with the following information : {}", infoLog);
	}

	// Create a fragment shader
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Inject the fragment shader source code 
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);

	// Compile the source code
	glCompileShader(fragShader);

	// Check for errors in compilation
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		LOG(Error, " Fragment Shader failed to compile with the following information : {}", infoLog);
	}

	// Create a shader program
	// A Shader program links each shader together and sends the output of one shader to the inputs of the next
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach shaders and link them
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	// Check for erros while linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		LOG(Error, " Shader program failed to link with the following information : {}", infoLog);
	}

	// Dont need the individual shaders now since we've compiled and linked them into the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);



	// Generate Vertex Array Object 
	// These are used to save VBO attribute configurations
	// So that you dont have to keep creating attrib pointers every time you need to bind the VBOs, only have to do it once
	// But have to make sure that the VAO is generated before attempting to make the attrib pointers 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Generate Vertex Buffer and store it in a vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Generate Element Buffer 
	unsigned int EBO;
	glGenBuffers(1, &EBO);


	// Again, make sure to bind VAO before the VBO so that it saves configurations 
	glBindVertexArray(VAO);

	// Bind the generated buffer.
	// What we're doing here is telling the gpu to keep memory for the vertex buffer. This buffer is an ArrayBuffer type.
	// You can have multiple types of buffers binded, but only one buffer can be binded for each type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	
	// We send the data of the vertex buffer to the memory that is being used for the array buffer
	// Since the vertex data will be used alot but wont be changed, we use a GL Static Draw type.
	// For info about more types look at the Notes.txt file (Buffer Usage Types)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the generated Element Buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Refer to Notes.txt for more info about Element Array Buffer (Drawing a Rectangle)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Tell openGL about the layout of the vertex data and enable the Attrib Array.
	// For info about the parameters refer to Notes.txt (VertexAttribPointer Parameter Details)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		

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





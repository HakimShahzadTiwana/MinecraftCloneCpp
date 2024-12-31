#include <stb/stb_image.h>

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
	 // Pos             //Color           // Texcoords
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f ,0.0f, 1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f ,0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f  // top left 
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
	vao.LinkVBO(vbo, 0, 8 * sizeof(float), 0);
	vao.LinkVBO(vbo, 1, 8 * sizeof(float), 3 * sizeof(float));
	vao.LinkVBO(vbo, 2, 8 * sizeof(float), 6 * sizeof(float));
	// Unbind buffers
	vao.unBind();
	vbo.unBind();
	ebo.unBind();	


	// Images usually have flipped co-ordinates compared to texCoords so we flip them again
	stbi_set_flip_vertically_on_load(true);

	// Load Texture file 
	int width, height, nChannels;
	unsigned char* texData = stbi_load("Textures/container.jpg", &width, &height, &nChannels,0);

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Convert loaded image data into texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);

	// Generate mip maps
	glGenerateMipmap(GL_TEXTURE_2D);

	texData = stbi_load("Textures/wall.jpg", &width, &height, &nChannels, 0);
	GLuint texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Convert loaded image data into texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);

	// Generate mip maps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Release the image data since we've converted it into a texture and dont need it anymore
	stbi_image_free(texData);

	glBindTexture(GL_TEXTURE_2D, 0);



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
	

	while (!glfwWindowShouldClose(window))
	{
		HandleKeyBoardEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render here
		// Activate the shader program
		
		//LOG_FUNC();
		float timeValue = glfwGetTime();

		// Calculate RGB offsets based on time
		float red = 0.5f + 0.5f * std::sin(timeValue);
		float green = 0.5f + 0.5f * sin(timeValue + 2.094f); // 2?/3 radians phase shift
		float blue = 0.5f + 0.5f * sin(timeValue + 4.188f); // 4?/3 radians phase shift

		// Send the color offset to the shader
		shader.set3FloatVector("colorOffset", red, green, blue);
		shader.setFloat("alpha", red);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
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





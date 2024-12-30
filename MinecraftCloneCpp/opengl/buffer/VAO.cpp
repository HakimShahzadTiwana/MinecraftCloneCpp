#include "VAO.h"

VAO::VAO()
{
	// Generate Vertex Array Object 
	// These are used to save VBO attribute configurations
	// So that you dont have to keep creating attrib pointers every time you need to bind the VBOs, only have to do it once
	// But have to make sure that the VAO is generated before attempting to make the attrib pointers 
	glGenVertexArrays(1, &ID);
}

void VAO::bind()
{
	// Again, make sure to bind VAO before the VBO so that it saves configurations 
	glBindVertexArray(ID);
}

void VAO::unBind()
{
	// Unbind buffers
	glBindVertexArray(0);
}

void VAO::cleanUp()
{
	glDeleteVertexArrays(1,&ID);
}

void VAO::LinkVBO(VBO vbo, GLuint layout)
{
	vbo.bind();
	// Tell openGL about the layout of the vertex data and enable the Attrib Array.
	// For info about the parameters refer to Notes.txt (VertexAttribPointer Parameter Details)
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
	vbo.unBind();
}



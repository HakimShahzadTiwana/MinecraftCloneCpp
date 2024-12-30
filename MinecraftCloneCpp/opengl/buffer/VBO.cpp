#include "VBO.h"

VBO::VBO()
{
	// Generate Vertex Buffer and store it in a vertex buffer object
	glGenBuffers(1, &ID);
}

VBO::VBO(GLfloat* data, GLsizei size)
{
	// Generate Vertex Buffer and store it in a vertex buffer object
	glGenBuffers(1, &ID);

	// Bind the buffer and add in the initial data
	bindAndUpload(data, size);
}

void VBO::bind()
{
	// Bind the generated buffer.
	// What we're doing here is telling the gpu to keep memory for the vertex buffer. This buffer is an ArrayBuffer type.
	// You can have multiple types of buffers binded, but only one buffer can be binded for each type
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unBind()
{
	// Unbind the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::uploadData(GLfloat* data, GLsizei size)
{
	// We send the data of the vertex buffer to the memory that is being used for the array buffer
	// Since the vertex data will be used alot but wont be changed, we use a GL Static Draw type.
	// For info about more types look at the Notes.txt file (Buffer Usage Types)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

void VBO::bindAndUpload(GLfloat* data, GLsizei size)
{
	bind();
	uploadData(data, size);
	unBind();
}

void VBO::cleanUp()
{
	glDeleteBuffers(1, &ID);
}

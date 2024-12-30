#include "EBO.h"

EBO::EBO()
{
	// Generate Buffer 
	glGenBuffers(1, &ID);
}

EBO::EBO(GLuint* data, GLsizei size)
{
	// Generate Buffer 
	glGenBuffers(1, &ID);

	// Bind the buffer and add in the initial data
	bindAndUpload(data, size);

}

void EBO::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::cleanUp()
{
	glDeleteBuffers(1, &ID);
}

void EBO::uploadData(GLuint* data, GLsizei size)
{
	// Refer to Notes.txt for more info about Element Array Buffer (Drawing a Rectangle)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void EBO::bindAndUpload(GLuint* data, GLsizei size)
{
	bind();
	uploadData(data, size);
	unBind();
}

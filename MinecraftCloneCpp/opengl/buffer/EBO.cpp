#include "EBO.h"
#include "Debugging/Logger.h"
EBO::EBO()
{
	LOG_FUNC();

	// Generate Buffer 
	glGenBuffers(1, &ID);
}

EBO::EBO(GLuint* data, GLsizei size)
{
	LOG_FUNC();

	// Generate Buffer 
	glGenBuffers(1, &ID);

	// Bind the buffer and add in the initial data
	bindAndUpload(data, size);

}

void EBO::bind()
{
	LOG_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unBind()
{
	LOG_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::cleanUp()
{
	LOG_FUNC();

	glDeleteBuffers(1, &ID);
}

void EBO::uploadData(GLuint* data, GLsizei size)
{
	LOG_FUNC();

	// Refer to Notes.txt for more info about Element Array Buffer (Drawing a Rectangle)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void EBO::bindAndUpload(GLuint* data, GLsizei size)
{
	LOG_FUNC();

	bind();
	uploadData(data, size);
	unBind();
}

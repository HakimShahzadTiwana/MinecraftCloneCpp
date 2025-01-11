#pragma once
#include "opengl/buffer/IBuffer.h"
#include "VBO.h"
class VAO : public IBuffer
{
public:

	VAO();
	virtual void bind();
	virtual void unBind();
	virtual void cleanUp();
	void LinkVBO(VBO vbo, GLuint layout, GLint elementCount, GLsizei stride, int offset);

};

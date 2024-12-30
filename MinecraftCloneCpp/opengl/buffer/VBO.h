#pragma once
#include "opengl/buffer/IBuffer.h"

class VBO : public IBuffer
{
public:

	VBO();
	VBO(GLfloat* data, GLsizei size);

	virtual void bind();
	virtual void unBind();
	virtual void cleanUp();
	void uploadData(GLfloat* data, GLsizei size);
	void bindAndUpload(GLfloat* data, GLsizei size);

};
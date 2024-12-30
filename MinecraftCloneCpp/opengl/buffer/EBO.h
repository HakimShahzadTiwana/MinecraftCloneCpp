#pragma once
#include "opengl/buffer/IBuffer.h"

class EBO : public IBuffer
{
public:
	EBO();
	EBO(GLuint* data, GLsizei size);

	virtual void bind();
	virtual void unBind();
	virtual void cleanUp();

	void uploadData(GLuint* data, GLsizei size);
	void bindAndUpload(GLuint* data, GLsizei size);

};
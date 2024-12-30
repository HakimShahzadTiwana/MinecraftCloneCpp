#pragma once
#include <glad/glad.h>

class IBuffer 
{
protected:
	GLuint ID;

	public:
		virtual void bind() = 0;
		virtual void unBind() = 0;
		virtual void cleanUp() =0;

};
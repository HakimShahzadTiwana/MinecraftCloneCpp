#pragma once
#include <GLFW/glfw3.h>

struct OpenGLProperties
{
	static constexpr int majorVer = 4;
	static constexpr int minorVer = 6;
	static constexpr int profileType = GLFW_OPENGL_CORE_PROFILE;
};

struct WindowProperties 
{
	static constexpr int width = 800;
	static constexpr int height = 600;
};
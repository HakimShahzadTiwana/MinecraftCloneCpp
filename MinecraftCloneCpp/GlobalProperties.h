#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

struct RenderProperties 
{
	static constexpr bool wireFrameMode = false;
};

struct CameraProperties 
{
	inline static float fov = 90.0f;

	inline static glm::mat4 viewMatrix = glm::mat4(1.0f);

};
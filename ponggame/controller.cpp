#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm; 

#include "controller.hpp"

glm::vec3 updatePosition()
{
	static double lastTime = glfwGetTime();
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 800 / 2, 800 / 2);
	
	float mousePos =  0.5f * float(400 - ypos) * deltaTime;
	float keyPos = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		keyPos = 10 * deltaTime;
	}
		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		keyPos = -10 * deltaTime;
	}

	lastTime = currentTime;

	return glm::vec3(mousePos,keyPos, deltaTime);
}
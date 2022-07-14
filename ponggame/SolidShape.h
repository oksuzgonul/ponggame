#pragma once
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <unordered_map>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shaderloader.hpp"
#include "controller.hpp"

enum class CollisionBorder
{
	TOP = 0,
	BOTTOM = 1,
	LEFT = 2,
	RIGHT = 3
};

class SolidShape
{
public:
	SolidShape();
	SolidShape(glm::vec3 positionNew, glm::vec2 dimensionsNew, glm::mat4* ProjectionW, glm::mat4* ViewW);
	virtual void renderSolidShape(glm::vec3 positionNew);
	void CleanUp();
private:
	unsigned int SolidVertexArrayID;
	unsigned int SolidVertexShaderID;
	unsigned int SolidVertexBuffer;
	unsigned int MatrixID;
	glm::vec3 position;
	glm::vec3 initPos;
	glm::vec2 dimensions;
	std::vector<glm::vec3> vertices;
	// Matrices
	glm::mat4* Projection;
	glm::mat4* View;
	std::unordered_map<CollisionBorder, float> collision;
	glm::vec3 direction;
public:
	glm::vec2 getDimensions();
	glm::vec3 getPosition();
	float getCollision(CollisionBorder border);
	glm::vec3 getDirection();
	void setPosition(float positionNew);
	void reset();
};
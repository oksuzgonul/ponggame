#pragma once
#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaderloader.hpp"

using namespace glm;
class UIElement
{
public:
	UIElement();
	virtual void drawUIElement();
	void CleanUp();
	void setVertices(std::vector<glm::vec2> verts);
private:
	unsigned int UIVertexBufferID;
	unsigned int UIShaderID;
	std::vector<glm::vec2> vertices;
	virtual void generateVertices();
};
#include "DottedLine.h"

DottedLine::DottedLine() :
	UIElement()
{
	generateVertices();
	this->setVertices(vertices);
}

void DottedLine::generateVertices()
{
	float stripWidth = 0.02f;
	float stripHeight = 0.08f;
	float stripGap = 0.02f;
	float yValue = 0.99f;
	for (int i = 0; i < 20; i++)
	{
		glm::vec2 vertex_up_left = glm::vec2(-stripWidth / 2, yValue);
		glm::vec2 vertex_up_right = glm::vec2(stripWidth / 2, yValue);
		yValue -= stripHeight;
		glm::vec2 vertex_down_right = glm::vec2(stripWidth / 2, yValue);
		glm::vec2 vertex_down_left = glm::vec2(-stripWidth / 2, yValue);
		yValue -= stripGap;

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);
	}
}

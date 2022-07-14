#include "UIElement.h"

UIElement::UIElement()
{
	glGenBuffers(1, &UIVertexBufferID);
	UIShaderID = LoadShaders("uielement.vertexshader", "uielement.fragmentshader");
	generateVertices();
}

void UIElement::drawUIElement()
{
	glBindBuffer(GL_ARRAY_BUFFER, UIVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);

	glUseProgram(UIShaderID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, UIVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
}

void UIElement::CleanUp()
{
	glDeleteBuffers(1, &UIVertexBufferID);
	glDeleteProgram(UIShaderID);
}

void UIElement::setVertices(std::vector<glm::vec2> verts)
{
	vertices = verts;
}

void UIElement::generateVertices()
{
	glm::vec2 vertex_up_left = glm::vec2(-0.5f, 0.5f);
	glm::vec2 vertex_up_right = glm::vec2(0.5f, 0.5f);
	glm::vec2 vertex_down_right = glm::vec2(0.5f, -0.5f);
	glm::vec2 vertex_down_left = glm::vec2(-0.5f, -0.5f);

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);
}

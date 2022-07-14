#include "SolidShape.h"

SolidShape::SolidShape()
{
}

SolidShape::SolidShape(glm::vec3 positionNew, glm::vec2 dimensionsNew, glm::mat4* ProjectionW, glm::mat4* ViewW) :
	position(positionNew),
	dimensions(dimensionsNew),
	Projection(ProjectionW),
	View(ViewW),
	direction(glm::vec3(0,0,0)),
	initPos(positionNew)
{
	collision.insert({ CollisionBorder::LEFT,position.x - dimensions.x / 2 });
	collision.insert({ CollisionBorder::RIGHT, position.x + dimensions.x / 2 });
	collision.insert({ CollisionBorder::TOP, position.y + dimensions.y / 2 });
	collision.insert({ CollisionBorder::BOTTOM, position.y - dimensions.y / 2 });

	glGenVertexArrays(1, &SolidVertexArrayID);
	glBindVertexArray(SolidVertexArrayID);
	//glGenBuffers(1, &SolidVertexBufferID);
	SolidVertexShaderID = LoadShaders("solid.vertexshader", "solid.fragmentshader");

	glm::vec3 vertex_up_left = glm::vec3(-dimensions.x / 2, dimensions.y / 2, 0.0f);
	glm::vec3 vertex_up_right = glm::vec3(dimensions.x / 2, dimensions.y / 2, 0.0f);
	glm::vec3 vertex_down_right = glm::vec3(dimensions.x / 2, -dimensions.y / 2, 0.0f);
	glm::vec3 vertex_down_left = glm::vec3(-dimensions.x / 2, -dimensions.y / 2, 0.0f);

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);

	glGenBuffers(1, &SolidVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, SolidVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Get a handle for MVP uniform
	MatrixID = glGetUniformLocation(SolidVertexShaderID, "MVP");
}

void SolidShape::renderSolidShape(glm::vec3 positionNew)
{
	// reset the direction if the pad is jiggled up and down
	if ((positionNew.y - position.y) * direction.y < 0)
		direction.y = 0.0f;
	//otherwise keep adding the direction vector
	direction += positionNew - position;
	position = positionNew;
	// Use our shader
	glUseProgram(SolidVertexShaderID);

	// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 Model = glm::translate(glm::mat4(), glm::vec3(position));
	glm::mat4 MVP = *Projection * *View * Model;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, SolidVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	collision.at(CollisionBorder::LEFT) = position.x - dimensions.x / 2;
	collision.at(CollisionBorder::RIGHT) = position.x + dimensions.x / 2;
	collision.at(CollisionBorder::TOP) = position.y + dimensions.y / 2;
	collision.at(CollisionBorder::BOTTOM) = position.y - dimensions.y / 2;
}

void SolidShape::CleanUp()
{
	glDeleteBuffers(1, &SolidVertexBuffer);
	glDeleteProgram(SolidVertexShaderID);
	glDeleteVertexArrays(1, &SolidVertexArrayID);
}

glm::vec2 SolidShape::getDimensions() { return dimensions; }

glm::vec3 SolidShape::getPosition() { return position; }

float SolidShape::getCollision(CollisionBorder border)
{	
	return collision.at(border);
}

glm::vec3 SolidShape::getDirection()
{
	return direction;
}

void SolidShape::setPosition(float positionNew)
{
	position.y = positionNew;
}

void SolidShape::reset()
{
	position = initPos;
	direction = glm::vec3(0.0f);
}


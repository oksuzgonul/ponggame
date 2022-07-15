#pragma once
#include "SolidShape.h"
#include "ScoreBoard.h"

class Ball : public SolidShape
{
public:
	Ball();
	Ball(glm::vec3 positionNew, glm::vec2 dimensions, glm::mat4* ProjectionW, 
		glm::mat4* ViewW, SolidShape* padRightInit, SolidShape* padLeftinit,
		ScoreBoard* sb1init, ScoreBoard* sb2init);
	void updateLocation(float deltaTime);
private:
	float Speed;
	glm::vec3 position;
	glm::vec3 direction;
	SolidShape* padRight;
	SolidShape* padLeft;
	ScoreBoard* sb1;
	ScoreBoard* sb2;
	void checkCollision();
};
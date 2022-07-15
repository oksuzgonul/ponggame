#include "Ball.h"

Ball::Ball() :
	Speed(0.0f),
	SolidShape()
{
}

Ball::Ball(glm::vec3 positionNew, glm::vec2 dimensions, glm::mat4* ProjectionW, 
	glm::mat4* ViewW, SolidShape* pad1init, SolidShape* pad2init,
	ScoreBoard* sb1init, ScoreBoard* sb2init) :
	Speed(1.0f),
	position(positionNew),
	SolidShape(positionNew, dimensions, ProjectionW, ViewW),
	direction(glm::vec3(1.0f, 0.0f, 0.0f)),
	padRight(pad1init),
	padLeft(pad2init),
	sb1(sb1init),
	sb2(sb2init)
{
}

void Ball::updateLocation(float deltaTime)
{
	checkCollision();
	position += Speed * deltaTime * direction;

	this->renderSolidShape(position);
}

void Ball::checkCollision()
{
	if (this->getCollision(CollisionBorder::RIGHT) >= 1.0f)
	{
		// sets the ball to the original position
		position = glm::vec3(0.0f);
		// services the ball to the other player
		direction.x *= -1;
		direction.y = 0;
		padLeft->reset();
		padRight->reset();

		if (sb1->scored())
		{
			sb1->reset();
			sb2->reset();
			return;
		}
	}
	else if (this->getCollision(CollisionBorder::LEFT) <= -1.0f)
	{
		// sets the ball to the original position
		position = glm::vec3(0.0f);
		// services the ball to the other player
		direction.x *= -1;
		direction.y = 0;
		padLeft->reset();
		padRight->reset();

		if (sb2->scored())
		{
			sb1->reset();
			sb2->reset();
			return;
		}
	}
	else if (this->getCollision(CollisionBorder::TOP) >= 1.0f
		|| this->getCollision(CollisionBorder::BOTTOM) <= -1.0f )
	{
		direction.y *= -1;
	}
	else if (this->getCollision(CollisionBorder::LEFT) <= padLeft->getCollision(CollisionBorder::RIGHT)
		&& this->getCollision(CollisionBorder::BOTTOM) <= padLeft->getCollision(CollisionBorder::TOP)
		&& this->getCollision(CollisionBorder::TOP) >= padLeft->getCollision(CollisionBorder::BOTTOM) 
		&& direction.x < 0)
	{
		direction.x *= -1;
		direction.y = padLeft->getDirection().y;
	}
	else if (this->getCollision(CollisionBorder::RIGHT) >= padRight->getCollision(CollisionBorder::LEFT)
		&& this->getCollision(CollisionBorder::BOTTOM) <= padRight->getCollision(CollisionBorder::TOP)
		&& this->getCollision(CollisionBorder::TOP) >= padRight->getCollision(CollisionBorder::BOTTOM) 
		&& direction.x > 0)
	{
		direction.x *= -1;
		direction.y = padRight->getDirection().y;
	}
}

#include "Pad.h"

Pad::Pad() :
	SolidShape(),
	isMouseControlled(0)
{
}
Pad::Pad(glm::vec3 positionNew, glm::vec2 dimensions, glm::mat4* ProjectionW, glm::mat4* ViewW, bool isMouseControlledNew) :
	SolidShape(positionNew, dimensions, ProjectionW, ViewW),
	isMouseControlled(isMouseControlledNew)
{
}

void Pad::renderPad()
{
	glm::vec3 update = updatePosition();
	glm::vec3 newPos = getPosition();

	if (isMouseControlled)
	{
		// update.y is mouse controll input
		newPos.y += update.x;
		//this->setPosition(this->getPosition().y + update.x);
	}
	else
	{
		// update.y is keyboard controll input
		newPos.y += update.y;
		//this->setPosition(this->getPosition().y + update.y);
	}

	this->renderSolidShape(newPos);
}
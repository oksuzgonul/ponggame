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

void Pad::renderPad(float pos)
{
	glm::vec3 newPos = getPosition();
	newPos.y = glm::clamp(newPos.y + pos, -0.75f, 0.75f);
	this->renderSolidShape(newPos);
}
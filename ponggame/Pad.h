#pragma once
#include "SolidShape.h"

class Pad : public SolidShape
{
public:
	Pad();
	Pad(glm::vec3 positionNew, glm::vec2 dimensions, glm::mat4* ProjectionW, glm::mat4* ViewW, bool isMouseControlledNew);
	void renderPad(float pos);
private:
	const bool isMouseControlled;
};
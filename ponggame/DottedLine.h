#pragma once
#include "UIElement.h"

using namespace glm;
class DottedLine : public UIElement
{
public:
	DottedLine();
private:
	std::vector<glm::vec2> vertices;
	virtual void generateVertices() override;
};
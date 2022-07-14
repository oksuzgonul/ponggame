#pragma once
#include "UIElement.h"
#include "texture.hpp"

using namespace glm;
class ScoreBoard
{
public:
	ScoreBoard(int x);
	void printScore();
	void cleanUp();
	bool scored();
	void reset();
private:
	unsigned int ScoreBoardVertexBufferID;
	unsigned int ScoreBoardUVBufferID;
	unsigned int ScoreBoardShaderID;
	unsigned int ScoreBoardTextureID;
	unsigned int ScoreBoardUniformID;
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> uvs;
	void generateVertices(int x);
	void drawNumber();
	void updateUV(const char* score);
	int score;
};
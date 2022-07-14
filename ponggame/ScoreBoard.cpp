#define _CRT_SECURE_NO_DEPRECATE
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(int x) :
	score(0)
{
	ScoreBoardTextureID = loadDDS("fonts.DDS");

	glGenBuffers(1, &ScoreBoardVertexBufferID);
	glGenBuffers(1, &ScoreBoardUVBufferID);

	ScoreBoardShaderID = LoadShaders("numbershader.vertexshader", "numbershader.fragmentshader");

	ScoreBoardUniformID = glGetUniformLocation(ScoreBoardShaderID, "numberSampler");
	generateVertices(x);
	glBindBuffer(GL_ARRAY_BUFFER, ScoreBoardVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
}

void ScoreBoard::printScore()
{
	char num[256];
	sprintf(num, "%d", score);
	updateUV(num);
	drawNumber();
}

void ScoreBoard::cleanUp()
{
	glDeleteBuffers(1, &ScoreBoardVertexBufferID);
	glDeleteBuffers(1, &ScoreBoardUVBufferID);
	glDeleteTextures(1, &ScoreBoardTextureID);
	glDeleteProgram(ScoreBoardShaderID);
}

bool ScoreBoard::scored()
{
	bool won(score == 9);
	if (!won)
	{
		score++;
	}
	return won;
}

void ScoreBoard::reset()
{
	score = 0;
}

void ScoreBoard::generateVertices(int x)
{
	int y = 700;
	int size = 60;

	glm::vec2 vertex_up_left = glm::vec2(x , y + size);
	glm::vec2 vertex_up_right = glm::vec2(x + size, y + size);
	glm::vec2 vertex_down_right = glm::vec2(x + size, y);
	glm::vec2 vertex_down_left = glm::vec2(x , y );

	vertices.push_back(vertex_up_left);
	vertices.push_back(vertex_down_left);
	vertices.push_back(vertex_up_right);

	vertices.push_back(vertex_down_right);
	vertices.push_back(vertex_up_right);
	vertices.push_back(vertex_down_left);
}

void ScoreBoard::drawNumber()
{
	glUseProgram(ScoreBoardShaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ScoreBoardTextureID);
	glUniform1i(ScoreBoardUniformID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, ScoreBoardVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ScoreBoardUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void ScoreBoard::updateUV(const char* score)
{
	uvs.clear();
	float uv_x = (score[0] % 16) / 16.0f;
	float uv_y = (score[0] / 16) / 16.0f;

	glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
	glm::vec2 uv_up_right = glm::vec2(uv_x + 0.5f / 16.0f, uv_y);
	glm::vec2 uv_down_right = glm::vec2(uv_x + 0.5f / 16.0f, (uv_y + 0.5f / 16.0f));
	glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 0.5f / 16.0f));
	uvs.push_back(uv_up_left);
	uvs.push_back(uv_down_left);
	uvs.push_back(uv_up_right);

	uvs.push_back(uv_down_right);
	uvs.push_back(uv_up_right);
	uvs.push_back(uv_down_left);

	glBindBuffer(GL_ARRAY_BUFFER, ScoreBoardUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

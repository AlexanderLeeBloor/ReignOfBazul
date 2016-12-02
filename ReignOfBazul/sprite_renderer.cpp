/**********************************************************************
* SpriteRenderer class
*
* The ResourceManager class draws the sprites from sprite sheets.
**********************************************************************/
#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader, glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize)
{
	this->shader = shader;
	this->initRenderData(normalizedTilePosition, normalizedTileSize);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f*size.x, 0.5f*size.y, 0.0f));	// Move the origin of rotation to the center of the quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));			// Then rotate
	model = glm::translate(model, glm::vec3(-0.5f*size.x, -0.5f*size.y, 0.0f));	// Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector3f("spriteColor", color); // Note: we won't need color for this game

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData(glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize)
{
	// Configure VAO/VBO
	GLuint VBO; // Record the index of this VBO
	GLfloat vertices[] = { // Fix this
		// Pos      // Tex
		0.0f, 1.0f, normalizedTilePosition.x, normalizedTilePosition.y,
		1.0f, 0.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y - normalizedTileSize.y,
		0.0f, 0.0f, normalizedTilePosition.x, normalizedTilePosition.y - normalizedTileSize.y,

		0.0f, 1.0f, normalizedTilePosition.x, normalizedTilePosition.y,
		1.0f, 1.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y,
		1.0f, 0.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y - normalizedTileSize.y
	};
	/*GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};*/

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::UpdateRenderData(glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize)
{
	// Configure VAO/VBO
	GLuint VBO; // Replace this with a glBufferSubData call
	GLfloat vertices[] = { // Fix this
		// Pos      // Tex
		0.0f, 1.0f, normalizedTilePosition.x, normalizedTilePosition.y,
		1.0f, 0.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y - normalizedTileSize.y,
		0.0f, 0.0f, normalizedTilePosition.x, normalizedTilePosition.y - normalizedTileSize.y,

		0.0f, 1.0f, normalizedTilePosition.x, normalizedTilePosition.y,
		1.0f, 1.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y,
		1.0f, 0.0f, normalizedTilePosition.x + normalizedTileSize.x, normalizedTilePosition.y - normalizedTileSize.y
	};

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}
/**********************************************************************
* SpriteRenderer class
*
* The ResourceManager class draws the sprites from sprite sheets.
**********************************************************************/
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:
	// Constructor (initializes shaders/shapes), Destructor
	SpriteRenderer(Shader &shader, glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize);
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void UpdateRenderData(glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize);
private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Put GLuint for a VBO ID number here.

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData(glm::vec2 normalizedTilePosition, glm::vec2 normalizedTileSize);
};

#endif 
/**********************************************************************
* GameLevel class
*
* The GameLevel class holds all tiles for each level (one level is one instance of GameLevel).
* Functions within this class load and render levels from memory.
**********************************************************************/
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel
{
public:
	// Level state
	std::vector<GameObject> Environment; // Formerly "Bricks"

	// Constructor
	GameLevel() {}

	// Load level from file
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);

	// Get tile locations for level
	//glm::vec4 GetTilePositionAndSize(GLuint index);

	// Render level
	void Draw(SpriteRenderer &renderer);

	// Check if the level is complete
	GLboolean IsCompleted();
private:
	// Initialize a level from tile data
	void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif
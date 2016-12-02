/**********************************************************************
* GameObject class
*
* The GameObject class is a container for holding all states relevant for a single game object entity.
* Objects within the game will require the properties of GameObject as a minimum.
**********************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <gl/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
	// Object state
	glm::vec2 Position, Size, Velocity, tilePosition, tileSize;
	glm::vec3 Color; // Probably will be removed
	GLfloat Rotation;
	GLboolean IsSolid;
	GLboolean Destroyed;

	// Render state
	Texture2D Sprite;

	// Constructor(s)
	GameObject();
	GameObject(glm::vec2 tilepos, glm::vec2 tilesize, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};


#endif 
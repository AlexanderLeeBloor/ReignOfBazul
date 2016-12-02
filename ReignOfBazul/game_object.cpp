/**********************************************************************
* GameObject class
*
* The GameObject class is a contained for holding all states relevant for a single game object entity.
* Objects within the game will require the properties of GameObject as a minimum.
**********************************************************************/
#include "game_object.h"

GameObject::GameObject()
	: tilePosition(0.0f, 0.0f), tileSize(0.125f, 0.125f), Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {}

GameObject::GameObject(glm::vec2 tilepos, glm::vec2 tilesize, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: tilePosition(tilepos), tileSize(tilesize), Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) {}

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.UpdateRenderData(this->tilePosition, this->tileSize);
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
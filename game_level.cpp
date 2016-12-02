/**********************************************************************
* GameLevel class
*
* The GameLevel class holds all tiles for each level (one level is one instance of GameLevel).
* Functions within this class load and render levels from memory.
**********************************************************************/
#include "game_level.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
	// Clear old data
	this->Environment.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData; // tileData is a vector of vectors
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word separated by spaces
				row.push_back(tileCode); //
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

/*glm::vec4 GetTilePositionAndSize(GLuint index)
{
	// index should count from zero
	glm::vec4 TilePositionAndSize;

	// Compute (x,y) coordinate of top-left corner, then normalize.
	TilePositionAndSize.x = (index % 8) / 8;
	TilePositionAndSize.y = (index / 8) / 8;
	// All background tiles are 16px by 16px.
	TilePositionAndSize.z = 1 / 8;
	TilePositionAndSize.w = 1 / 8;

	return TilePositionAndSize;
}*/

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : this->Environment)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	// Possible to add in additional checks, such as secrets revealed by destroyed tiles.
	// But if so, is that the best way to go about it?
}

GLboolean GameLevel::IsCompleted()
{
	// TBD: Create win condition (e.g. defeat the boss)
	return false;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	// Note that this function makes the size of the level equal to the window size
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width); // Width and height of individual tiles
	GLfloat unit_height = levelHeight / height;

	// Initialize level tiles based on tileData
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			glm::vec2 pos(unit_width * x, unit_height * y);
			glm::vec2 size(unit_width, unit_height);

			//glm::vec4 tilePositionAndSize = GetTilePositionAndSize((GLuint) tileData[y][x]);
			//glm::vec2 tilepos(tilePositionAndSize.x, tilePositionAndSize.y);
			//glm::vec2 tilesize(tilePositionAndSize.z, tilePositionAndSize.w);

			// Compute (x,y) coordinate of top-left corner, then normalize.
			glm::vec2 tilepos(0.0f, 0.0f);
			tilepos.x = (float)(tileData[y][x] % 8) / 8;
			tilepos.y = (float)(tileData[y][x] / 8) / 8;
			// All background tiles are 16px by 16px.
			glm::vec2 tilesize(0.0f, 0.0f);
			tilesize.x = (float)1 / 8;
			tilesize.y = (float)1 / 8;

			// Check tile type from level data (2D level array)
			// Although not needed to determine which tile to draw, the switch-case may allow special properties to be prescribed to game objects with great flexibility.
			// If it turns out that there are very few special properties to consider, a few if-else if statements can be substituted in for efficiency.
			/*switch (tileData[y][x])
			{
			case 0:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 1:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 2:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 3:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 4:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 5:
				GameObject obj5(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj5.IsSolid = GL_TRUE;
				this->Environment.push_back(obj5);
				break;
			case 6:
				GameObject obj6(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj6.IsSolid = GL_TRUE;
				this->Environment.push_back(obj6);
				break;
			case 7:
				GameObject obj7(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj7.IsSolid = GL_TRUE;
				this->Environment.push_back(obj7);
				break;
			case 8:
				GameObject obj8(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj8.IsSolid = GL_TRUE;
				this->Environment.push_back(obj8);
				break;
			case 9:
				GameObject obj9(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj9.IsSolid = GL_TRUE;
				this->Environment.push_back(obj9);
				break;
			case 10:
				GameObject obj10(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj10.IsSolid = GL_TRUE;
				this->Environment.push_back(obj10);
				break;
			case 11:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 12:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 13:
				GameObject obj13(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj13.IsSolid = GL_TRUE;
				this->Environment.push_back(obj13);
				break;
			case 14:
				GameObject obj14(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj14.IsSolid = GL_TRUE;
				this->Environment.push_back(obj14);
				break;
			case 15:
				GameObject obj15(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj15.IsSolid = GL_TRUE;
				this->Environment.push_back(obj15);
				break;
			case 16:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 17:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 18:
				GameObject obj18(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj18.IsSolid = GL_TRUE;
				this->Environment.push_back(obj18);
				break;
			case 19:
				GameObject obj19(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj19.IsSolid = GL_TRUE;
				this->Environment.push_back(obj19);
				break;
			case 20:
				GameObject obj20(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj20.IsSolid = GL_TRUE;
				this->Environment.push_back(obj20);
				break;
			case 21:
				GameObject obj21(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj21.IsSolid = GL_TRUE;
				this->Environment.push_back(obj21);
				break;
			case 22:
				GameObject obj22(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj22.IsSolid = GL_TRUE;
				this->Environment.push_back(obj22);
				break;
			case 23:
				GameObject obj23(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj23.IsSolid = GL_TRUE;
				this->Environment.push_back(obj23);
				break;
			case 24:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 25:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 26:
				GameObject obj26(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj26.IsSolid = GL_TRUE;
				this->Environment.push_back(obj26);
				break;
			case 27:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 28:
				GameObject obj28(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj28.IsSolid = GL_TRUE;
				this->Environment.push_back(obj28);
				break;
			case 29:
				GameObject obj29(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj29.IsSolid = GL_TRUE;
				this->Environment.push_back(obj29);
				break;
			case 30:
				GameObject obj30(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj30.IsSolid = GL_TRUE;
				this->Environment.push_back(obj30);
				break;
			case 31:
				GameObject obj31(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj31.IsSolid = GL_TRUE;
				this->Environment.push_back(obj31);
				break;
			case 32:
				GameObject obj32(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj32.IsSolid = GL_TRUE;
				this->Environment.push_back(obj32);
				break;
			case 33:
				GameObject obj33(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj33.IsSolid = GL_TRUE;
				this->Environment.push_back(obj33);
				break;
			case 34:
				GameObject obj34(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj34.IsSolid = GL_TRUE;
				this->Environment.push_back(obj34);
				break;
			case 35:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 36:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 37:
				GameObject obj37(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj37.IsSolid = GL_TRUE;
				this->Environment.push_back(obj37);
				break;
			case 38:
				GameObject obj38(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj38.IsSolid = GL_TRUE;
				this->Environment.push_back(obj38);
				break;
			case 39:
				GameObject obj39(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj39.IsSolid = GL_TRUE;
				this->Environment.push_back(obj39);
				break;
			case 40:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 41:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 42:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 43:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 44:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 45:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 46:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 47:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 48:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 49:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 50:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 51:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 52:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 53:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 54:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 55:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 56:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 57:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 58:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 59:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 60:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 61:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 62:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			case 63:
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
				break;
			}*/
/*
			glm::vec2 pos(unit_width * x, unit_height * y);
			glm::vec2 size(unit_width, unit_height);
			glm::vec2 tilepos(0.875f, 0.875f);
			glm::vec2 tilesize(0.125f, 0.125f);
*/
/*			if (tileData[y][x] == 1) // This is a solid tile (note that in Breakout, there was only one type of solid tile, but the GameObject class still had an IsSolid property)
			{
				tilepos.x = 0.875f;
				tilepos.y = 0.875f;
				tilesize.x = 0.125f;
				tilesize.y = 0.125f;

				GameObject obj(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj.IsSolid = GL_TRUE;
				this->Environment.push_back(obj);
			}
			else if (tileData[y][x] > 1) // Other tiles -> This whole if/elseif section will be replaced with something that calls if/elseif ResourceManager::GetFrame(ResourceManager::GetTexture("SpriteSheet"),"Player-Animations", 4);
			{							// Where GetFrame(...) chooses a subsection of the Texture based on a keyword and selects the specific frame to use from an index.
				glm::vec3 color = glm::vec3(1.0f); // White tile
				if (tileData[y][x] == 2)
				{
					tilepos.x = 0.750f;
					tilepos.y = 0.500f;
					tilesize.x = 0.125f;
					tilesize.y = 0.125f;
				}
				if (tileData[y][x] == 3)
				{
					tilepos.x = 0.750f;
					tilepos.y = 0.500f;
					tilesize.x = 0.125f;
					tilesize.y = 0.125f;
				}
				if (tileData[y][x] == 4)
				{
					tilepos.x = 0.750f;
					tilepos.y = 0.500f;
					tilesize.x = 0.125f;
					tilesize.y = 0.125f;
				}
				if (tileData[y][x] == 5)
				{
					tilepos.x = 0.750f;
					tilepos.y = 0.500f;
					tilesize.x = 0.125f;
					tilesize.y = 0.125f;
				}
				//glm::vec2 pos(unit_width * x, unit_height * y);
				//glm::vec2 size(unit_width, unit_height);
				this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), color));
			}*/
			this->Environment.push_back(GameObject(tilepos, tilesize, pos, size, ResourceManager::GetTexture("BackgroundTiles"), glm::vec3(1.0f, 1.0f, 1.0f)));
		}
	}
}
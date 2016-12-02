/**********************************************************************
* ResourceManager class
*
* The ResourceManager class manages the textures and shaders.
* No ResourceManager objects are constructed. Rather, it employs static, publicly available members and functions.
**********************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <gl/glew.h>

#include "texture.h"
#include "shader.h"

class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>	Shaders;
	static std::map<std::string, Texture2D>	Textures;
	// Load & Generate a shader program from file
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	// Retrieve a stored shader
	static Shader GetShader(std::string name);
	// Load & Generate a texture program from file
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	// Retrieve a stored texture
	static Texture2D GetTexture(std::string name);
	// Retrieve a tile from a texture atlas (sprite sheet)
	//static Texture2D ResourceManager::getTileFromTexture(Texture2D texture);
	// De-allocate all loaded resources
	static void Clear();
private:
	// Constructor
	ResourceManager() {}
	// Load and generate a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	// Load and generate a texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif
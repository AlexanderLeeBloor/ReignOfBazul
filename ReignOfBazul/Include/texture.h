/**********************************************************************
* Texture2D class
*
* The Texture2D class stores and configures textures in OpenGL.
* It also contains utility functions for easy management.
**********************************************************************/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

class Texture2D // This class may require additional functions or properties to facilitate a sprite atlas/animation (e.g. an UpdateTexture function)
{
public:
	// Holds the ID of the texture object, used for all texture operations to reference to this particular texture
	GLuint ID;
	// Texture image dimensions
	GLuint Width, Height; // Width and Height of loaded image in pixels
	// Texture Format
	GLuint Internal_Format; // Format of texture object
	GLuint Image_Format; // Format of loaded image
	// Texture configuration
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
	// Constructor
	Texture2D();
	// Generates texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;
};

#endif
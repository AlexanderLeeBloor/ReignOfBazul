/**********************************************************************
* Game class
* 
* The game class manages all aspects of running the game in the game loop.
* This includes:
* 1. Initialization
* 2. Updates
* 3. Processing Inputs
* 4. Rendering
**********************************************************************/
#ifndef GAME_H
#define GAME_H
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_OVER
};

// Size of the player
const glm::vec2 PLAYER_SIZE(64, 64);
// Initial velocity of the player
const GLfloat PLAYER_VELOCITY(300.0f);

// Game holds all game-related state information and functionality.
// All game-related data is combined into this class for easy access to and management of game components.
class Game
{
public:
	// Game state
	GameState				State;
	GLboolean				Keys[1024];
	GLuint					Width, Height;
	std::vector<GameLevel>	Levels;
	GLuint					Level;
	// Constructor, Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders, textures, and levels)
	void Init();
	// Game Loop:
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

#endif
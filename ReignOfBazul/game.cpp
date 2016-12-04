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
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

// Game-related State data
SpriteRenderer		*Renderer;
GameObject			*Player;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("./Shaders/sprite.vs", "./Shaders/sprite.frag", nullptr, "sprite");
	
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	// Load textures
	ResourceManager::LoadTexture("./Images/Sprite-Palette.png", GL_FALSE, "background");
	ResourceManager::LoadTexture("./Images/SpriteSheet.png", GL_TRUE, "SpriteSheet");
	ResourceManager::LoadTexture("./Images/BackgroundTiles.png", GL_TRUE, "BackgroundTiles");
	//ResourceManager::LoadTexture("./Images/awesomeface.png", GL_TRUE, "face");
	//ResourceManager::LoadTexture("./Images/block.png", GL_FALSE, "block");
	//ResourceManager::LoadTexture("./Images/block_solid.png", GL_FALSE, "block_solid");
	//ResourceManager::LoadTexture("./Images/paddle.png", true, "paddle");
	
	// Configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2 - 192, this->Height - PLAYER_SIZE.y - 256);
	glm::vec2 playerSpritePosition = glm::vec2(0.0f, 0.250f);
	glm::vec2 playerSpriteSize = glm::vec2(0.125f, 0.125f);
	Player = new GameObject(playerSpritePosition, playerSpriteSize, playerPos, PLAYER_SIZE, ResourceManager::GetTexture("SpriteSheet"));

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"), playerSpritePosition, playerSpriteSize);

	// Load levels
	GameLevel one, two, three, four;
	one.Load("./Levels/level-one.txt", this->Width, this->Height);
	two.Load("./Levels/level-two.txt", this->Width, this->Height);
	three.Load("./Levels/level-three.txt", this->Width, this->Height);
	four.Load("./Levels/level-four.txt", this->Width, this->Height);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	// Audio (TBD)
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// Move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_S])
		{
			if (Player->Position.y <= this->Height - Player->Size.x)
				Player->Position.y += velocity;
		}
		if (this->Keys[GLFW_KEY_W])
		{
			if (Player->Position.y >= 0)
				Player->Position.y -= velocity;
		}
	}
}

void Game::Update(GLfloat dt)
{

}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// Draw background (Obsolete now because the level tiles ARE the background)
		// Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);

		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		// Draw player
		Player->Draw(*Renderer);
	}
}
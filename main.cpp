/**********************************************************************
* Reign of Bazul:
* A 2D adventure game inspired by Zelda, D&D, and arcade beat 'em ups.
**********************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"

// GLFW function declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Width and height of the screen
//const GLuint SCREEN_WIDTH = 800;
//const GLuint SCREEN_HEIGHT = 600;
const GLuint SCREEN_WIDTH = 960;
const GLuint SCREEN_HEIGHT = 512;

Game ReignOfBazul(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Reign of Bazul", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call to catch glewInit() bug. All other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	ReignOfBazul.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State eventually. Active for now.
	ReignOfBazul.State = GAME_ACTIVE;

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Manage user input
		ReignOfBazul.ProcessInput(deltaTime);

		// Update game state (TBD)

		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ReignOfBazul.Render();

		glfwSwapBuffers(window);
	}
	// Delete all resources as loaded
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			ReignOfBazul.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			ReignOfBazul.Keys[key] = GL_FALSE;
	}
}
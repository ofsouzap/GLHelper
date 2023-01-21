#define _USE_MATH_DEFINES

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "ShaderProgram.h"
#include "SceneObject.h"
#include "ModelReader.h"
#include "Camera.h"
#include "Texture.h"

using namespace GLHelper;

Camera* camera; // Declared here so can be used in key callback

#pragma region Logging

void printError(const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void errorCallback(int error, const char* description)
{
	printError(description);
}

#pragma endregion

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		// Move up
		camera->setPosition({
			camera->getPosition().x,
			camera->getPosition().y + 1,
			camera->getPosition().z
			});
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		// Move down
		camera->setPosition({
			camera->getPosition().x,
			camera->getPosition().y - 1,
			camera->getPosition().z
			});
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		// Move right
		camera->setPosition({
			camera->getPosition().x - 1,
			camera->getPosition().y,
			camera->getPosition().z
			});
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		// Move left
		camera->setPosition({
			camera->getPosition().x + 1,
			camera->getPosition().y,
			camera->getPosition().z
			});
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		// Move back
		camera->setPosition({
			camera->getPosition().x,
			camera->getPosition().y,
			camera->getPosition().z + 1
			});
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		// Move forward
		camera->setPosition({
			camera->getPosition().x,
			camera->getPosition().y,
			camera->getPosition().z - 1
			});
	}
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		// Decrease FOV
		camera->setFov(camera->getFov() - (M_PI / 24.f));
	}
	else if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		// Increase FOV
		camera->setFov(camera->getFov() + (M_PI / 24.f));
	}

}

int main()
{

	GLFWwindow* window;
	int window_width, window_height, window_aspect_ratio;

#pragma region GLFW Window Set-Up

	// Initialise GLFW
	if (glfwInit() != GLFW_TRUE)
	{
		printError("Couldn't initialise GLFW");
		return 1;
	}

	// Set GLFW error callback
	glfwSetErrorCallback(errorCallback);

	// Create window
	window = glfwCreateWindow(512, 512, "GLHelper - Basic Scene Example", NULL, NULL);

	// Check window created
	if (window == NULL)
	{
		printError("Couldn't create window");
		glfwTerminate();
		return 1;
	}

	// Create context
	glfwMakeContextCurrent(window);

	// Initialise glad (must be done after creating window context)
	gladLoadGL(glfwGetProcAddress);

	// Set GLFW key callback
	glfwSetKeyCallback(window, keyCallback);

	// Get framebuffer sizes and give to OpenGL

	glfwGetFramebufferSize(window, &window_width, &window_height);
	window_aspect_ratio = (float)window_height / (float)window_width;
	glViewport(0, 0, window_width, window_height);

	// Set buffer swap interval
	glfwSwapInterval(1);

#pragma endregion

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Create camera object
	camera = new Camera(window_aspect_ratio, M_PI / 4.f);
	camera->setPosition({ 0.f, 0.f, 5.f });

#pragma region Create object

	// Load model

	int vertexCount;
	GLfloat* objPos;
	GLfloat* objUV;
	GLfloat* objNorm;
	ModelReader::readOBJModel("monkey.obj", &vertexCount, &objPos, &objUV, &objNorm);

	// Load texture
	Texture* texture = Texture::fromBMP("monkey_texture.bmp");

	// Create shader program
	ShaderProgram shader("vertex_shader_textured.glsl", "frag_shader_textured.glsl");

	// Create scene object and set its texture
	SceneObject obj(&shader, vertexCount);
	obj.addAttrib("oc_pos", GL_FLOAT, sizeof(GLfloat), 3, objPos);
	obj.addAttrib("uv", GL_FLOAT, sizeof(GLfloat), 2, objUV);
	obj.setTexture(texture);

#pragma endregion

#pragma region Main Loop

	while (!glfwWindowShouldClose(window))
	{

		// Get current time
		double time = glfwGetTime();

		// Clear with background color
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Create modelling matrix

		mat4x4 m;

		mat4x4_identity(m);
		mat4x4_rotate_Y(m, m, time);

		// Draw object
		obj.draw(m, camera);

		// Swap rendering buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();

	}

#pragma endregion

#pragma region Clean up

	glfwTerminate();

#pragma endregion

	return 0;

}
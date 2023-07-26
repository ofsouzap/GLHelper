#define _USE_MATH_DEFINES

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <stdio.h>

#include "ShaderProgram.h"
#include "SceneObject.h"
#include "ModelReader.h"
#include "Camera.h"
#include "Texture.h"

using namespace GLHelper;
using glm::mat4x4;
using glm::vec3;

Camera* camera;

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
		camera->changePosition({0.0, 1.0, 0.0});
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		// Move down
		camera->changePosition({0.0, -1.0, 0.0});
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		// Move right
		camera->changePosition({-1.0, 0.0, 0.0});
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		// Move left
		camera->changePosition({1.0, 0.0, 0.0});
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		// Move back
		camera->changePosition({0.0, 0.0, 1.0});
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		// Move forward
		camera->changePosition({0.0, 0.0, -1.0});
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
	window = glfwCreateWindow(512, 512, "GLHelper - Terrain Scene Example", NULL, NULL);

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
	camera->setPosition({ 0.f, 10.f, 15.f });
    camera->setAngles({ M_PI / 8.f, 0.f });

    // Create lighting configuration
    vec3 light_pos = vec3(50.f, 50.f, 50.f);
    vec3 light_col_diff = vec3(1.f, 1.f, 0.9f); // Slightly yellow
    vec3 light_col_spec = vec3(1.f, 1.f, 1.f);

#pragma region Create objects

    // Shader (used for both objects)

    ShaderProgram shader("vert_shader.glsl", "frag_shader.glsl");

	// Terrain

	int terrainVertCount;
	GLfloat* terrainPos;
	GLfloat* terrainUV;
	GLfloat* terrainNorm;
	ModelReader::readOBJModel("terrain.obj", &terrainVertCount, &terrainPos, &terrainUV, &terrainNorm);
	Texture* terrainTexture = Texture::fromBMP("terrain_texture.bmp");

	SceneObject terrain(&shader, terrainVertCount);
	terrain.addAttrib("oc_pos", GL_FLOAT, sizeof(GLfloat), 3, terrainPos);
	terrain.addAttrib("uv", GL_FLOAT, sizeof(GLfloat), 2, terrainUV);
	terrain.addAttrib("oc_norm", GL_FLOAT, sizeof(GLfloat), 3, terrainNorm);
	terrain.setTexture(terrainTexture);

    float terrain_diff_coeff = 0.8f;
    float terrain_spec_coeff = 0.2f;
    float terrain_roughness = 0.1f;

    // Creature

    int creatureVertCount;
	GLfloat* creaturePos;
	GLfloat* creatureUV;
	GLfloat* creatureNorm;
	ModelReader::readOBJModel("creature.obj", &creatureVertCount, &creaturePos, &creatureUV, &creatureNorm);
	Texture* creatureTexture = Texture::fromBMP("creature_texture.bmp");

	SceneObject creature(&shader, creatureVertCount);
	creature.addAttrib("oc_pos", GL_FLOAT, sizeof(GLfloat), 3, creaturePos);
	creature.addAttrib("uv", GL_FLOAT, sizeof(GLfloat), 2, creatureUV);
	creature.addAttrib("oc_norm", GL_FLOAT, sizeof(GLfloat), 3, creatureNorm);
	creature.setTexture(creatureTexture);

    float creature_diff_coeff = 0.2f;
    float creature_spec_coeff = 0.8f;
    float creature_roughness = 0.7f;

#pragma endregion

#pragma region Main Loop

	while (!glfwWindowShouldClose(window))
	{

		// Get current time
		double time = glfwGetTime();

		// Clear with background color
		glClearColor(1.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Create modelling matrices

		mat4x4 terrain_m = glm::identity<mat4x4>();

		mat4x4 creature_m = glm::identity<mat4x4>();
        creature_m = glm::translate(creature_m, vec3(-7.5f, 2.2f, -9.0f));
        // creature_m = glm::translate(creature_m, vec3(0.f, 5.f, 0.f));
        creature_m = glm::rotate(
            creature_m,
            0.5f,
            vec3(0.f, 0.f, -1.f)
        );

        // Since I want to give the shader more values, I need to do this manually.
        // shader is the shader used for both objects so I only set the global values once

        shader.useProgram();
        shader.setUniformVec3("wc_light_pos", &light_pos[0]);
        shader.setUniformVec3("light_col_diff", &light_col_diff[0]);
        shader.setUniformVec3("light_col_spec", &light_col_spec[0]);

        // Terrain
        shader.setUniformFloat("diff_coeff", &terrain_diff_coeff);
        shader.setUniformFloat("spec_coeff", &terrain_spec_coeff);
        shader.setUniformFloat("roughness", &terrain_roughness);
		terrain.draw(terrain_m, camera);

        // Creature
        shader.setUniformFloat("diff_coeff", &creature_diff_coeff);
        shader.setUniformFloat("spec_coeff", &creature_spec_coeff);
        shader.setUniformFloat("roughness", &creature_roughness);
		creature.draw(creature_m, camera);

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
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Camera.h"
#include "Scene.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
GLFWwindow *window;

std::vector<Shape*> shapes;
std::vector<Light*> lights;

bool isSceneBunny = false;
	



void ClearFrameBuffer()
{
	memset(&frameBuffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * 3 * sizeof(float));
}

void Display()
{	
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

void CharacterCallback(GLFWwindow* lWindow, unsigned int key) {
	std::cout << "Key " << (char)key << " is pressed." << std::endl;
	switch ((char)key) {
	case 'b':
		isSceneBunny = !isSceneBunny;
		break;
	default:
		break;
	}
}

void Init()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment5 - Dathan Johnson", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glfwSetCharCallback(window, CharacterCallback);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearFrameBuffer();

	bool isSceneChosen = false;
	std::string number;
	int num;
	while (!isSceneChosen) {

		std::cout << "Menu to choose scene. Press the corresponding number with the scene you want to see" << std::endl;
		std::cout << "	1) scene with spheres and planes" << std::endl;
		std::cout << "	2) scene with bunny" << std::endl;

		std::cin >> number;
		num = atoi(number.c_str());
		if (num != 1 && num != 2) {
			std::cout << number << " is an invalid input. Try again" <<std::endl;
		}
		else {
			isSceneChosen = true;
			std::cout << "Loading your scene" << std::endl;
			break;
		}
	}

	Scene scene;
	if (num == 1) {
		scene = Scene();
	}
	else {
		//LoadModel("../obj/bunny.obj");
		scene = Scene(true);
	}
	
	
	Camera camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	auto start = std::chrono::high_resolution_clock::now();
	camera.TakePicture(&scene);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Time passed (ms): " << duration.count() << std::endl;
	
	float *renderedImage = camera.GetRenderedImage();
	memcpy(frameBuffer, renderedImage, sizeof(float) * WINDOW_HEIGHT * WINDOW_WIDTH * 3);
}


int main()
{	
	Init();
	while ( glfwWindowShouldClose(window) == 0) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
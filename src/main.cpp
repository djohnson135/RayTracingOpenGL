#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <chrono>
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"
#include "Triangle.h"
#include "BCH.h"
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
GLFWwindow *window;

std::vector<Shape*> shapes;
std::vector<Light*> lights;

bool isSceneBunny = false;
	
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;

//std::vector<Triangle> triangleVector;
std::vector<Triangle*> triangleShapes;

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

bool LoadModel(char* name, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals)
{
	// Taken from Shinjiro Sueda with slight modification
	std::string meshName(name);
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if (!rc) {
		std::cerr << errStr << std::endl;
		return false;
	}
	else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					vertices.push_back(glm::vec3(attrib.vertices[3 * idx.vertex_index + 0],
						attrib.vertices[3 * idx.vertex_index + 1],
						attrib.vertices[3 * idx.vertex_index + 2]));
					if (!attrib.normals.empty()) {
						normals.push_back(glm::vec3(attrib.normals[3 * idx.normal_index + 0],
							attrib.normals[3 * idx.normal_index + 1],
							attrib.normals[3 * idx.normal_index + 2]));
					}
				}
				index_offset += fv;
			}
		}
	}
	return true;
}

void CreateTriangleVector(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals)
{
	glm::vec3 ka = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 kd = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 ks = glm::vec3(1.0f, 1.0f, 0.5f);
	glm::vec3 km = glm::vec3(0.0f, 0.0f, 0.0f);
	float n = 100.0f;
	
	for (int i = 0; i < vertices.size() / 3; i++)
	{
		
		Triangle * myTriangle = new Triangle(vertices[i * 3 + 0], vertices[i * 3 + 1], vertices[i * 3 + 2], normals[i * 3 + 0], normals[i * 3 + 1], normals[i * 3 + 2], ka, kd, ks, km, n);
		triangleShapes.push_back(myTriangle);
		
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
		glm::vec3 ka = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 kd = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 ks = glm::vec3(1.0f, 1.0f, 0.5f);
		glm::vec3 km = glm::vec3(0.0f, 0.0f, 0.0f);
		float n = 100.0f;

		LoadModel("../obj/bunny.obj", vertices, normals);
		CreateTriangleVector(vertices, normals);
		//BCH * boundingBox = new BCH
		BCH* boundingBox = new BCH(triangleShapes, ka, kd, ks, km, n);


		scene = Scene(boundingBox);
		//scene = Scene()
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
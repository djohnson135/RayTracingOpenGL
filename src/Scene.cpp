#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
Scene::~Scene()
{
}

Scene::Scene()
{
	Light light1( 
		glm::vec3(0.0f, 3.0f, -2.0f), //position
		glm::vec3(0.2f,0.2f,0.2f)	  //color
	);

	Light light2(
		glm::vec3(-2.0f, 1.0f, 4.0f), //position
		glm::vec3(0.5f, 0.5f, 0.5f)	  //color
	);

	this->lights.push_back(&light1);
	this->lights.push_back(&light2);
	//Shape* bpt;

	Sphere* sphere1 = new Sphere(
		glm::vec3(-1.0f, -0.7f, 3.0f), //position
		0.3f, //radius
		glm::vec3(0.1f, 0.1f, 0.1f), //ka
		glm::vec3(0.2f, 1.0f, 0.2f), //kd
		glm::vec3(1.0f, 1.0f, 1.0f), //ks
		glm::vec3(0.0f, 0.0f, 0.0f), //km
		100.0f //n
	);
	Sphere* sphere2 = new Sphere(
		glm::vec3(1.0f, -0.5f, 3.0f), //position
		0.5f, //radius
		glm::vec3(0.1f, 0.1f, 0.1f), //ka
		glm::vec3(0.0f, 0.0f, 1.0f), //kd
		glm::vec3(1.0f, 1.0f, 1.0f), //ks
		glm::vec3(0.0f, 0.0f, 0.0f), //km
		10.0f //n
	);
	//reflective sphere
	Sphere* sphere3 = new Sphere(
		glm::vec3(-1.0f, 0.0f, -0.0f), //position
		1.0f, //radius
		glm::vec3(0.0f, 0.0f, 0.0f), //ka
		glm::vec3(0.0f, 0.0f, 0.0f), //kd
		glm::vec3(0.0f, 0.0f, 0.0f), //ks
		glm::vec3(1.0f, 1.0f, 1.0f), //km
		0.0f //n
	);

	//reflective sphere
	Sphere* sphere4 = new Sphere(
		glm::vec3(1.0f, 0.0f, -1.0f), //position
		1.0f, //radius
		glm::vec3(0.0f, 0.0f, 0.0f), //ka
		glm::vec3(0.0f, 0.0f, 0.0f), //kd
		glm::vec3(0.0f, 0.0f, 0.0f), //ks
		glm::vec3(0.8f, 0.8f, 0.8f), //km
		0.0f //n
	);

	this->shapes.push_back(sphere1);
	this->shapes.push_back(sphere2);
	this->shapes.push_back(sphere3);
	this->shapes.push_back(sphere4);


	Plane* plane1 = new Plane(
		glm::vec3(0.0f,-1.0f,0.0f), //center
		glm::vec3(0.0f, 1.0f, 0.0f), //normal
		glm::vec3(0.1f, 0.1f, 0.1f), //ka
		glm::vec3(1.0f, 1.0f, 1.0f), //kd
		glm::vec3(0.0f, 0.0f, 0.0f), //ks
		glm::vec3(0.0f, 0.0f, 0.0f), //km
		0.0f //n
	);

	//Plane* plane2 = new Plane(
	//	glm::vec3(0.0f, 0.0f, -3.0f), //center
	//	glm::vec3(0.0f, 0.0f, 1.0f), //normal
	//	glm::vec3(0.1f, 0.1f, 0.1f), //ka
	//	glm::vec3(1.0f, 1.0f, 1.0f), //kd
	//	glm::vec3(0.0f, 0.0f, 0.0f), //ks
	//	glm::vec3(0.0f, 0.0f, 0.0f), //km
	//	0.0f //n
	//);

	this->shapes.push_back(plane1); 
	//this->shapes.push_back(plane2); //covers entire scene


}

float Scene::hit(glm::vec3 origin, glm::vec3 ray, float t0, float t1, std::vector<Shape*> & rec)
{
	float t = FLT_MAX;
	for (Shape* shape: this->shapes) {
		float newt = shape->intersect(origin, ray, t0, t1);
		if (newt < t) {
			t = newt;
			rec.clear();
			rec.push_back(shape);
		}
	}
	//for (int i = 0; i < this->shapes.size(); i++) {
	//	//Shape* shape = &shapes.at(i);
	//	glm::vec3 t = this->shapes[i]->intersect(origin, ray, t0, t1);
	//}
	//if (t > 0) return true;

	//hit is false if eauls FLT_MAX
	return t;
}
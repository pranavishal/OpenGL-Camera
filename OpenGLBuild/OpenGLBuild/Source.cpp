#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm/mat4x4.hpp>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "MyWindow.h"
#include "Camera.h"

//pi constant value
const float piValue = 3.14159265f;
//creating the window layout
//const GLint WIDTH = 800;
//const GLint HEIGHT = 600;

// used to convert degrees into radians
const float toRadians = piValue / 180.0f;

MyWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;






// vertex shader vao and vbos
//GLuint shader, uniformModel, uniformProjection;

bool direction = true;
float triOffset = 0.0f;
float triMax = 0.7f;
float triIncrement = 0.005f;

float currentAngle = 0.0f;
bool sizeOfDirection = true;
float currentSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader 
static const char* vShader = "Shaders/shadervert.txt";

// Fragment shader
static const char* fShader = "Shaders/shaderfrag.txt";



void ObjectRenderer() {

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//bottom left coordinate
		-0.86f, -1.0f, 0.0f,
		//background coordinate
		0.0f, -1.0, 1.0f,
		//bottom right coordinate
		1.0f, -0.45f, 0.0f,
		// top coordinate
		0.3f, 0.87f, 0.0f
	};

	Mesh* object1 = new Mesh();
	object1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(object1);

	Mesh* object2 = new Mesh();
	object2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(object2);
	////binding the vao and vbos with their IDs
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenBuffers(1, &ibo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glGenBuffers(1, &vbo);
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//		// data sets to read in at a time, type of data, normalization, skipping data, offset data
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//		glEnableVertexAttribArray(0);

	//	//unbinding the vao and vbos
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

////method to terminate openGL if something fails 
//void termination(const char * message) {
//	printf("%s", message);
//	glfwTerminate();
//}



void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main() 
{
	////Initialize GLFW
	//if (glfwInit() != GLFW_TRUE) {
	//	termination("GLFW was not able to initialize!");
	//	//printf("GLFW was not able to initialize!");
	//	//glfwTerminate();
	//	//standard return value for program exiting with errors
	//	return 1;
	//}

	//// setup GLFW window properties
	//// OpenGL version (using 3.3)
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//// the core profile ensures there is no backwards compatibility
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//// forward compatibility
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	////creating the window using our dimensions established above
	//GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

	//if (!mainWindow) {
	//	termination("GLFW Window creation failed");
	//	//printf("GLFW Window creation failed");
	//	//glfwTerminate();
	//	return 1;

	//}


	////buffer size info
	//int bufferWidth = 0;
	//int bufferHeight = 0;

	//glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//// set everything drawn to mainWindow
	//glfwMakeContextCurrent(mainWindow);

	////allow extension features
	//glewExperimental = GL_TRUE;

	//if (glewInit() != GLEW_OK) {
	//	termination("GLEW failed to initialize");
	//	//printf("GLEW failed to initialize");
	//	glfwDestroyWindow(mainWindow);
	//	//glfwTerminate();
	//	return 1;
	//}

	//glEnable(GL_DEPTH_TEST);

	//// Setup viewport size (top left coordinates, width, height)
	//glViewport(0, 0, bufferWidth, bufferHeight);

	mainWindow = MyWindow(800, 600);
	mainWindow.Initialise();

	ObjectRenderer();
	CreateShaders();


	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// make a loop until the window is closed
	// kind of similar to Unity Update method in C#
	while (!mainWindow.getShouldClose()) {


		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// handle user input (user closes the window manually)
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//if direction is going to the right
		if (direction) {
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}

		if (std::abs(triOffset) >= triMax) {
			direction = !direction;
		}
		float incrementer = 0.1f;
		currentAngle += incrementer;
		if (currentAngle >= 360) {
			currentAngle -= 360.0f;
		}

		float sizeIncrementer = 0.001f;
		if (sizeOfDirection) {
			currentSize += sizeIncrementer;

		}
		else {
			currentSize -= sizeIncrementer;
		}

		if (currentSize >= maxSize || currentSize <= minSize) {
			sizeOfDirection = !sizeOfDirection;
		}

		
		//clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		uniformView = shaderList[0].GetViewLocation();

		glm::mat4 model(1.0f);

		//model = glm::translate(model, glm::vec3(triOffset/*0.0f*/, 0.0f, -2.5f));
		model = glm::rotate(model, (currentAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(triOffset, triOffset * 0.3f, 0.0f));
		
		
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, (currentAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-triOffset/*0.0f*/, 1.0f, -2.5f));
		
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

			//glBindVertexArray(vao);
			////commented out code below shouldn't be needed since the ibo/ebo is still bound to the vao
			////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			//glBindVertexArray(0);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}



	return 0;
}



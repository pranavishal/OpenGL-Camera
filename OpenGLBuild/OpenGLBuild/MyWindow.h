#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class MyWindow
{
public:
	MyWindow();
	MyWindow(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLfloat getBufferWidth() {
		return bufferWidth;
	}

	GLfloat getBufferHeight() {
		return bufferHeight;
	}

	bool getShouldClose() { 
		return glfwWindowShouldClose(mainWindow);
	}

	bool* getsKeys() {
		return keys;
	}

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() {
		glfwSwapBuffers(mainWindow);
	}

	~MyWindow();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	//covering range of ascii characters for input
	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};


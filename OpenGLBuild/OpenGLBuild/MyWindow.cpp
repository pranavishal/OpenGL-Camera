#include "MyWindow.h"

MyWindow::MyWindow() {
	xChange = 0.0f;
	yChange = 0.0f;
	mouseFirstMoved = true;
	width = 800;
	height = 600;

	//initializing key array to get rid of garbage value
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight) {
	xChange = 0.0f;
	yChange = 0.0f;
	mouseFirstMoved = true;
	width = windowWidth;
	height = windowHeight;

	//initializing key array to get rid of garbage value
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

}

//void termination(const char* message) {
//	printf("%s", message);
//	glfwTerminate();
//}

int MyWindow::Initialise() {
	//Initialize GLFW
	if (glfwInit() != GLFW_TRUE) {
		printf("GLFW was not able to initialize!");
		glfwTerminate();
		//termination("GLFW was not able to initialize!");
		//printf("GLFW was not able to initialize!");
		//glfwTerminate();
		//standard return value for program exiting with errors
		return 1;
	}

	// setup GLFW window properties
	// OpenGL version (using 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// the core profile ensures there is no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	//creating the window using our dimensions established above
	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	if (!mainWindow) {
		printf("GLFW Window creation failed");
		glfwTerminate();
		//termination("GLFW Window creation failed");
		//printf("GLFW Window creation failed");
		//glfwTerminate();
		return 1;

	}


	//buffer size info

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set everything drawn to mainWindow
	glfwMakeContextCurrent(mainWindow);

	//handle input from keys and mouse
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//allow extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW failed to initialize");
		glfwTerminate();
		//printf("GLEW failed to initialize");
		glfwDestroyWindow(mainWindow);
		//glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup viewport size (top left coordinates, width, height)
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void MyWindow::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat MyWindow::getXChange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat MyWindow::getYChange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void MyWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int main) {
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("Key has been pressed: %d\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("Key has been released: %d\n", key);
		}
	}
}

void MyWindow::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	//to avoid inverted controls
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	// print mouse input for debugging purposes
	//printf("x: %.6f, y: %.6f\n", theWindow->xChange, theWindow->yChange);
}

MyWindow::~MyWindow() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

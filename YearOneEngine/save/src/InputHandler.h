#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "cmd.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class InputHandler {
public:
	InputHandler(GLFWwindow* window);
	~InputHandler();

	//def keyboard input
	void processInput();
	void setWCmd(Command* command);
	void setSCmd(Command* command);
	void setACmd(Command* command);
	void setDCmd(Command* command);
	void setSpaceBarCmd(Command* command);
	void setClickLeftCmd(Command* command);
private:
	GLFWwindow* window;
	Command* buttonW;
	Command* buttonS;
	Command* buttonA;
	Command* buttonD;
	Command* spaceBar;
	Command* clickLeft;
};



#endif
#pragma once
#include <iostream>
#include <SDL/SDL.h>

class MouseHandler
{
	float last_x, last_y;
	float x, y;
	bool last_left_down;
	bool last_right_down;
	bool left_down;
	bool right_down;
	bool scroll_down;
	bool scroll_up;

public:
	MouseHandler();
	~MouseHandler();

	// Get the x location 
	float getX();
	float getLastX();
	// Get the y location 
	float getY();
	float getLastY();
	// Check button states 
	bool isLeftDown();
	bool wasLeftDown();
	bool isRightDown();
	bool wasRightDown();
	bool scrollUp();
	bool scrollDown();

	// Call to update the mouse state
	void updateState(SDL_Event windowEvent);

	// Call at the end of the game update 
	void update();
};


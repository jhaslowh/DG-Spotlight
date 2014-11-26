#pragma once
#include <iostream>
#include <stdlib.h>
#include "Spotlight.h"
#include "GLHandler.h"

#define SD_MAX_LIGHTS 4

class SpotlightHandler
{
	// Current added light 
	int currentLight;
	Spotlight* lights[SD_MAX_LIGHTS];

	// Arrays to send to shader 
	GLfloat lightPos[SD_MAX_LIGHTS * 4];
	GLfloat lightDir[SD_MAX_LIGHTS * 3];
	GLfloat lightCutOff[SD_MAX_LIGHTS];
	GLfloat lightCutoffInner[SD_MAX_LIGHTS];
	GLfloat lightColor[SD_MAX_LIGHTS * 4];

public:
	SpotlightHandler();
	~SpotlightHandler();

	// Add spotlight to handler 
	void addLight(Spotlight* sl);

	// Set light at index
	// Index must be less than count of current lights 
	void setLight(Spotlight* sl, unsigned int index);
	
	// Remove spotlight from handler 
	void removeLight(unsigned int index);

	// Get light at index 
	Spotlight* getLight(unsigned int index);

	// Send lights to gl 
	void sendLights(GLHandler* mgl);
};


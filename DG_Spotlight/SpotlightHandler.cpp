#include "SpotlightHandler.h"


SpotlightHandler::SpotlightHandler()
{
	currentLight = 0;
	for (int i = 0; i < SD_MAX_LIGHTS; i++)
		lights[i] = NULL;
}

SpotlightHandler::~SpotlightHandler()
{
	for (int i = 0; i < SD_MAX_LIGHTS; i++)
		delete lights[i];
}

// Add spotlight to handler 
void SpotlightHandler::addLight(Spotlight* sl){
	if (currentLight < SD_MAX_LIGHTS){
		lights[currentLight] = sl;
		currentLight++;
	}
	else{
		std::cout << "ERROR: Could not add a new light. Max lights is " << SD_MAX_LIGHTS << " \n";
	}
}

// Set light at index
	// Index must be less than count of current lights 
void SpotlightHandler::setLight(Spotlight* sl, unsigned int index){
	if (index < SD_MAX_LIGHTS && index < currentLight){
		delete lights[index];
		lights[index] = sl;
	}
}

// Remove spotlight from handler 
void SpotlightHandler::removeLight(unsigned int index){
	// Make sure that are lights 
	if (currentLight == 0){
		std::cout << "ERROR: No lights to remove\n";
		return;
	}

	// Make sure index is valid 
	if (index > currentLight - 1){
		std::cout << "ERROR: Index too large\n";
		return;
	}

	// Remove light at index 
	for (int i = index; i < currentLight; i++){
		if (i >= SD_MAX_LIGHTS - 1){
			lights[i] = lights[i + 1];
		}
	}

	// Decrement light count 
	currentLight--;
}

// Get light at index 
Spotlight* SpotlightHandler::getLight(unsigned int index){
	if (index >= SD_MAX_LIGHTS){
		std::cout << "ERROR: Index sent to getLight(unsigned int index) too large\n";
		return NULL;
	}
	return lights[index];
}

// Send lights to gl 
void SpotlightHandler::sendLights(GLHandler* mgl){
	for (int i = 0; i < currentLight; i++){
		// Set light pos 
		lightPos[(i * 4)] = (*lights[i]->getLoc())[0];
		lightPos[(i * 4) + 1] = (*lights[i]->getLoc())[1];
		lightPos[(i * 4) + 2] = (*lights[i]->getLoc())[2];
		lightPos[(i * 4) + 3] = 1.0f;

		// Set light direction 
		lightDir[(i * 3)] = (*lights[i]->getDirec())[0];
		lightDir[(i * 3) + 1] = (*lights[i]->getDirec())[1];
		lightDir[(i * 3) + 2] = (*lights[i]->getDirec())[2];

		// Set light cut off 
		lightCutOff[i] = lights[i]->getCosCutoff();
		// Set light cut off inner
		lightCutoffInner[i] = lights[i]->getCosCutoffInner();
		// Set light color
		lightColor[(i * 4)] = lights[i]->getColor()[0];
		lightColor[(i * 4) + 1] = lights[i]->getColor()[1];
		lightColor[(i * 4) + 2] = lights[i]->getColor()[2];
		lightColor[(i * 4) + 3] = 1.0f;
	}

	// Send light value 
	glUniform1i(mgl->mLightCount, currentLight);
	glUniform4fv(mgl->mLightPosHandle, SD_MAX_LIGHTS, lightPos);
	glUniform3fv(mgl->mSpotLightDirection, SD_MAX_LIGHTS, lightDir);
	glUniform1fv(mgl->mSlotLightCosCutoff, SD_MAX_LIGHTS, lightCutOff);
	glUniform1fv(mgl->mSlotLightCosCutoffInner, SD_MAX_LIGHTS, lightCutoffInner);
	glUniform4fv(mgl->mSLColor, SD_MAX_LIGHTS, lightColor);
}
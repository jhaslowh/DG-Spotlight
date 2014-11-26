#include "Spotlight.h"


Spotlight::Spotlight()
{
	loc = glm::vec3(1, 1, 1);
	cutoff = 60.0f;
	cutoffInner = 40.0f;
	cosCutoff = cos(cutoff * PI_OVER_180);
	cosCutoffInner = cos(cutoffInner * PI_OVER_180);
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
}

Spotlight::~Spotlight()
{

}

// Get location of camera
glm::vec3* Spotlight::getLoc(){
	return &loc;
}
// Set location
void Spotlight::setLoc(glm::vec3 location){
	loc = location;
}

// Set the spotlight cutoff
void Spotlight::setCutoff(float value){
	cutoff = value;
	cosCutoff = cos(cutoff * PI_OVER_180);
}
// Get the cos cut off
float Spotlight::getCosCutoff(){
	return cosCutoff;
}

// Set color for the light
void Spotlight::setColor(float r, float g, float b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
// Get color for light
GLfloat* Spotlight::getColor(){
	return color;
}

// Set the spotlight cutoff inner
void Spotlight::setCutoffInner(float value){
	cutoffInner = value;
	cosCutoffInner = cos(cutoffInner * PI_OVER_180);
}
// Get the cos cut off inner
float Spotlight::getCosCutoffInner(){
	return cosCutoffInner;
}

// Set direction of spotlight
void Spotlight::setDirec(glm::vec3 dir){
	direc = dir;
}

// Get direction of spotlight 
glm::vec3* Spotlight::getDirec(){
	return &direc;
}

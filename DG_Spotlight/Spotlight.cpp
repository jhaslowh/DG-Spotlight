#include "Spotlight.h"


Spotlight::Spotlight()
{
	loc = glm::vec3(1, 1, 1);
	cutoff = 60.0f;
	cutoffInner = 40.0f;
	cosCutoff = cos(cutoff * PI_OVER_180);
	cosCutoffInner = cos(cutoffInner * PI_OVER_180);
	fixRotationMatrix();
	fixDirection();
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
	fixDirection();
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

// Set the spotlight cutoff inner
void Spotlight::setCutoffInner(float value){
	cutoffInner = value;
	cosCutoffInner = cos(cutoffInner * PI_OVER_180);
}
// Get the cos cut off inner
float Spotlight::getCosCutoffInner(){
	return cosCutoffInner;
}

// Set spotlight rotation
void Spotlight::setRotation(glm::quat value){
	orientation = value;
	fixRotationMatrix();
	fixDirection();
}
// Rotate the spotlight 
void Spotlight::rotate(float angle, glm::vec3 axis){
	glm::quat rot = glm::angleAxis(angle, axis);
	orientation = glm::cross(orientation, rot);
	fixRotationMatrix();
	fixDirection();
}

// Get direction of spotlight 
glm::vec3* Spotlight::getDirec(){
	return &direc;
}

// Fix rotation matrix 
void Spotlight::fixRotationMatrix(){
	glm::mat4 rotMatrix = glm::mat4_cast(glm::conjugate(orientation));
	invRotMatrix = glm::inverse(rotMatrix);
}

// Fix direction
void Spotlight::fixDirection(){
	direc = loc + glm::vec3(invRotMatrix * glm::vec4(0, 0, -1, 0));
	direc = glm::normalize(direc - loc);
}
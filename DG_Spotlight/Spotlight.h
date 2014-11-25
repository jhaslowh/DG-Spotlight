#pragma once
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI_OVER_180 (3.14159f / 180.0f)

class Spotlight
{
	// Spotlight location
	glm::vec3 loc;
	glm::vec3 direc;
	// Orientation of spotlight
	glm::quat orientation;
	// Spotlight cutoff 
	float cutoff;
	float cosCutoff;
	// Spotlight cutoff inner 
	float cutoffInner;
	float cosCutoffInner;
	// Inverse Rotation matrix
	glm::mat4 invRotMatrix;
	// Spotlight Color
	GLfloat color[4];

public:
	Spotlight();
	~Spotlight();

	// Get location of camera
	glm::vec3* getLoc();
	// Set location
	void setLoc(glm::vec3 location);
	// Move spotlight
	void move(float dist, glm::vec3 direc);

	// Set the spotlight cutoff
	void setCutoff(float value);
	// Get the cos cut off
	float getCosCutoff();

	// Set color for the light
	void setColor(float r, float g, float b);
	// Get color for light
	GLfloat* getColor();

	// Set the spotlight cutoff inner
	void setCutoffInner(float value);
	// Get the cos cut off inner
	float getCosCutoffInner();

	// Set spotlight rotation
	void setRotation(glm::quat value);
	// Rotate the spotlight 
	void rotate(float angle, glm::vec3 axis);

	// Get direction of spotlight 
	glm::vec3* getDirec();

private:
	// Fix rotation matrix 
	void fixRotationMatrix();

	// Fix direction
	void fixDirection();
};


#pragma once
#include <stdlib.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera3D
{
	glm::quat x, y, z;
	// Current location of the camera
	glm::vec3 loc;
	// Current orientation of the camera
	glm::quat orientation;
	// Inverse Rotation matrix
	glm::mat4 invRotMatrix;
	glm::mat4 rotMatrix;
	glm::mat4 invYRotMatrix;

public:
	Camera3D();
	Camera3D(glm::vec3 location);

	// Reset camera to default rotation and origin
	void reset();

	// Get location of camera
	glm::vec3 getLoc();
	// Set location
	void setLoc(glm::vec3 location);

	// Rotate the camera localy 
	void rotate(float angle, glm::vec3 axis);

	// Move camera relative to rotation
	void move(float dist, glm::vec4 axis);
	// Move camera relative to world space 
	void moveWS(float dist, glm::vec4 axis);

	// Get target of camera
	glm::vec3 getTarget();

	// Get view matrix of camera 
	glm::mat4 getViewMatrix();

	// Center to camera dirction to the horizon
	void centerToHorizon();

private:
	// Fix rotation matrix 
	void fixRotationMatrix();
};


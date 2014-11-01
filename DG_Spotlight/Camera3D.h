#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera3D
{
	// Current location of the camera
	glm::vec3 loc;
	// Current orientation of the camera
	glm::quat orientation;
	// Inverse Rotation matrix
	glm::mat4 invRotMatrix;
	glm::mat4 rotMatrix;

public:
	Camera3D();
	Camera3D(glm::vec3 location);

	// Reset camera to default rotation and origin
	void reset();

	// Get location of camera
	glm::vec3 getLoc();
	// Set location
	void setLoc(glm::vec3 location);

	// Rotate the camera
	void rotate(float angle, glm::vec3 axis);

	// Move camera forward by value
	void moveForwardBy(float value);
	// Move camera backward by value
	void moveBackBy(float value);
	// Move camera up by value
	void moveUpBy(float value);
	// Move camera down by value
	void moveDownBy(float value);
	// Move camera left / right
	void moveSide(float value);

	// Get target of camera
	glm::vec3 getTarget();

	// Get view matrix of camera 
	glm::mat4 getViewMatrix();

private:
	// Fix rotation matrix 
	void fixRotationMatrix();
};


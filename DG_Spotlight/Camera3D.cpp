#include "Camera3D.h"

Camera3D::Camera3D(){
	fixRotationMatrix();
}
Camera3D::Camera3D(glm::vec3 location){
	loc = location;
	fixRotationMatrix();
}

// Reset camera to default rotation and origin
void Camera3D::reset(){
	orientation = glm::quat();
	loc = glm::vec3();
	fixRotationMatrix();
}

// Get location of camera
glm::vec3 Camera3D::getLoc(){ return loc;}
// Set location
void Camera3D::setLoc(glm::vec3 location){loc = location;}

// Rotate the camera
void Camera3D::rotate(float angle, glm::vec3 axis){
	//glm::vec3 nAxis = glm::normalize(glm::vec3(rotMatrix * glm::vec4(axis, 0.0f)));
	glm::quat rot = glm::angleAxis(angle, axis);
	orientation = glm::cross(orientation, rot);
	//orientation = orientation * rot;
	fixRotationMatrix();
}

// Move camera forward by value
void Camera3D::moveForwardBy(float value){
	loc = loc + glm::vec3(invRotMatrix * glm::vec4(0, 0, value, 0));
}
// Move camera backward by value
void Camera3D::moveBackBy(float value){
	loc = loc + glm::vec3(invRotMatrix * glm::vec4(0, 0, -value, 0));
}
// Move camera up by value
void Camera3D::moveUpBy(float value){
	loc = loc + glm::vec3(invRotMatrix * glm::vec4(0, value, 0, 0));
}
// Move camera down by value
void Camera3D::moveDownBy(float value){
	loc = loc + glm::vec3(invRotMatrix * glm::vec4(0, -value, 0, 0));
}
// Move camera left / right
void Camera3D::moveSide(float value){
	loc = loc + glm::vec3(invRotMatrix * glm::vec4(value, 0, 0, 0));
}

// Get target of camera
glm::vec3 Camera3D::getTarget(){
	//return loc + glm::vec3(rotationMatrix * glm::vec4(0, 0, 1, 0));
	return glm::vec3(invRotMatrix * glm::vec4(0, 0, -1, 0));
}

// Get view matrix of camera 
glm::mat4 Camera3D::getViewMatrix(){
	/*return glm::lookAt(
			loc,			   // Camera location
			getTarget(),	   // Target look at location 
			glm::vec3(0, 1, 0) // Camera up
		);*/

	glm::mat4 view = glm::mat4_cast(glm::conjugate(orientation));
	view = glm::translate(view, -loc);
	return view;
}

// Fix rotation matrix 
void Camera3D::fixRotationMatrix(){
	rotMatrix = glm::mat4_cast(glm::conjugate(orientation));
	invRotMatrix = glm::inverse(rotMatrix);
}
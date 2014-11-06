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

// Rotate the camera localy 
void Camera3D::rotate(float angle, glm::vec3 axis){
	glm::quat rot = glm::angleAxis(angle, axis);
	orientation = orientation * rot;
	fixRotationMatrix();
}

// Move camera relative to rotation
void Camera3D::move(float dist, glm::vec4 axis){
	loc = loc + glm::vec3(invRotMatrix * (axis * dist));
}
// Move camera relative to world space 
void Camera3D::moveWS(float dist, glm::vec4 axis){
	loc = loc + glm::vec3(invYRotMatrix * (dist * axis));
}

// Get target of camera
glm::vec3 Camera3D::getTarget(){
	return glm::vec3(invRotMatrix * glm::vec4(0, 0, -1, 0));
}

// Get view matrix of camera 
glm::mat4 Camera3D::getViewMatrix(){
	glm::mat4 view = glm::mat4_cast(glm::conjugate(orientation));
	view = glm::translate(view, -loc);
	return view;
}

// Center to camera dirction to the horizon
void Camera3D::centerToHorizon(){
	// TODO 
	fixRotationMatrix();
}

// Fix rotation matrix 
void Camera3D::fixRotationMatrix(){
	// Make inverse matrix 
	rotMatrix = glm::mat4_cast(glm::conjugate(orientation));
	invRotMatrix = glm::inverse(rotMatrix);

	// Make inverse matrix for just y 
	// TODO 
	invYRotMatrix = glm::inverse(rotMatrix);
}
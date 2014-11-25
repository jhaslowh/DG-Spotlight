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
	// Twice for accuracy 
	rotate(-getDegreesToX(), glm::vec3(1.0, 0.0, 0.0));
	fixRotationMatrix();
	rotate(-getDegreesToZ(), glm::vec3(0.0, 0.0, 1.0));
	fixRotationMatrix();
}
 
// Get the axis and angle for this camera 
// Angle is in radians 
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/
void Camera3D::getAxisAngle(float* angle, glm::vec3* axis){
	// if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
	if (orientation.w > 1.0f)
		orientation = glm::normalize(orientation);
	*angle = 2.0f * acos(orientation.w);
	// assuming quaternion normalised then w is less than 1, so term always positive.
	double s = sqrt(1.0f - orientation.w * orientation.w); 
	// test to avoid divide by zero, s is always positive due to sqrt
	if (s < 0.00001) { 
		// if s close to zero then direction of axis not important
		(*axis)[0] = orientation.x;
		(*axis)[1] = orientation.y;
		(*axis)[2] = orientation.z;
	}
	else {
		(*axis)[0] = orientation.x / s; // normalise axis
		(*axis)[1] = orientation.y / s;
		(*axis)[2] = orientation.z / s;
	}
	// Normalise final axis  
	if (glm::length(*axis) > 0.0f)
		*axis = glm::normalize(*axis);
}

// Returns degrees to x-axis
float Camera3D::getDegreesToX(){
	glm::vec3 tar = glm::vec3(invRotMatrix * glm::vec4(0, 0, -1, 0));
	float dist = sqrt((tar[0] * tar[0]) + (tar[2] * tar[2]));
	return atan2(tar[1], dist) * (180.0f / 3.1415f);
}

// Returns degrees to z-axis
float Camera3D::getDegreesToZ(){
	glm::vec3 tar = glm::vec3(invRotMatrix * glm::vec4(1, 0, 0, 0));
	float dist = sqrt((tar[0] * tar[0]) + (tar[2] * tar[2]));
	return atan2(tar[1], dist) * (180.0f / 3.1415f);
}

// Fix rotation matrix 
void Camera3D::fixRotationMatrix(){
	// Make inverse matrix 
	rotMatrix = glm::mat4_cast(glm::conjugate(orientation));
	invRotMatrix = glm::inverse(rotMatrix);
}
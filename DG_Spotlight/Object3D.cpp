#include "Object3D.h"


Object3D::Object3D()
{
	pos_x = pos_y = pos_z = 0.0f;
	rot_x = rot_y = rot_z = 0.0f;
	scale = 1.0f;
	origin_x = 0.0f;
	origin_y = 0.0f;
}

Object3D::~Object3D()
{

}

// Set the position of the object 
void Object3D::setPosition(float x, float y, float z){
	pos_x = x; pos_y = y; pos_z = z;
}

// Set the rotation of the cube on the x axis  
void Object3D::setRotationX(float degrees){
	rot_x = degrees;
}
float Object3D::getRotationX(){ return rot_x; };

// Set the rotation of the cube on the z axis  
void Object3D::setRotationY(float degrees){
	rot_y = degrees;
}
float Object3D::getRotationY(){ return rot_y; };

// Set the rotation of the cube on the z axis  
void Object3D::setRotationZ(float degrees){
	rot_z = degrees;
}
float Object3D::getRotationZ(){ return rot_z; };

// Set the scale of the cube
void Object3D::setScale(float value){
	scale = value;
}

// Set the origin of the cube 
void Object3D::setOrigin(float x, float y){
	origin_x = x;
	origin_y = y;
}
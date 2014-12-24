#pragma once

/// Author: Jonathan Haslow-Hall
/// Basic 3D object class. 
class Object3D
{
protected:
	// 3D Position and orientation information 
	float pos_x, pos_y, pos_z;
	float rot_x, rot_y, rot_z;
	float scale;
	float origin_x;
	float origin_y;

public:
	Object3D();
	virtual ~Object3D();

	//// Getters and setters 

	// Set the position of the cube 
	void setPosition(float, float, float);
	// Set the rotation of the cube on the x axis  
	void setRotationX(float);
	float getRotationX();
	// Set the rotation of the cube on the y axis  
	void setRotationY(float);
	float getRotationY();
	// Set the rotation of the cube on the z axis  
	void setRotationZ(float);
	float getRotationZ();
	// Set the scale of the cube
	void setScale(float);
	// Set the origin of the cube 
	void setOrigin(float, float);
};


#pragma once
#include <stdlib.h>
#include <glew.h>

#include "GLHandler.h"

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

	// Material 
	GLint textureID;
	GLfloat color[4];

	// Object Arrays
	GLuint index_count;
	GLushort* indicies;
	GLfloat* verts;
	GLfloat* cords;
	GLfloat* norms;

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

	// Setup the cubes texture 
	void setTexture(GLint id);

	// Set the RGB color 
	void setColor(const float, const float, const float);
	// Set the RGBA color
	void setColor(const float, const float, const float, const float);
	// Set the alpha value 
	void setAlpha(const float);

	//// Functions

	// Resize arrays
	void resizeIndicies(unsigned int size);
	void resizeVerts(unsigned int size);
	void resizeCords(unsigned int size);
	void resizeNorms(unsigned int size);
	// Set values in arrays 
	void setIndice(unsigned int index, GLushort value);
	void setVertex(unsigned int index, GLfloat value);
	void setCord(unsigned int index, GLfloat value);
	void setNorm(unsigned int index, GLfloat value);

	// Draw object to the scene 
	virtual void draw(GLHandler* mgl);
};


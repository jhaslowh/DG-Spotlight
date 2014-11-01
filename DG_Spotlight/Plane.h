#pragma once
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "FileHelper.h"
#include "GLHandler.h"

class Plane
{
	// Drawing variables 
	GLushort indicies[6];
	GLfloat verts[12];
	GLfloat cords[8];
	GLfloat norms[12];
	GLint textureID;
	float pos_x, pos_y, pos_z;
	float rot_x, rot_y, rot_z;
	float scale;
	float origin_x;
	float origin_y;
	GLfloat color[4];

public:
	Plane();
	~Plane();

	// Setup the cubes texture 
	void setTexture(std::string);

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
	// Set the RGB color 
	void setColor(const float, const float, const float);
	// Set the RGBA color
	void setColor(const float, const float, const float, const float);
	// Set the alpha value 
	void setAlpha(const float);

	// Call to draw the cube
	void draw(GLHandler);
};


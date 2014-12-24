#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "FileHelper.h"
#include "GLHandler.h"
#include "Object3D.h"

class Cube : public Object3D
{
public:
	Cube();
	virtual ~Cube();

	// Set texture for the cube 
	void setTexture(std::string file);
};


#pragma once
#include <glew.h>
#include <SOIL/SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "SDL/SDL_rwops.h"
#include "Object3D.h"

using namespace std;

// Load a texture into opengl 
int loadPNG(string file);

// Load a obj file into an Object3D
// Basic OBJ loader
// Not all features are supported 
void loadOBJ(string file, Object3D* obj);

// Convert string to double 
double toDouble(string s);

// Convert string to int 
int toInt(string s);

// String split 
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
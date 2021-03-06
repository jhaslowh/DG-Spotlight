#pragma once
/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "IOHelper.h"

class GLHandler
{
public:
	// Shader handles 
	GLuint vs, fs;
	GLuint program;
	GLint mPositionHandle;			// Position
	GLint mTextCordHandle;			// Texture UV's
	GLint mProjMatrixHandle;		// Projection Matrix
	GLint mModelMatrixHandle;		// Model Matrix 
	GLint mViewMatrixHandle;		// View Matrix 
	GLint mNormalMatrixHandle;		// Normal Matrix 
	GLint mNormalHandler;			// Normal 
	GLint mCameraPosHandler;		// Camera position 

	GLint mLightPosHandle;			// Light Position
	GLint mTextureHandle;			// Texture
	GLint mUseTexture;
	GLint mSpotLightDirection;
	GLint mSlotLightCosCutoff;
	GLint mSlotLightCosCutoffInner;
	GLint mSpecular;
	GLint mDiffuse;
	GLint mAmbient;
	GLint mShininess;
	GLint mSLColor;	
	GLint mLightCount;

	// Matrix's
	glm::mat4 orthoMatrix;
	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;

private:
	// Sent matrix's
	glm::mat4 sentProjMatrix;
	glm::mat4 sentViewMatrix;
	glm::mat4 sentModelMatrix;

public:
	// Functions
	GLHandler();
	~GLHandler(void);

	// Call to load 
	int load();

	// Grab uniform handle 
	void grabHandleUni(int& handle, const GLchar* name);
	// Grab attribute handle 
	void grabHandleAtt(int& handle, const GLchar* name);

	// Delete MGL shader 
	void deleteShader();

	// Call to set up gl for rendering
	void setupGL();

	// Call when done rendering 
	void endGL();
	
	// Set the Projection matrix for the shader. 
	// This is used to map the game to the screen, 
	// so use an orthographic matrix or a projection 
	// matrix.
	// use glm::mat4() for identity 
	void setProjectionMatrix(glm::mat4);
	
	// Set the View matrix for the shader. 
	// This is used as the camera for the game. 
	// use glm::mat4() for identity 
	void setViewMatrix(glm::mat4);

	// Set the model matrix for the shader. 
	// use glm::mat4() for identity 
	void setModelMatrix(glm::mat4);
	
	// Fix the normal matrix
	// This is based off of send matrix's 
	void fixNormalMatrix();

	// Call to fix the ortho matrix if screen size has changed 
	void makeOrthoMatrix(const float width,const float height);
	// Call to fix the proj matrix if the screen size has changed 
	void makeProjMatrix(const float fov, const float aspectRatio, const float near, const float far);
	// Set the view matrix 
	// Camera location  : glm::vec(0,0,0)
	// Target           : glm::vec(0,0,0)
	void makeViewCamera(const glm::vec3 cameraLocation, const glm::vec3 targetLocation);

	// Bind vertex and cord buffers
	void bindBuffers(GLfloat* verts, GLfloat* cords);
	// Bind normal buffer
	void bindNormals(GLfloat* norm);
	// Bind texture 
	void bindTexture(int id);

	// Will check for and print out opengl error
	void checkForGLError();
	// Print out GLSL shader error 
	void printGLSLError(GLint shader);
};
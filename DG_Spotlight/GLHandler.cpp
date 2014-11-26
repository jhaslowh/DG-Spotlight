#include "GLHandler.h"

GLHandler::GLHandler(){
	program = 0;
}
GLHandler::~GLHandler(){
	//std::cout << "TODO We should not see this\n";
}

/**
* Setup the shaders used for rendering 
*/
int GLHandler::load(){

	deleteShader();

	// ---------------
	// Compile shaders
	// ---------------

	// Make the opengl shaders 
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
 
	// Vertex shader 
	vs = glCreateShader(GL_VERTEX_SHADER);
	if (vs == 0){
		std::cout << "ERROR: Creating vertex shader int\n";
		return 0;
	}
	std::string mfile = readFile("shader_vertex.cpp");
	const char* buff = mfile.c_str();
	glShaderSource(vs, 1, &buff, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (0 == compile_ok){
		fprintf(stderr, "Error in vertex shader\n");
		glDeleteShader(vs);
		return 0;
	}

	// Fragment shader 
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	if (fs == 0){
		std::cout << "ERROR: Creating fragment shader int\n";
		return 0;
	}
	mfile = readFile("shader_fragment.cpp");
	const char* buff2 = mfile.c_str();
	glShaderSource(fs, 1, &buff2, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		fprintf(stderr, "Error in fragment shader\n");
		glDeleteShader(vs);
		glDeleteShader(fs);
		return 0;
	}

	// Make shader program
	program = glCreateProgram();
	std::cout << "Shader program: " << program << "\n";
	// Give the vertex shader to our shader program
	glAttachShader(program, vs);
	// Give the fragment shader to out shader program 
	glAttachShader(program, fs);
	// Similar to the linker for a compiler. 
	// Initializes all values to 0 and defines 
	// a location for each uniform and attrubute. 
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		deleteShader();
		return 0;
	}

	// ----------------------
	// Grab shader attributes/uniforms 
	// ----------------------

	// get handle to shape's transformation matrix
	grabHandleUni(mModelMatrixHandle, "modelm");
	grabHandleUni(mProjMatrixHandle, "projm");
	grabHandleUni(mViewMatrixHandle, "viewm");
	grabHandleUni(mNormalMatrixHandle, "normm");
	// get handle to vertex shader's vPosition member
	grabHandleAtt(mPositionHandle, "position");
	grabHandleAtt(mNormalHandler, "aNormal");
	// Grab texture information
	grabHandleUni(mTextureHandle, "texture");
	grabHandleAtt(mTextCordHandle, "aTexCoordinate");
	grabHandleUni(mUseTexture, "useTexture");
	// Lighting 
	grabHandleUni(mLightPosHandle, "lightPos");
	grabHandleUni(mSpotLightDirection, "slDirection");
	grabHandleUni(mSlotLightCosCutoff, "slCosCutoff");
	grabHandleUni(mSlotLightCosCutoffInner, "slCosCutoffInner");

	grabHandleUni(mAmbient, "global_ambient");
	grabHandleUni(mSpecular, "m_specular");
	grabHandleUni(mDiffuse, "m_diffuse");
	grabHandleUni(mShininess, "m_shininess");
	grabHandleUni(mCameraPosHandler, "cam");
	grabHandleUni(mSLColor, "slColor");
	grabHandleUni(mLightCount, "lightCount");

	return 1;
}

// Grab uniform handle 
void GLHandler::grabHandleUni(int& handle, const GLchar* name){
	handle = glGetUniformLocation(program, name);
	if (handle == -1)
		std::cout << "Error grabbing " << name << " location\n";
}
// Grab attribute handle 
void GLHandler::grabHandleAtt(int& handle, const GLchar* name){
	handle = glGetAttribLocation(program, name);
	if (handle == -1)
		std::cout << "Error grabbing " << name << " location\n";
}

// Delete MGL shader 
void GLHandler::deleteShader(){
	if (program != 0){
		glUseProgram(0);
		glDetachShader(program, vs);
		glDeleteShader(vs);
		glDetachShader(program, fs);
		glDeleteShader(fs);
		glDeleteProgram(program);
		program = 0;
	}
}

// Setup gl calls for drawing 
void GLHandler::setupGL(){
	// Set the cull face 
	glEnable(GL_CULL_FACE);
	// Set which cull face to use 
	glCullFace(GL_BACK);

	// Setup alpha blending 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

// Disable all setup 
void GLHandler::endGL(){
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

// Set the Projection matrix for the shader. 
// use glm::mat4() for identity 
void GLHandler::setProjectionMatrix(glm::mat4 matrix){
	sentProjMatrix = matrix;
	glUniformMatrix4fv(mProjMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set the camera matrix for the shader 
void GLHandler::setViewMatrix(glm::mat4 matrix){
	sentViewMatrix = matrix;
	glUniformMatrix4fv(mViewMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set the model matrix for the shader 
void GLHandler::setModelMatrix(glm::mat4 matrix){
	sentModelMatrix = matrix;
	glUniformMatrix4fv(mModelMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

// Fix the normal matrix
// This is based off of send matrix's 
void GLHandler::fixNormalMatrix(){
	glm::mat3 normalMatrix(sentModelMatrix);
	normalMatrix = glm::inverseTranspose(normalMatrix);
	glUniformMatrix3fv(mNormalMatrixHandle, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

// Call to fix the ortho matrix if screen size has changed 
void GLHandler::makeOrthoMatrix(const float w,const float h){
	// left, width, height, top
	orthoMatrix = glm::ortho( 0.0f, w, h, 0.0f, 1.0f, -1.0f);
}

// Call to fix the proj matrix if the screen size has changed 
void GLHandler::makeProjMatrix(const float fov, const float aspectRatio, const float near, const float far){
	projMatrix = glm::perspective(fov, aspectRatio, near, far);
}
// Set the view matrix 
// Camera location  : glm::vec(0,0,0)
// Target           : glm::vec(0,0,0)
void GLHandler::makeViewCamera(const glm::vec3 cameraLocation, const glm::vec3 targetLocation){
	viewMatrix = glm::lookAt(
		cameraLocation,   // Camera location
		targetLocation,   // Target look at location 
		glm::vec3(0, 1, 0)  // Camera up
	);
}


// Bind vertex and cord buffers
void GLHandler::bindBuffers(GLfloat* verts, GLfloat* cords){
	/// Set up vertex and coord buffers 
	glEnableVertexAttribArray(mPositionHandle);
	glVertexAttribPointer(mPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, verts );

	/// Bind texture
	glEnableVertexAttribArray(mTextCordHandle);
	glVertexAttribPointer(mTextCordHandle, 2,GL_FLOAT, GL_FALSE, 0, cords);
}
// Bind normal buffer
void GLHandler::bindNormals(GLfloat* norm){
	/// Set up vertex and coord buffers 
	glEnableVertexAttribArray(mNormalHandler);
	glVertexAttribPointer(mNormalHandler, 3, GL_FLOAT, GL_FALSE, 0, norm);
}
// Bind texture 
void GLHandler::bindTexture(int id){
	// Set the active texture unit to texture unit 0.
	glActiveTexture(GL_TEXTURE0);
	// Bind the texture to this unit.
	glBindTexture(GL_TEXTURE_2D, id);
	// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
	glUniform1i(mTextureHandle, 0);
}

// Will check for and print out opengl error
void GLHandler::checkForGLError(){
	GLenum glErr = glGetError();
	while (glErr != GL_NO_ERROR){
		switch (glErr){
		case GL_INVALID_ENUM:
			std::cout << "ERROR (GL_INVALID_ENUM): An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.\n";
		case GL_INVALID_VALUE:
			std::cout << "ERROR (GL_INVALID_VALUE): A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.\n";
		case GL_INVALID_OPERATION:
			std::cout << "ERROR (GL_INVALID_OPERATION): The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.\n";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "ERROR (GL_INVALID_FRAMEBUFFER_OPERATION): The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.\n";
		case GL_OUT_OF_MEMORY:
			std::cout << "ERROR (GL_OUT_OF_MEMORY): There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.\n";
		case GL_STACK_UNDERFLOW:
			std::cout << "ERROR (GL_STACK_UNDERFLOW): An attempt has been made to perform an operation that would cause an internal stack to underflow.\n";
		case GL_STACK_OVERFLOW:
			std::cout << "ERROR (GL_STACK_OVERFLOW): An attempt has been made to perform an operation that would cause an internal stack to overflow.\n";
		default:
			std::cout << "ERROR: Error not recognized\n";
		}
		glErr = glGetError();
	}
}



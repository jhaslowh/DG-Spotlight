#include "Object3D.h"


Object3D::Object3D()
{
	pos_x = pos_y = pos_z = 0.0f;
	rot_x = rot_y = rot_z = 0.0f;
	scale = 1.0f;
	origin_x = 0.0f;
	origin_y = 0.0f;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	textureID = -1;
	index_count = 0;

	indicies = NULL;
	verts = NULL;
	cords = NULL;
	norms = NULL;
}

Object3D::~Object3D()
{
	delete[] indicies;
	delete[] verts;
	delete[] cords;
	delete[] norms;

	indicies = NULL;
	verts = NULL;
	cords = NULL;
	norms = NULL;
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

// Setup the cubes texture 
void Object3D::setTexture(GLint id){
	textureID = id;
}

// Set the RGB color 
void Object3D::setColor(const float r, const float g, const float b){
	color[0] = r; color[1] = g; color[2] = b;
}

// Set the RGBA color
void Object3D::setColor(const float r, const float g, const float b, const float a){
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

// Set the alpha value 
void Object3D::setAlpha(const float a){
	color[3] = a;
}


// Resize arrays
void Object3D::resizeIndicies(unsigned int size){
	index_count = size;
	delete[] indicies;
	indicies = new GLushort[size];
}
void Object3D::resizeVerts(unsigned int size){
	delete[] verts;
	verts = new GLfloat[size];
}
void Object3D::resizeCords(unsigned int size){
	delete[] cords;
	cords = new GLfloat[size];
}
void Object3D::resizeNorms(unsigned int size){
	delete[] norms;
	norms = new GLfloat[size];
}
// Set values in arrays 
void Object3D::setIndice(unsigned int index, GLushort value){
	indicies[index] = value;
}
void Object3D::setVertex(unsigned int index, GLfloat value){
	verts[index] = value;
}
void Object3D::setCord(unsigned int index, GLfloat value){
	cords[index] = value;
}
void Object3D::setNorm(unsigned int index, GLfloat value){
	norms[index] = value;
}


// Draw object to the scene 
void Object3D::draw(GLHandler* mgl){
	/// Matrix transform ///
	// Starting matrix 
	glm::mat4 mMatrix;
	// Translate 
	mMatrix = glm::translate(mMatrix, glm::vec3(pos_x, pos_y, pos_z));
	// Rotation
	mMatrix = glm::rotate(mMatrix, rot_x, glm::vec3(1.0f, 0.0f, 0.0f));
	mMatrix = glm::rotate(mMatrix, rot_y, glm::vec3(0.0f, 1.0f, 0.0f));
	mMatrix = glm::rotate(mMatrix, rot_z, glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale 
	mMatrix = glm::scale(mMatrix, glm::vec3(scale));
	// Origin
	mMatrix = glm::translate(mMatrix, glm::vec3(-origin_x, -origin_y, 0.0f));
	// Send the rotation matrix to the shader 
	mgl->setModelMatrix(mMatrix);

	// Fix normal matrix 
	mgl->fixNormalMatrix();

	/// Set material Properties 
	glUniform4fv(mgl->mDiffuse, 1, color);

	// Set up vertex and coord buffers 
	if (verts != NULL){
		glEnableVertexAttribArray(mgl->mPositionHandle);
		// Describe our vertices array to OpenGL 
		glVertexAttribPointer(
			mgl->mPositionHandle, // attribute
			3,                 // number of elements per vertex, here (x,y,z)
			GL_FLOAT,          // the type of each element
			GL_FALSE,          // take our values as-is
			0,                 // no extra data between each position
			verts  // pointer to the C array
			);
	}
	else std::cout << "ERROR: Trying to render object3d with no vertex data\n";
	// Send normals to shader 
	if (norms != NULL){
		glEnableVertexAttribArray(mgl->mNormalHandler);
		glVertexAttribPointer(mgl->mNormalHandler, 3, GL_FLOAT, GL_FALSE, 0, norms);
	}

	if (textureID != -1 && cords != NULL){
		glUniform1i(mgl->mUseTexture, 1);
		// Bind textures 
		glEnableVertexAttribArray(mgl->mTextCordHandle);
		glVertexAttribPointer(
			mgl->mTextCordHandle,
			2,                 // number of elements per coord, here (x,y)
			GL_FLOAT,          // the type of each element
			GL_FALSE,          // take our values as-is
			0,                 // no extra data between each position
			cords			  // pointer to the C array
			);

		/** Bind Texture **/
		//mgl.toggleTextures(true);
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl->mTextureHandle, 0);
	}
	else
		glUniform1i(mgl->mUseTexture, 0);

	// Draw the sent indicies 
	if (indicies != NULL)
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_SHORT, indicies);
	else std::cout << "ERROR: Trying to render object with no indicies\n";

	// Disable vertexes 
	glDisableVertexAttribArray(mgl->mPositionHandle);
	glDisableVertexAttribArray(mgl->mTextCordHandle);
	glDisableVertexAttribArray(mgl->mNormalHandler);
}
#include "Plane.h"

Plane::Plane()
{
	pos_x = 0.0f;
	pos_y = 0.0f;
	pos_z = 0.0f;
	rot_x = 0.0f;
	rot_y = 0.0f;
	rot_z = 0.0f;
	scale = 1.0f;
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;
	origin_x = 0;
	origin_y = 0;
	textureID = -1;

	// Vertexes  
	verts[0] = -0.5f; verts[1] = 0.0f; verts[2] = -0.5f;  // Vertex 1
	verts[3] = -0.5f; verts[4] = 0.0f; verts[5] = 0.5f;  // Vertex 2
	verts[6] = 0.5f;  verts[7] = 0.0f; verts[8] = 0.5f;  // Vertex 3
	verts[9] = 0.5f;  verts[10] = 0.0f; verts[11] = -0.5f; // Vertex 4

	// Indicies
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 2;
	indicies[4] = 3;
	indicies[5] = 0;

	// Normals 
	// Front Face 
	for (int i = 0; i < 12; i += 3){
		norms[i] = 0.0f;
		norms[i + 1] = 1.0f;
		norms[i + 2] = 0.0f;
	}
}
Plane::~Plane(){}

// Setup the cubes texture 
void Plane::setTexture(std::string file){
	textureID = loadPNG(file);

	cords[0] = 0.0f; cords[1] = 0.0f;
	cords[2] = 0.0f; cords[3] = 1.0f;
	cords[4] = 1.0f; cords[5] = 1.0f;
	cords[6] = 1.0f; cords[7] = 0.0f;
}

// Set the position of the cube 
void Plane::setPosition(float x, float y, float z){
	pos_x = x; pos_y = y; pos_z = z;
}

// Set the rotation of the cube on the x axis  
void Plane::setRotationX(float degrees){
	rot_x = degrees;
}
float Plane::getRotationX(){ return rot_x; };

// Set the rotation of the cube on the z axis  
void Plane::setRotationY(float degrees){
	rot_y = degrees;
}
float Plane::getRotationY(){ return rot_y; };

// Set the rotation of the cube on the z axis  
void Plane::setRotationZ(float degrees){
	rot_z = degrees;
}
float Plane::getRotationZ(){ return rot_z; };

// Set the scale of the cube
void Plane::setScale(float value){
	scale = value;
}

// Set the origin of the cube 
void Plane::setOrigin(float x, float y){
	origin_x = x;
	origin_y = y;
}

// Set the RGB color 
void Plane::setColor(const float r, const float g, const float b){
	color[0] = r; color[1] = g; color[2] = b;
}

// Set the RGBA color
void Plane::setColor(const float r, const float g, const float b, const float a){
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

// Set the alpha value 
void Plane::setAlpha(const float a){
	color[3] = a;
}

// Call to draw the cube
void Plane::draw(GLHandler mgl){
	/// Matrix transform
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
	mgl.setModelMatrix(mMatrix);

	// Fix normal matrix 
	mgl.fixNormalMatrix();

	// Set diffuse color 
	glUniform4fv(mgl.mDiffuse, 1, color);

	/// Set up vertex and coord buffer
	glEnableVertexAttribArray(mgl.mPositionHandle);
	// Describe our vertices array to OpenGL 
	glVertexAttribPointer(
		mgl.mPositionHandle, // attribute
		3,                 // number of elements per vertex, here (x,y,z)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		verts  // pointer to the C array
		);
	// Send normals to shader 
	glEnableVertexAttribArray(mgl.mNormalHandler);
	glVertexAttribPointer(mgl.mNormalHandler, 3, GL_FLOAT, GL_FALSE, 0, norms);

	if (textureID != -1){
		glUniform1i(mgl.mUseTexture, 1);
		// Bind textures 
		glEnableVertexAttribArray(mgl.mTextCordHandle);
		glVertexAttribPointer(
			mgl.mTextCordHandle,
			2,                 // number of elements per coord, here (x,y)
			GL_FLOAT,          // the type of each element
			GL_FALSE,          // take our values as-is
			0,                 // no extra data between each position
			cords			  // pointer to the C array
			);

		/// Bind Texture
		// Set the active texture unit to texture unit 0.
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture to this unit.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
		glUniform1i(mgl.mTextureHandle, 0);
	}
	else
		glUniform1i(mgl.mUseTexture, 0);

	// Draw the sent indicies 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indicies);

	// Disable vertexes 
	glDisableVertexAttribArray(mgl.mPositionHandle);
	glDisableVertexAttribArray(mgl.mTextCordHandle);
	glDisableVertexAttribArray(mgl.mNormalHandler);
}
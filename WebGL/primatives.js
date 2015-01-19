
// Cube structure 
function Cube(){
  this.x = 0;
  this.y = 0;
  this.z = 0;
  this.rotation = [0,0,0];
  this.diffuse = [1.0,1.0,1.0,1.0];
  this.scale = 1.0;
}

// Set cubes location 
Cube.prototype.location = function(x,y,z){
  this.x = x;
  this.y = y;
  this.z = z;
}

Cube.prototype.setScale = function(s){this.scale = s;}
Cube.prototype.setColor = function(r,g,b,a){
  this.diffuse[0]=r;
  this.diffuse[1]=g;
  this.diffuse[2]=b;
  this.diffuse[3]=a;
}

// Initialize cube 
Cube.prototype.init = function(gl){
  // Make vertex array 
  this.vertBuff = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, this.vertBuff);
  var vertices = [
  // Front Face
    -0.5,  0.5, 0.5,
    -0.5, -0.5, 0.5,
     0.5, -0.5, 0.5,
     0.5,  0.5, 0.5,
  // Back Face
     0.5,  0.5, -0.5,
     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,
  // Top Face
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,
     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,
  // Bottom Face
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5, -0.5,  0.5,
  // Left Face
     0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
  // Right Face
    -0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,
  ];
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  // Make normal buffer 
  this.normBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, this.normBuffer);
  var norms = [
  // Front face 
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
  // Back face 
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
  // Top face 
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
  // Bottom face 
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
  // Left face 
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
  // Right face 
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
  ];
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(norms), gl.STATIC_DRAW);

  this.indiceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indiceBuffer);
  var indicies = [
    0,1,2,2,3,0,
    4,5,6,6,7,4,
    8,9,10,10,11,8,
    12,13,14,14,15,12,
    16,17,18,18,19,16,
    20,21,22,22,23,20
  ];
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indicies), gl.STATIC_DRAW);
}

// Draw cube 
Cube.prototype.draw = function(gl){
  mat4.identity(mMatrix);
  mat4.translate(mMatrix,mMatrix, [this.x, this.y, this.z]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[0], [1.0,0.0,0.0]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[1], [0.0,1.0,0.0]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[2], [0.0,0.0,1.0]);
  mat4.scale(mMatrix,mMatrix, [this.scale,this.scale,this.scale]);
  //mat4.translate(mMatrix,mMatrix, [0.0, 0.0, 0.0]); // Origin
  gl.uniformMatrix4fv(shaderProgram.mModelMatrixHandle, false, mMatrix);

  // Normal matrix 
  mat3.normalFromMat4(nMatrix, mMatrix);
  gl.uniformMatrix3fv(shaderProgram.mNormalMatrixHandle, false, nMatrix);

  // Color 
  gl.uniform4f(shaderProgram.mDiffuse, this.diffuse[0],this.diffuse[1],this.diffuse[2],this.diffuse[3]);

  gl.enableVertexAttribArray(shaderProgram.mPositionHandle);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.vertBuff);
  gl.vertexAttribPointer(shaderProgram.mPositionHandle, 3, gl.FLOAT, false, 0, 0);

  gl.enableVertexAttribArray(shaderProgram.mNormalHandler);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.normBuffer);
  gl.vertexAttribPointer(shaderProgram.mNormalHandler, 3, gl.FLOAT, false, 0, 0);

  gl.uniform1i(shaderProgram.mUseTexture, 0);

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indiceBuffer);
  gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_SHORT, 0);
}

// ---------------------------------------------------------------

// Plane structure 
function Plane(){
  this.x = 0;
  this.y = 0;
  this.z = 0;
  this.rotation = [0,0,0];
  this.diffuse = [1.0,1.0,1.0,1.0];
  this.scale = 1.0;
}

// Set planes location 
Plane.prototype.location = function(x,y,z){
  this.x = x;
  this.y = y;
  this.z = z;
}

Plane.prototype.setScale = function(s){this.scale = s;}
Cube.prototype.setColor = function(r,g,b,a){
  this.diffuse[0]=r;
  this.diffuse[1]=g;
  this.diffuse[2]=b;
  this.diffuse[3]=a;
}

// Initialize cube 
Plane.prototype.init = function(gl){
  // Make vertex array 
  this.vertBuff = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, this.vertBuff);
  var vertices = [
    -0.5,  0.0,  -0.5,
    -0.5,  0.0,  0.5,
    0.5,  0.0,  0.5,
    0.5,  0.0,  -0.5,
  ];
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  // Make normal buffer 
  this.normBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, this.normBuffer);
  var norms = [
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
  ];
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(norms), gl.STATIC_DRAW);

  this.indiceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indiceBuffer);
  var indicies = [0,1,2,2,3,0];
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indicies), gl.STATIC_DRAW);
}

// Draw plane 
Plane.prototype.draw = function(gl){
  mat4.identity(mMatrix);
  mat4.translate(mMatrix,mMatrix, [this.x, this.y, this.z]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[0], [1.0,0.0,0.0]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[1], [0.0,1.0,0.0]);
  mat4.rotate(mMatrix,mMatrix, this.rotation[2], [0.0,0.0,1.0]);
  mat4.scale(mMatrix,mMatrix, [this.scale,this.scale,this.scale]);
  //mat4.translate(mMatrix,mMatrix, [0.0, 0.0, 0.0]); // Origin
  gl.uniformMatrix4fv(shaderProgram.mModelMatrixHandle, false, mMatrix);

  // Normal matrix 
  mat3.normalFromMat4(nMatrix, mMatrix);
  gl.uniformMatrix3fv(shaderProgram.mNormalMatrixHandle, false, nMatrix);

  // Color 
  gl.uniform4f(shaderProgram.mDiffuse, this.diffuse[0], this.diffuse[1], this.diffuse[2], this.diffuse[3]);

  gl.enableVertexAttribArray(shaderProgram.mPositionHandle);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.vertBuff);
  gl.vertexAttribPointer(shaderProgram.mPositionHandle, 3, gl.FLOAT, false, 0, 0);

  gl.enableVertexAttribArray(shaderProgram.mNormalHandler);
  gl.bindBuffer(gl.ARRAY_BUFFER, this.normBuffer);
  gl.vertexAttribPointer(shaderProgram.mNormalHandler, 3, gl.FLOAT, false, 0, 0);

  gl.uniform1i(shaderProgram.mUseTexture, 0);

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indiceBuffer);
  gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);
}

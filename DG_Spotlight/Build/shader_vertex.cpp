#version 100  
precision highp float;

// Inputs 
in vec4 position;       // Position handle 
in vec3 aNormal;        // Normal handle 
in vec2 aTexCoordinate; // Texture coord handle 
uniform vec3 cam;       // Camera location 

// Matrix's 
uniform mat4 modelm;  // Model Matrix handle
uniform mat4 viewm;   // View Matrix handle
uniform mat4 projm;   // Projection Matrix handle
uniform mat3 normm;   // Normal Matrix handle

// Output to fragment
varying vec2 vTexCoord;  // Texture coord handle that both shaders use 
varying vec3 vNormal;         // Normal to send to texture 
varying vec3 vEye;            // Eye vector
varying vec3 vLightDirec;     // Light direction vector 
varying vec4 vpos;

void main() {       
    // Vertex position in world space 
    vec4 pos = modelm * position;
    vpos = pos;
    
    // Compute normal 
    vNormal = normalize(normm * aNormal);
    // Compute eye value 
    vEye = cam - pos.xyz;
    // Send texture cord 
    vTexCoord = aTexCoordinate; 

    // Set final position 
    gl_Position = projm * viewm * modelm * position;
}

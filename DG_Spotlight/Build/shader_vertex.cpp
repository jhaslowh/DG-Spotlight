//#version 400  

// Inputs 
in vec4 position;       // Position handle 
in vec3 aNormal;        // Normal handle 
in vec2 aTexCoordinate; // Texture coord handle 

// Matrix's 
uniform mat4 modelm;  // Model Matrix handle
uniform mat4 viewm;   // View Matrix handle
uniform mat4 projm;   // Projection Matrix handle
uniform mat3 normm;   // Normal Matrix handle
uniform vec3 cam;     // Camera location 

// Output to fragment
varying vec2 vTexCoordinate;  // Texture coord handle that both shaders use 
varying vec3 vNormal;         // Normal to send to texture 
varying vec3 vEye;            // Eye vector
varying vec3 vLightDirec;     // Light direction vector 

// Lighting 
uniform vec4 lightPos; // Position of spotlight 

void main() {       
    // Vertex position
    vec4 pos = modelm * position;
    
    // Compute normal 
    vNormal = normalize(normm * aNormal);
    // Compute light direction 
    vLightDirec = vec3(lightPos - pos);
    // Compute eye value 
    vEye = pos.xyz - cam;

    // Send texture cord 
    vTexCoordinate = aTexCoordinate; 
    // Set final position 
    gl_Position = projm * viewm * modelm * position;
};

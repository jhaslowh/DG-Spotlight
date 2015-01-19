#version 100
precision highp float;

// Inputs from program 
uniform sampler2D texture;     // Texture handle 
uniform bool useTexture;       // Toggle use of texture

// Input from vertex shader 
varying vec2 vTexCoord;   // Texture coord handle that both shaders use 
varying vec3 vNormal;     // Normal from vertex shader 
varying vec3 vEye;        // Eye vector
varying vec3 vLightDirec; // Light direction vector 
varying vec4 vpos;

// Lighting 
//const int MAX_LIGHTS = 4;
uniform vec4 lightPos[4];          // Position of spotlight 
uniform vec3 slDirection[4];       // Direction of spotlight
uniform float slCosCutoff[4];      // Cutoff for spotlight 
uniform float slCosCutoffInner[4]; // Cutoff for spotlight 
uniform vec4 slColor[4];           // Spotlight color 
uniform int lightCount;         // Count of current lights 

uniform vec4 global_ambient;  // Global ambient light 

// Material properties 
uniform vec4 m_specular;   // Material specular color 
uniform vec4 m_diffuse;    // Material diffuse color 
uniform float m_shininess; // Material shininess 
uniform vec4 m_ambient;    // Material ambient

void main() { 
    float intensity = 0.0;  // Intensity of spotlight on given pixel 
    vec4 mDiffuse;    // Material diffuse 
    vec4 diffuse;     // Will be final diffuse color
    vec4 specular;    // Will be final specular color 

    // Use texture and flat color as diffuse 
    mDiffuse = (useTexture) ? m_diffuse * texture2D(texture, vTexCoord) : m_diffuse;
 
    vec3 N = normalize(vNormal);
    vec3 E = normalize(vEye); // Eye Vector 
 
    /// For each light 
    for (int i = 0; i < lightCount; i++){
        // Normal of computed light direction
        vec3 LD = normalize(vec3(lightPos[i] - vpos));
        // Normal of spotlight direction
        vec3 SD = normalize(-slDirection[i]);  
        // Get value of how far pixel is to center of spotlight area 
        float SdL = dot(SD,LD);
        // Compute light intensity 
        intensity = clamp((slCosCutoff[i] - SdL) / (slCosCutoff[i] - slCosCutoffInner[i]), 0.0, 1.0);
        // Spotlight final color with intensity 
        vec4 lightColor = slColor[i] * intensity;
        // Compute diffuse intensity [diffuse += ]
        diffuse += mDiffuse * lightColor * max(dot(N,LD), 0.0);
        // Compute specular intensity [specular +=]
        vec3 h = normalize(LD + E); // Half Vector 
        specular += m_specular * lightColor * pow(max(dot(h,N), 0.0), m_shininess);
    }
    ///

    // Final color 
    gl_FragColor = diffuse + specular + global_ambient;
}
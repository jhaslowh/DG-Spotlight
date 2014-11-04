//#version 400

// Inputs from program 
uniform sampler2D texture;     // Texture handle 
uniform bool useTexture;       // Toggle use of texture

// Input from vertex shader 
varying vec2 vTexCoord;   // Texture coord handle that both shaders use 
varying vec3 vNormal;     // Normal from vertex shader 
varying vec3 vEye;        // Eye vector
varying vec3 vLightDirec; // Light direction vector 

// Lighting 
uniform vec3 slDirection;       // Direction of spotlight
uniform float slCosCutoff;      // Cutoff for spotlight 
uniform float slCosCutoffInner; // Cutoff for spotlight 

uniform vec4 l_ambient;         // Global ambient light 
// Material properties 
uniform vec4 l_specular;        // Material specular color 
uniform vec4 l_diffuse;         // Material diffuse color 
uniform float l_shininess;      // Material shininess 

void main() { 
    float intensity = 0.0;  // Intensity of spotlight on given pixel 
    vec4 mDiffuse;    // Material diffuse 
    vec4 diffuse;     // Will be final diffuse color
    vec4 specular;    // Will be final specular color 
    float kD, kS;     // Coefficients 

    // Use texture and flat color as diffuse 
    mDiffuse = (useTexture) ? l_diffuse * texture2D(texture, vTexCoord) : l_diffuse;
 
    // Normal of light direction
    vec3 ld = normalize(vLightDirec);
    // Normal of spotlight direction
    vec3 sd = normalize(-slDirection);  
    vec3 n = normalize(vNormal);
    vec3 eye = normalize(vEye);
 
    ///== TODO for each light 

    // Get value of how far pixel is to center of spotlight area 
    float SdL = dot(sd,ld);
    // Compute light intensity 
    intensity = clamp((slCosCutoff - SdL) / (slCosCutoff - slCosCutoffInner), 0.0, 1.0);

    // Compute diffuse intensity [diffuse += ]
    diffuse = mDiffuse * intensity * max(dot(n,ld), 0.0);
    // Compute specular intensity [specular +=]
    vec3 h = normalize(ld + eye);
    specular = l_specular * intensity * pow(max(dot(h,n), 0.0), l_shininess);

    ///== 

    // Final color 
    gl_FragColor = l_ambient + diffuse + specular;
};
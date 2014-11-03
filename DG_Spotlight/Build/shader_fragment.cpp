//#version 400

// Inputs 
uniform sampler2D texture;     // Texture handle 
uniform bool useTexture;       // Toggle use of texture
uniform vec4 color;            // Color handle

// Input from vertex shader 
varying vec2 vTexCoordinate;   // Texture coord handle that both shaders use 
varying vec3 vNormal;          // Normal from vertex shader 
varying vec3 vEye;            // Eye vector
varying vec3 vLightDirec;     // Light direction vector 

// Lighting 
uniform vec3 spotlightDirection; // Direction of spotlight
uniform float spotlightCosCutoff;// Cutoff for spotlight 
uniform float spotlightCosCutoffInner;// Cutoff for spotlight 
uniform vec4 l_specular;
uniform vec4 l_diffuse;
uniform vec4 l_ambient;         // Global ambient light 
uniform float l_shininess;

void main() { 
    // Values to be computed 
    float intensity = 0.0;
    float kD = 0.0;
    float kS = 0.0;
    vec4 spec = vec4(0.0);
 
    // Normal of light direction
    vec3 ld = normalize(vLightDirec);
    // Normal of spotlight direction
    vec3 sd = normalize(-spotlightDirection);  
 
    // Check if pixel is inside spotlight cone 
    float SdL = dot(sd,ld);
    if (SdL > spotlightCosCutoff) {
        // Grab normal
        vec3 n = normalize(vNormal);
        intensity = clamp((spotlightCosCutoff - SdL) / (spotlightCosCutoff - spotlightCosCutoffInner), 0.0, 1.0);
        //gl_FragColor = vec4(intensity, intensity, intensity, 1.0); return;

        if (intensity > 0.0) {
            // Compute diffuse intensity 
            kD = max(dot(n,ld), 0.0) * intensity;

            // Compute specular intensity
            vec3 eye = normalize(vEye);
            vec3 h = normalize(ld + eye);
            float intSpec = max(dot(h,n), 0.0);
            kS = pow(intSpec, l_shininess) * intensity;
        }
    }

    // Set final color 
    vec4 textColor; 
    if (useTexture)
        textColor = color * texture2D(texture, vTexCoordinate);
    else 
        textColor = color;

    gl_FragColor = (kD * l_diffuse * textColor) + (kS * l_specular) + (l_ambient * textColor);
};
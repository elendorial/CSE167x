# version 120 

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Mine is an old machine.  For version 130 or higher, do 
// in vec4 color;  
// in vec3 mynormal; 
// in vec4 myvertex;
// That is certainly more modern

varying vec4 color;
varying vec3 mynormal; 
varying vec4 myvertex; 

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.  These could be varying and/or bound to 
// a buffer.  But for now, I'll just make them uniform.  
// I use ambient, diffuse, specular, shininess as in OpenGL.  
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 


vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

	float nDotL = dot(normal, direction)  ;         
	vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

	float nDotH = dot(normal, halfvec) ; 
	vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

	vec4 retval = lambert + phong ; 
	return retval ;            
} 

void main (void) 
{
  
  vec4 totalLighting = vec4(0, 0, 0, 1);
  vec4 col0;
  vec4 col1;   
  
  
    
    if (enablelighting) {
         
        const vec3 eyepos = vec3(0,0,0) ; 
        vec4 _mypos = gl_ModelViewMatrix * myvertex ; 
        vec3 mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos) ; 

        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ;
        
        for(int index = 0; index < numused; index++)
        {
          if(lightposn[index].w == 0.0) //directional light
          {
            vec3 temp_pos = vec3(lightposn[index].xyz);
            vec3 direction0 = normalize (temp_pos) ; 
            vec3 half0 = normalize (direction0 + eyedirn) ; 
            totalLighting = totalLighting + ComputeLight(direction0, lightcolor[index].xyzw, normal, half0, diffuse, specular, shininess);
          }
          if(lightposn[index].w == 1.0)
          {
            vec3 position = lightposn[index].xyz / lightposn[index].w ; 
            vec3 direction1 = normalize (position - mypos) ; // no attenuation 
            vec3 half1 = normalize (direction1 + eyedirn) ; 
            totalLighting = totalLighting + ComputeLight(direction1, lightcolor[index].xyzw, normal, half1, diffuse, specular, shininess);
          }
            
          
        }

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

        // Color all pixels black for now, remove this in your implementation!
        
        gl_FragColor = ambient + emission + totalLighting;
    } else {
        gl_FragColor = color; 
    }
}

// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
  
  mat3 R;
  mat3 I = mat3(1,0,0,0,1,0,0,0,1);
  mat3 middle = mat3(axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2], axis[0]*axis[1], axis[1]*axis[1], axis[1]*axis[2], axis[0]*axis[2], axis[1]*axis[2], axis[2]*axis[2]);
  mat3 last = mat3(0,axis[2], -axis[1], -axis[2], 0, axis[0], axis[1], -axis[0], 0);
  
  R = cos((degrees/180.0)*pi)*I+(1-cos((degrees/180.0)*pi))*middle+sin((degrees/180.0)*pi)*last;

  // You will change this return call
  return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
  
  vec3 unit_up = glm::normalize(up);
  
  eye = rotate(degrees, unit_up)*eye;
  
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
  
  vec3 w = glm::cross(eye, up);
  
  vec3 w_unit = glm::normalize(w);
  
  eye = rotate(degrees, w_unit)*eye;
  
  up = rotate(degrees, w_unit)*up;
  
  
  
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
  
  vec3 a = eye;
  
  vec3 w = glm::normalize(a);
  
  vec3 u = glm::normalize(glm::cross(up, w));
  
  vec3 v = glm::normalize(glm::cross(w, u));
  
  mat4 R = mat4(u[0], v[0], w[0], 0, u[1], v[1], w[1], 0, u[2], v[2], w[2], 0, 0, 0, 0, 1);
  
  mat4 T = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye[0], -eye[1], -eye[2], 1);
  
  mat4 M = R*T;
  // You will change this return call
  return M;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

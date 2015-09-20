// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{

  mat3 R;
  mat3 I = mat3(1,0,0,0,1,0,0,0,1);
  mat3 middle = mat3(axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2], axis[0]*axis[1], axis[1]*axis[1], axis[1]*axis[2], axis[0]*axis[2], axis[1]*axis[2], axis[2]*axis[2]);
  mat3 last = mat3(0,axis[2], -axis[1], -axis[2], 0, axis[0], axis[1], -axis[0], 0);
  
  R = cos((degrees/180.0)*pi)*I+(1-cos((degrees/180.0)*pi))*middle+sin((degrees/180.0)*pi)*last;

  // You will change this return call
  return R;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  vec3 unit_up = glm::normalize(up);
  
  eye = rotate(degrees, unit_up)*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  vec3 w = glm::cross(eye, up);
  
  vec3 w_unit = glm::normalize(w);
  
  eye = rotate(degrees, w_unit)*eye;
  
  up = rotate(degrees, w_unit)*up;
  
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  
  ret = mat4(1/(tan(0.5*fovy*pi/180.0)*aspect), 0, 0, 0, 0, 1/tan(0.5*fovy*pi/180.0), 0, 0, 0, 0, -(zFar+zNear)/(zFar-zNear), -1, 0, 0, -2*zFar*zNear/(zFar-zNear), 0);
  //ret=glm::perspective(fovy, aspect, zFar, zNear);
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  
  ret = mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
  
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
  
  ret = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
  
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}

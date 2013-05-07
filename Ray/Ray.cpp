#include "Ray.h"

Ray::Ray(){
  dir = vec3(-1);
  orig = vec3(-1);
}

Ray::Ray(vec3 o, vec3 d){
  dir = d;
  orig = o;
}

Ray::~Ray(){}
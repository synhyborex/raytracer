#include "GeomObj.h"

GeomObj::GeomObj(){
  objID = -1;
  rgbColor = vec3(-1); //-1 indicates color not present
  rgbfColor = vec4(-1);
  ambient = 0.0f;
  diffuse = 0.0f;
  specular = 0.0f;
  roughness = 0.0f;
  reflection = 0.0f;
  refraction = 0.0f;
  ior = 0.0f;
  vec3 translate = vec3(0); //0 indicates no transformation
  vec3 scale = vec3(0);
  vec3 rotate = vec3(0);
  mat4 composite = mat4(1); //identity matrix
  intersection = vec3(0);
}

GeomObj::GeomObj(int id){
  objID = id;
  rgbColor = vec3(-1); //-1 indicates color not present
  rgbfColor = vec4(-1);
  ambient = 0.0f;
  diffuse = 0.0f;
  specular = 0.0f;
  roughness = 0.0f;
  reflection = 0.0f;
  refraction = 0.0f;
  ior = 0.0f;
  vec3 translate = vec3(0); //0 indicates no transformation
  vec3 scale = vec3(0);
  vec3 rotate = vec3(0);
  mat4 composite = mat4(1); //identity matrix
  intersection = vec3(0);
}

GeomObj::~GeomObj(){}
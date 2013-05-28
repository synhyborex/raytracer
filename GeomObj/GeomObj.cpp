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

vec3 GeomObj::transformBB(int x){
  vec3 one,two,three,four,five,six,seven,eight;
  one = vec3(composite*vec4(bb.min.x,bb.min.y,bb.min.z,1));
  two = vec3(composite*vec4(bb.min.x,bb.min.y,bb.max.z,1));
  three = vec3(composite*vec4(bb.min.x,bb.max.y,bb.min.z,1));
  four = vec3(composite*vec4(bb.min.x,bb.max.y,bb.max.z,1));
  five = vec3(composite*vec4(bb.max.x,bb.min.y,bb.min.z,1));
  six = vec3(composite*vec4(bb.max.x,bb.min.y,bb.max.z,1));
  seven = vec3(composite*vec4(bb.max.x,bb.max.y,bb.min.z,1));
  eight = vec3(composite*vec4(bb.max.x,bb.max.y,bb.max.z,1));

  vec3 ret;
  if(x == 0){ //bounding box max
    ret.x = std::max(std::max(std::max(std::max(std::max(std::max(
      std::max(one.x,two.x),three.x),four.x),five.x),six.x),seven.x),eight.x);
    ret.y = std::max(std::max(std::max(std::max(std::max(std::max(
      std::max(one.y,two.y),three.y),four.y),five.y),six.y),seven.y),eight.y);
    ret.z = std::max(std::max(std::max(std::max(std::max(std::max(
      std::max(one.z,two.z),three.z),four.z),five.z),six.z),seven.z),eight.z);
  }
  else if(x == 1){ //bounding box min
    ret.x = std::min(std::min(std::min(std::min(std::min(std::min(
      std::min(one.x,two.x),three.x),four.x),five.x),six.x),seven.x),eight.x);
    ret.y = std::min(std::min(std::min(std::min(std::min(std::min(
      std::min(one.y,two.y),three.y),four.y),five.y),six.y),seven.y),eight.y);
    ret.z = std::min(std::min(std::min(std::min(std::min(std::min(
      std::min(one.z,two.z),three.z),four.z),five.z),six.z),seven.z),eight.z);
  }
  return ret;
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "../WorldObj/Light.h"
#include "../Image/Image.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "../glm/gtc/type_ptr.hpp" //value_ptr
#include <fstream>
#include <cmath>
#include <vector>
#define PLANE 1
#define SPHERE 2
#define CONE 3
#define BOX 4
#define TRIANGLE 5
#define epsilon 0.01f

using namespace std;
using namespace glm;

//bounding box
struct BBox{
  vec3 min, max; //bounds
  vec3 pivot; //center on axes
  bool intersect(vec3 ray, vec3 origin, float* b){
    float tMax = INT_MAX;
    float tMin = INT_MIN;
    float t1,t2;

    for(int i = 0; i < ray.length(); i++){
      t1 = (min[i]-origin[i])/ray[i];
      t2 = (max[i]-origin[i])/ray[i];
      if(t2<t1) swap(t1,t2);
      if(t1>tMin) tMin=t1;
      if(t2<tMax) tMax=t2;
    }

    if(tMin > tMax || tMax < 0){
      return false;
    }
    *b = tMin;
    return true;
  }

  bool intersect(vec3 ray, vec3 origin){
    float tMax = INT_MAX;
    float tMin = INT_MIN;
    float t1,t2;

    for(int i = 0; i < ray.length(); i++){
      t1 = (min[i]-origin[i])/ray[i];
      t2 = (max[i]-origin[i])/ray[i];
      if(t2<t1) swap(t1,t2);
      if(t1>tMin) tMin=t1;
      if(t2<tMax) tMax=t2;
    }

    if(tMin > tMax || tMax < 0){
      return false;
    }
    return true;
  }
};

class GeomObj{
  public:
    GeomObj();
    GeomObj(int id);
    ~GeomObj();
    virtual void parse(ifstream&) =0; //gets object info
    virtual vec3 transformBB(int); //transforms bounding box
    virtual bool intersect(vec3,vec3,float*) =0; //checks for intersections
    virtual void shade(vec3,vec3,color_t*,Light,int) =0; //colors the object
    virtual void printID(){cout << "Geom " << objID << endl;}; //prints ID
    virtual vec3 reflectedRay(vec3,vec3) =0; //returns reflected ray
    virtual vec3 refractedRay(vec3,vec3,vec3*,float*,float*) =0; //returns refracted ray
    virtual int getID(){return objID;}; //returns ID
    virtual void setID(int id){objID = id;}; //sets object ID
    int objID; //object ID
    vec3 rgbColor; //rgb color
    vec4 rgbfColor; //rgbf color
    float ambient; //ambient light
    float diffuse; //diffuse light
    float specular; //specular light
    float roughness; //material value
    float reflection; //reflection value
    float refraction; //refraction value
    float ior; //index of refraction
    vec3 translate; //amount to translate object
    vec3 scale; //amount to scale object
    vec3 rotate; //amount to rotate object
    mat4 composite; //composite transformation matrix
    vec3 intersection; //point of intersection
    BBox bb; //bounding box
};
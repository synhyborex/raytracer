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

using namespace std;
using namespace glm;

class GeomObj{
  public:
    GeomObj();
    GeomObj(int id);
    ~GeomObj();
    virtual void parse(ifstream&) =0; //gets object info
    virtual bool intersect(vec3,vec3,float*) =0; //checks for intersections
    virtual void shade(vec3,vec3,color_t*,Light,int) =0; //colors the object
    virtual void printID(){cout << "Geom " << objID << endl;}; //prints ID
    virtual vec3 reflectedRay(vec3,vec3) =0; //returns reflected ray
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
};
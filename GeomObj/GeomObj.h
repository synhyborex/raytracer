#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "../glm/gtc/type_ptr.hpp" //value_ptr
#include <fstream>

using namespace std;
using namespace glm;

class GeomObj{
  public:
    GeomObj();
    GeomObj(int id);
    ~GeomObj();
    virtual void parse(ifstream&) =0;
    virtual void intersect() =0;
    virtual void shade() =0;
    virtual void printID(){cout << "Geom " << objID << endl;};
    virtual int getID(){return objID;};
    int objID; //object ID
    vec3 rgbColor; //rgb color
    vec3 rgbfColor; //rgbf color
    double ambient; //ambient light
    double diffuse; //diffuse light
    double specular; //specular light
    double roughness; //material value
    double reflection; //reflection value
    double refraction; //refraction value
    double ior; //index of refraction
    vec3 translate; //amount to translate object
    vec3 scale; //amount to scale object
    vec3 rotate; //amount to rotate object
};
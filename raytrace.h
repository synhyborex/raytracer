#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GeomObj/GeomObj.h"
#include "GeomObj/ConeObj.h"
#include "GeomObj/PlaneObj.h"
#include "GeomObj/TriObj.h"
#include "GeomObj/SphereObj.h"
#include "GeomObj/BoxObj.h"
#include "WorldObj/WorldObj.h"
#include "WorldObj/Light.h"
#include "WorldObj/Camera.h"
#include "Image/Image.h"

//scene objects
Light* light;
Camera* camera;
PlaneObj* plane;
SphereObj* sphere;
BoxObj* box;
TriObj* tri;
ConeObj* cone;

//image variables
int imageWidth; //width of image
int imageHeight; //height of image
vec3 objLoc[3]; //coverted location, max of 3 sets
vec3 camLoc; //camera location
vec3 lightLoc; //light location
vec3 ray; //ray to cast
color_t clr; //color
float t; //interpolation value
vec3 camSpace; //camera space coordinates
vec3 worldSpace; //world space coordinates
float rightB, top, bot, leftB; //camera space bounding box

//object storage variables
int totalSize; //number of objects
vector<BoxObj*> BoxList;
vector<ConeObj*> ConeList;
vector<PlaneObj*> PlaneList;
vector<SphereObj*> SphereList;
vector<TriObj*> TriList;

//file pointers
ifstream infile;
char* filename;

/*****FUNCTIONS*****/

float world_to_pixel_x(float height, float width, float x){
  float d = (width-1)/2;
  float c = d;

  return (c*x+d)*height/width; //adjust for scaling
}

float world_to_pixel_y(float height, float width, float y){
  float f = (height-1)/2;
  float e = f;

  return e*y+f;
}
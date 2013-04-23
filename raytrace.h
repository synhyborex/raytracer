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
#include "WorldObj/Camera.h"

//scene objects
Light* light;
Camera* camera;
PlaneObj* plane;
SphereObj* sphere;
BoxObj* box;
TriObj* tri;
ConeObj* cone;

//image variables
Image* img;
int imageWidth; //width of image
int imageHeight; //height of image
color_t clr; //color
float rightB, topB, botB, leftB; //camera space bounding box
int shade; //the kind of shading

//object storage variables
int totalSize; //number of objects
vector<GeomObj*> objList;

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
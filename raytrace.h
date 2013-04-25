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
float rightB, topB, botB, leftB; //camera space bounding box

//coloring variables
color_t clr; //color
color_t background; //default for no color
int shade; //the kind of shading
int recursionDepth; //how many times to recurse

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

color_t raytrace(vec3 ray, vec3 origin){
  color_t clr; //color to return
  float t = INT_MAX; //interpolation value
  float minDist = INT_MAX; //smallest distance
  int bestObj = -1; //closest object. -1 means no intersect
  float reflection; //object reflection coefficient

  recursionDepth--;
  if(recursionDepth >= 0){ //still more recursions to go
    //check primary ray against each object
    for(int size = 0; size < objList.size(); size++){
      //if intersect
      if(objList[size]->intersect(ray,origin,&t)){
        if(t < minDist){ //check depth
          minDist = t; //update depth
          bestObj = size; //update closest object
        }
      }
    }
    vec3 intersection = origin + minDist*ray;

    //figure out what to draw, if anything
    color_t shadeColor;
    if(bestObj != -1){ //valid object
      //get base color
      //using rgb color
      if(objList[bestObj]->rgbColor != vec3(-1)){
        shadeColor.r = objList[bestObj]->rgbColor.x;
        shadeColor.g = objList[bestObj]->rgbColor.y;
        shadeColor.b = objList[bestObj]->rgbColor.z;
      }
      //else using rgbf color
      else if(objList[bestObj]->rgbfColor != vec4(-1)){
        shadeColor.r = objList[bestObj]->rgbfColor.x;
        shadeColor.g = objList[bestObj]->rgbfColor.y;
        shadeColor.b = objList[bestObj]->rgbfColor.z;
        //need to do something with alpha value
      }
      //else invalid color
      else{
        cout << "Invalid color." << endl;
      }

      //reflection
      color_t reflColor;
      reflection = objList[bestObj]->reflection;
      if(reflection > 0.0f){
        vec3 reflect = objList[bestObj]->reflectedRay(ray,intersection); //reflection vector
        reflColor = raytrace(reflect,intersection);
      }
      else{
        reflColor = background;
      }

      ///*
      //check for shadows
      vec3 shadowRay = light->loc - intersection;
      float interp; //linear interpolation value
      bool shadow = false;

      //intersect shadow feeler with geometry
      for(int size = 0; size < objList.size(); size++){
        //if intersection
        if(objList[size]->intersect(shadowRay,intersection,&interp)){
          shadow = true;
        }
      }
      if(!shadow){
        objList[bestObj]->shade(ray,intersection,&shadeColor,*light,shade);
      }
      else{
        //set to ambient color
        shadeColor.r = shadeColor.r*objList[bestObj]->ambient;
        shadeColor.g = shadeColor.g*objList[bestObj]->ambient;
        shadeColor.b = shadeColor.b*objList[bestObj]->ambient;
      }
      //*/

      /* softer-looking shadows
      //set to ambient color
      clr.r = clr.r*objList[bestObj]->ambient;
      clr.g = clr.g*objList[bestObj]->ambient;
      clr.b = clr.b*objList[bestObj]->ambient;

      //check for shadows
      vec3 intersection = camera->loc + minDist*ray;
      vec3 shadowRay = light->loc - intersection;
      float interp; //linear interpolation value

      //intersect shadow feeler with geometry
      for(int size = 0; size < objList.size(); size++){
        //if no intersection or if t is out of range
        if(!objList[size]->intersect(shadowRay,intersection,&interp)){
          //full shading
          objList[bestObj]->shade(ray,intersection,&clr,*light,shade);
        }
      }
      */

      //update color with all values
      clr.r = (1-reflection)*shadeColor.r + reflection*reflColor.r;
      clr.g = (1-reflection)*shadeColor.g + reflection*reflColor.g;
      clr.b = (1-reflection)*shadeColor.b + reflection*reflColor.b;
    }
    else{ //nothing to draw at that pixel
      clr = background;
    }
  }
  else clr = background;
  recursionDepth++;

  return clr;
}
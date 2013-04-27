#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
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
  float epsilon = 0.000001f; //shadow offset

  recursionDepth--;
  if(recursionDepth >= 0){ //still more recursions to go
    //check primary ray against each object
    for(int index = 0; index < objList.size(); index++){
      //if intersect
      if(objList[index]->intersect(ray,origin,&t)){
        if(t > epsilon && t < minDist){ //check depth
          minDist = t; //update depth
          bestObj = index; //update closest object
        }
      }
    }
    //calculate point of intersection
    vec3 intersection = origin + minDist*ray;

    //figure out what to draw, if anything
    color_t shadeColor; //light-based color contribution
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
      color_t reflColor; //reflection-based color contribution
      reflection = objList[bestObj]->reflection; //get reflection value
      if(reflection > 0.0f){ //the surface is reflective
        //calculate reflection vector and recurse with it
        vec3 reflect = objList[bestObj]->reflectedRay(ray,intersection);
        reflColor = raytrace(reflect,intersection);
      }
      else{ //no reflection
        reflColor = background;
      }

      //check for shadows
      vec3 shadowRay = light->loc - intersection; //shadow vector
      float tShadow; //range check
      bool shadow = false; //no shadows

      //intersect shadow feeler with geometry
      for(int index = 0; index < objList.size(); index++){
        //if intersection
        if(objList[index]->intersect(shadowRay,
          intersection+(shadowRay*epsilon),&tShadow)){
          shadow = true;
        }
      }
      if(!shadow){ //no shadows
        objList[bestObj]->shade(ray,intersection,&shadeColor,*light,shade);
      }
      else{ //shadows
        //set to ambient color
        shadeColor.r = shadeColor.r*objList[bestObj]->ambient;
        shadeColor.g = shadeColor.g*objList[bestObj]->ambient;
        shadeColor.b = shadeColor.b*objList[bestObj]->ambient;
      }

      //update color with all values
      clr.r = (1-reflection)*shadeColor.r + reflection*reflColor.r;
      clr.g = (1-reflection)*shadeColor.g + reflection*reflColor.g;
      clr.b = (1-reflection)*shadeColor.b + reflection*reflColor.b;
    }
    else clr = background; //nothing to draw at that pixel
  }
  else clr = background; //nothing to draw at that pixel
  recursionDepth++;

  return clr;
}
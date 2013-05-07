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
#include "Ray/Ray.h"

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

color_t raytrace(Ray ray){
  color_t clr; //color to return
  float t = INT_MAX; //interpolation value
  float minDist = INT_MAX; //smallest distance
  int bestObj = -1; //closest object. -1 means no intersect
  float epsilon = 0.000001f; //shadow offset

  recursionDepth--;
  if(recursionDepth >= 0){ //still more recursions to go
    //check primary ray against each object
    for(int index = 0; index < objList.size(); index++){
      //if intersect
      if(objList[index]->intersect(ray.dir,ray.orig,&t)){
        if(t > epsilon && t < minDist){ //check depth
          minDist = t; //update depth
          bestObj = index; //update closest object
        }
      }
    }

    //figure out what to draw, if anything
    color_t shadeColor; //light-based color contribution
    if(bestObj != -1){ //valid object
      //calculate point of intersection
      vec3 intersection;
      if(objList[bestObj]->objID == 5){
        intersection = objList[bestObj]->intersection;
      } 
      else intersection = ray.orig + minDist*ray.dir;
      
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
      float reflection = objList[bestObj]->reflection; //reflection coeff
      if(reflection > 0.0f){ //the surface is reflective
        //calculate reflection vector and recurse with it
        Ray reflect(intersection,
          objList[bestObj]->reflectedRay(ray.dir,intersection));
        reflColor = raytrace(reflect); //recurse
      }
      else{ //no reflection
        reflColor = background;
      }

      //refraction
      color_t refrColor; //refraction-based color contribution
      float cos_theta = -1.0f; //Schlick cos(theta) term
      float R0 = -1.0f; //R0 for Schlick math
      float refraction = objList[bestObj]->refraction; //refraction coeff
      if(refraction > 0.0f){ //the surface is refractive
        //reflected ray
        //Ray reflect2(intersection,
          //objList[bestObj]->reflectedRay(ray.dir,intersection));

        //calculate refraction vector
        Ray refract(intersection,
          objList[bestObj]->refractedRay(ray.dir,intersection,&cos_theta,&R0));

        //check for valid ray
        if(refract.dir == vec3(-1)) //total internal reflection
          refrColor = background;
        else refrColor = raytrace(refract);
      }
      else{ //no refraction
        refrColor = background;
      }

      //check for shadows
      Ray shadowRay(intersection,light->loc - intersection); //shadow vector
      float tShadow; //range check
      bool shadow = false; //no shadows

      //intersect shadow feeler with geometry
      for(int index = 0; index < objList.size(); index++){
        //if intersection
        if(objList[index]->intersect(shadowRay.dir,
          shadowRay.orig+(shadowRay.dir*epsilon),&tShadow)){
          shadow = true;
        }
      }
      if(!shadow){ //no shadows
        objList[bestObj]->shade(ray.dir,intersection,&shadeColor,*light,shade);
      }
      else{ //shadows
        //set to ambient color
        shadeColor.r = shadeColor.r*objList[bestObj]->ambient;
        shadeColor.g = shadeColor.g*objList[bestObj]->ambient;
        shadeColor.b = shadeColor.b*objList[bestObj]->ambient;
      }

      //Schlick's approximation
      float R; //reflectance term
      if(R0 == -1.0f || cos_theta == -1.0f){
        R = 1.0f;
      }
      else R = R0 + (1-R0)*pow(1-cos_theta,5);

      //update color with all values
      /*clr.r = R*reflColor.r + (1-R)*refrColor.r;
      clr.g = R*reflColor.g + (1-R)*refrColor.g;
      clr.b = R*reflColor.b + (1-R)*refrColor.b;*/
      clr.r = (1-reflection-refraction)*shadeColor.r + reflection*reflColor.r
        + refraction*refrColor.r;
      clr.g = (1-reflection-refraction)*shadeColor.g + reflection*reflColor.g
        + refraction*refrColor.g;
      clr.b = (1-reflection-refraction)*shadeColor.b + reflection*reflColor.b
        + refraction*refrColor.b;
    }
    else clr = background; //nothing to draw at that pixel
  }
  else clr = background; //nothing to draw at that pixel
  recursionDepth++;

  return clr;
}
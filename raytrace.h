#include <stdio.h>
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
#include "GeomObj/BVH_Node.h"
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
vector<GeomObj*> objList; //list of objects
vector<PlaneObj*> planeList; //list of planes
vector<Light*> lightList; //list of lights
BVH_Node* bvh;


//file pointers
ifstream infile;
char* filename;

/*****FUNCTIONS*****/
float world_to_pixel_x(float,float,float);
float world_to_pixel_y(float,float,float);
color_t raytrace(Ray,bool);
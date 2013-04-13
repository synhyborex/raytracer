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

//vector to store objects
vector<GeomObj*> objectList;

//file pointers
ifstream infile;
char* filename;

//window variables
int w_width;
int w_height;
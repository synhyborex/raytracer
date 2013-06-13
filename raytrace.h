#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <string>
#include <streambuf>
#include <climits>
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

/* class to store colors */
class SColor {

public:

    float Red, Green, Blue;

    SColor()
        : Red(0.7f), Green(0.7f), Blue(0.7f) {}

};

/* class to store vector for position (or vector) */
class SVector3 {

public:

    float X, Y, Z;

    SVector3()
        : X(0), Y(0), Z(0) {}

    SVector3(float in)
        : X(in), Y(in), Z(in) {}

    SVector3(float in_x, float in_y, float in_z)
        : X(in_x), Y(in_y), Z(in_z) {}

    SVector3 crossProduct(SVector3 const & v) const {
        return SVector3(Y*v.Z - v.Y*Z, v.X*Z - X*v.Z, X*v.Y - v.X*Y);
    }

    float dotProduct(SVector3 const & v) const {
        return X*v.X + Y*v.Y + Z*v.Z;
    }

    float length() const {
        return sqrtf(X*X + Y*Y + Z*Z);
    }

    SVector3 operator + (SVector3 const & v) const {
        return SVector3(X+v.X, Y+v.Y, Z+v.Z);
    }

    SVector3 & operator += (SVector3 const & v) {
        X += v.X;
        Y += v.Y;
        Z += v.Z;

        return * this;
    }

    SVector3 operator - (SVector3 const & v) const {
        return SVector3(X-v.X, Y-v.Y, Z-v.Z);
    }

    SVector3 & operator -= (SVector3 const & v) {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;

        return * this;
    }

    SVector3 operator * (SVector3 const & v) const {
        return SVector3(X*v.X, Y*v.Y, Z*v.Z);
    }

    SVector3 & operator *= (SVector3 const & v) {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;

        return * this;
    }

    SVector3 operator / (SVector3 const & v) const {
        return SVector3(X/v.X, Y/v.Y, Z/v.Z);
    }

    SVector3 & operator /= (SVector3 const & v) {
        X /= v.X;
        Y /= v.Y;
        Z /= v.Z;

        return * this;
    }

    SVector3 operator * (float const s) const {
        return SVector3(X*s, Y*s, Z*s);
    }

    SVector3 & operator *= (float const s) {
        X *= s;
        Y *= s;
        Z *= s;

        return * this;
    }

    SVector3 operator / (float const s) const {
        return SVector3(X/s, Y/s, Z/s);
    }

    SVector3 & operator /= (float const s) {
        X /= s;
        Y /= s;
        Z /= s;

        return * this;
    }

};

/* class to store a mesh vertex with both a position and color */
class SVertex {

public:

    SVector3 Position;
    SColor Color;

};

/* class to store all the vertices and all the triangles of a mesh */
class CMesh {

public:

    struct STriangle
    {
        unsigned int VertexIndex1, VertexIndex2, VertexIndex3;
        SColor Color;
    };

    std::vector<SVertex> Vertices;
    std::vector<STriangle> Triangles;

    CMesh(){}

    ~CMesh(){}

    void PrintMesh();

    void centerMeshByExtents(SVector3 const & CenterLocation);

    void resizeMesh(SVector3 const & Scale);

    float GetVertex(int i, int j, unsigned int size);

};

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

//BVH variables
BVH_Node* bvh;
bool usebvh;

//file pointers
ifstream infile;
char* filename;

//rasterizer variables
bool useRaster;
CMesh *TheMesh; //global mesh
float** depth; //depth buffer
char** files; //list of files
char** rasterFiles; //list of files
bool* pov; //.pov or .m
bool finalrender; //is it my final render?

/*****RAYTRACER FUNCTIONS*****/
float world_to_pixel_x(float,float,float);
float world_to_pixel_y(float,float,float);
void sampleDisk(float,float,float*,float*);
vec3 diskToHemisphere(float,float);
color_t raytrace(int,int,Ray,bool,int,int);

/*****RASTERIZER FUNCTIONS*****/
void InitGeom(char*);
float getBeta(float,float,vec3[3]);
float getArea(float,float,vec3[3]);
float getGamma(float,float,vec3[3]);
vec3 getNormal(vec3[3],mat4);
vec3 getCenter(vec3[3]);
color_t rasterShade(vec3[3],vec3,mat4,vec4,color_t,Light,int);
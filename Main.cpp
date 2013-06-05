/* Base code for mesh for CPE 471 Rasterizer project */
/* Reads in an ASCII mesh into stl vectors (stored in CMesh class) */
/* heavily edited version of I. Dunn's c++ parser - ZJW */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <string>
#include <streambuf>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include "Image.h"
#include "types.h"

using namespace std;

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

    CMesh();
        void PrintMesh();

    ~CMesh();
    void centerMeshByExtents(SVector3 const & CenterLocation);

    void resizeMesh(SVector3 const & Scale);

    float GetVertex(int i, int j, unsigned int size);

};

/* code to parse through a .m file and write the data into a mesh */
int loadASCIIMesh(std::string const & fileName, CMesh *Mesh) {
    std::ifstream File;
    File.open(fileName.c_str());

    if (! File.is_open())
    {
        std::cerr << "Unable to open mesh file: " << fileName << std::endl;
        return 0;
    }

    //CMesh * Mesh = new CMesh();

    while (File)
    {
        std::string ReadString;
        std::getline(File, ReadString);

        std::stringstream Stream(ReadString);

        std::string Label;
        Stream >> Label;

        if (Label.find("#") != std::string::npos)
        {
            // Comment, skip
            continue;
        }

        if ("Vertex" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            SVector3 Position;
            Stream >> Position.X;
            Stream >> Position.Y;
            Stream >> Position.Z;

            SVertex Vertex;
            Vertex.Position = Position;

            Mesh->Vertices.push_back(Vertex);
        }
        else if ("Face" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            int Vertex1, Vertex2, Vertex3;
            Stream >> Vertex1;
            Stream >> Vertex2;
            Stream >> Vertex3;

            CMesh::STriangle Triangle;
            Triangle.VertexIndex1 = Vertex1 - 1;
            Triangle.VertexIndex2 = Vertex2 - 1;
            Triangle.VertexIndex3 = Vertex3 - 1;

            size_t Location;
            if ((Location = ReadString.find("{")) != std::string::npos) // there is a color
            {
                Location = ReadString.find("rgb=(");
                Location += 5; // rgb=( is 5 characters

                ReadString = ReadString.substr(Location);
                std::stringstream Stream(ReadString);
                float Color;
                Stream >> Color;
                Triangle.Color.Red = Color;
                Stream >> Color;
                Triangle.Color.Green = Color;
                Stream >> Color;
                Triangle.Color.Blue = Color;
            }

            Mesh->Triangles.push_back(Triangle);
        }
        else if ("" == Label)
        {
            // Just a new line, carry on...
        }
        else if ("Corner" == Label)
        {
            // We're not doing any normal calculations... (oops!)
        }
        else
        {
            std::cerr << "While parsing ASCII mesh: Expected 'Vertex' or 'Face' label, found '" << Label << "'." << std::endl;
        }
    }

    if (! Mesh->Triangles.size() || ! Mesh->Vertices.size())
    {
        delete Mesh;
        return 0;
    }

    return 1;
}

CMesh::CMesh()
{}

CMesh::~CMesh()
{}

/* Just an example of how to iterate over the mesh triangles */
void CMesh::PrintMesh() {
    for(unsigned int j = 0; j < Triangles.size(); j++)
    {
        SVertex Vertex;
        cout << "New Vertices from triangle " << j << endl;
        Vertex = Vertices[Triangles[j].VertexIndex1];
        cout << "V1 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
        Vertex = Vertices[Triangles[j].VertexIndex2];
        cout << "V2 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
        Vertex = Vertices[Triangles[j].VertexIndex3];
        cout << "V3 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
    }
}

/* center the mesh */
void CMesh::centerMeshByExtents(SVector3 const & CenterLocation) {
  
    if (Vertices.size() < 2)
        return;

    SVector3 Min, Max;
    {
        std::vector<SVertex>::const_iterator it = Vertices.begin();
        Min = it->Position;
        Max = it->Position;
        for (; it != Vertices.end(); ++ it)
        {
            if (Min.X > it->Position.X)
                Min.X = it->Position.X;
            if (Min.Y > it->Position.Y)
                Min.Y = it->Position.Y;
            if (Min.Z > it->Position.Z)
                Min.Z = it->Position.Z;

            if (Max.X < it->Position.X)
                Max.X = it->Position.X;
            if (Max.Y < it->Position.Y)
                Max.Y = it->Position.Y;
            if (Max.Z < it->Position.Z)
                Max.Z = it->Position.Z;
        }
    }

    SVector3 Center = (Max + Min) / 2;

    SVector3 VertexOffset = CenterLocation - Center;
    for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
        it->Position += VertexOffset;
}

/* resize the mesh */
void CMesh::resizeMesh(SVector3 const & Scale)
{
    if (Vertices.size() < 2)
        return;

    SVector3 Min, Max;
    {
        std::vector<SVertex>::const_iterator it = Vertices.begin();
        Min = it->Position;
        Max = it->Position;
        for (; it != Vertices.end(); ++ it)
        {
            if (Min.X > it->Position.X)
                Min.X = it->Position.X;
            if (Min.Y > it->Position.Y)
                Min.Y = it->Position.Y;
            if (Min.Z > it->Position.Z)
                Min.Z = it->Position.Z;

            if (Max.X < it->Position.X)
                Max.X = it->Position.X;
            if (Max.Y < it->Position.Y)
                Max.Y = it->Position.Y;
            if (Max.Z < it->Position.Z)
                Max.Z = it->Position.Z;
        }
    }

    SVector3 Extent = (Max - Min);
    SVector3 Resize = Scale / std::max(Extent.X, std::max(Extent.Y, Extent.Z));
    for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
        it->Position *= Resize;
}

float CMesh::GetVertex(int i, int j, unsigned int size){
  if(size < Triangles.size())
  {
    SVertex Vertex;
    if(i == 0){
      Vertex = Vertices[Triangles[size].VertexIndex1];

      if(j == 0){
            return Vertex.Position.X;
        }
        else if(j == 1){
            return Vertex.Position.Y;
        }
        else if(j == 2){
        return Vertex.Position.Z;
      }
    }
    else if(i == 1){
        Vertex = Vertices[Triangles[size].VertexIndex2];
        
        if(j == 0){
            return Vertex.Position.X;
        }
        else if(j == 1){
            return Vertex.Position.Y;
      }
      else if(j == 2){
        return Vertex.Position.Z;
      }
    }
    else if(i == 2){
        Vertex = Vertices[Triangles[size].VertexIndex3];
        
      if(j == 0){
            return Vertex.Position.X;
        }
      else if(j == 1){
        return Vertex.Position.Y;
      }
      else if(j == 2){
        return Vertex.Position.Z;
      }
    }
  }

  return -2;
}

/* Global mesh */
CMesh *TheMesh;

/* initialize the geometry 
   Change file name to load a different mesh file
*/

void InitGeom(){
  TheMesh = new CMesh();
  assert(loadASCIIMesh("Models/bunny10k.m", TheMesh));
  TheMesh->resizeMesh(SVector3(1));
  TheMesh->centerMeshByExtents(SVector3(0));
}

float getBeta(float x, float y, float arr[3][3]){
  float beta = arr[0][0] - arr[0][2];
  beta *= y - arr[1][2];
  float temp = x - arr[0][2];
  temp *= arr[1][0] - arr[1][2];
  beta -= temp;
  beta *= 0.5;
  return beta;
}

float getArea(float x, float y, float arr[3][3]){
  float area = arr[0][2] - arr[0][0];
  area *= arr[1][1] - arr[1][0];
  float temp = arr[0][1] - arr[0][0];
  temp *= arr[1][2] - arr[1][0];
  area -= temp;
  area *= 0.5;
  if (area < 0) area *= -1;
  return area;
}

float getGamma(float x, float y, float arr[3][3]){
  float gamma = arr[0][1] - arr[0][0];
  gamma *= y - arr[1][0];
  float temp = x - arr[0][0];
  temp *= arr[1][1] - arr[1][0];
  gamma -= temp;
  gamma *= 0.5;
  return gamma;
}

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

/* now you can do what you'd like with the triangles */
int main(int argc, char *argv[]){
  InitGeom();

  // holds a triangle's 3 vertices' x, y, z
  float arr[3][3];
  int width = 640;
  int height = 480;
  int size = -1;  //used to detect TheMesh->GetVertex error

  //initialize depth buffer
  float depth[width][height];
  for (int i=0; i<width; i++){
    for (int j=0; j<height; j++){
      depth[i][j] = INT_MAX;
    }
  }

  // make a 640x480 image (allocates buffer on the heap)
  Image img(width, height);

  //loop across mesh
  while(++size > -1){
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        arr[j][i] = TheMesh->GetVertex(i, j, size);
        if(arr[j][i] == -2){  //getVertex returned in error
          size = -2;
        }
      }
    }

    if(size == -2){
      break;
    }

    arr[0][0] = world_to_pixel_x(height, width, arr[0][0]);
    arr[1][0] = world_to_pixel_y(height, width, arr[1][0]);
    arr[2][0] *= -1;

    arr[0][1] = world_to_pixel_x(height, width, arr[0][1]);
    arr[1][1] = world_to_pixel_y(height, width, arr[1][1]);
    arr[2][1] *= -1;

    arr[0][2] = world_to_pixel_x(height, width, arr[0][2]);
    arr[1][2] = world_to_pixel_y(height, width, arr[1][2]);
    arr[2][2] *= -1;
      
    // make a color
    color_t clr_a, clr_b, clr_c;

    clr_a.r = 1;
    clr_a.g = 0;
    clr_a.b = 0;

    clr_b.r = 1;
    clr_b.g = 0;
    clr_b.b = 0;
      
    clr_c.r = 1;
    clr_c.g = 0;
    clr_c.b = 0;

    // set a square to be the color above

    //set bounding box
    float max_x = std::max(arr[0][0], arr[0][1]);
    max_x = std::max(max_x, arr[0][2]);
    float max_y = std::max(arr[1][0], arr[1][1]);
    max_y = std::max(max_y, arr[1][2]);
    float min_x = std::min(arr[0][0], arr[0][1]);
    min_x = std::min(min_x, arr[0][2]);
    float min_y = std::min(arr[1][0], arr[1][1]);
    min_y = std::min(min_y, arr[1][2]);
      
    for (int i = min_x; i <= max_x; i++) {
      for (int j = min_y; j <= max_y; j++) {
        float beta = getBeta(i, j, arr);
        float area = getArea(i, j, arr);
        beta /= area;
        float gamma = getGamma(i, j, arr);
        gamma /= area;
        float alpha = 1.0 - beta - gamma;
        if (beta <= 1 && beta >= 0){
          if (gamma <= 1 && gamma >= 0){
            if (alpha <= 1 && alpha >= 0){
              float curZ = alpha*arr[2][0] + beta*arr[2][1] + gamma*arr[2][2];
              if(depth[i][j] > curZ){
                color_t clr;
                clr.r = alpha*clr_a.r + beta*clr_b.r + gamma*clr_c.r;
                clr.r *= (1-curZ)/2; //adjusted for proper shading

                clr.g = alpha*clr_a.g + beta*clr_b.g + gamma*clr_c.g;
                clr.g *= (1-curZ)/2;

                clr.b = alpha*clr_a.b + beta*clr_b.b + gamma*clr_c.b;
                clr.b *= (1-curZ)/2;

                img.pixel(i, j, clr);
                depth[i][j] = curZ;
              }
            }
          }
        }
      }
    }

  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

  return 0;
}

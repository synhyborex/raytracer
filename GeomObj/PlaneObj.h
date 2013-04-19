#pragma once

#include "GeomObj.h"

class PlaneObj: public GeomObj{
  public:
    PlaneObj();
    PlaneObj(int id);
    ~PlaneObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual void shade(vec3,vec3,color_t*,Light,int);
    virtual void printID();
    vec3 getNormal();
    void setNormal(vec3);
    float getDist();
    void setDist(float);

  private:
    vec3 normal; //normal
    float distance; //distance of plane
};
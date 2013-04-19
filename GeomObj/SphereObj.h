#pragma once

#include "GeomObj.h"

class SphereObj: public GeomObj{
  public:
    SphereObj();
    SphereObj(int id);
    ~SphereObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual void shade(vec3,vec3,color_t*,Light,int);
    virtual void printID();
    float getRadius();
    void setRadius(float);
    vec3 getLoc();
    void setLoc(vec3);

  private:
    float radius;
    vec3 loc;

};
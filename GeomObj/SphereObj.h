#pragma once

#include "GeomObj.h"

class SphereObj: public GeomObj{
  public:
    SphereObj();
    SphereObj(int id);
    ~SphereObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual color_t shade(vec3,vec3,color_t,Light,int);
    virtual vec3 reflectedRay(vec3,vec3);
    virtual vec3 refractedRay(vec3,vec3,vec3*,float*,float*);
    virtual void printID();
    virtual vec3 getNormal(vec3);
    float getRadius();
    void setRadius(float);
    vec3 getLoc();
    void setLoc(vec3);

  private:
    float radius;
    vec3 loc;

};
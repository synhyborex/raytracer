#pragma once

#include "GeomObj.h"

class TriObj: public GeomObj{
  public:
    TriObj();
    TriObj(int id);
    ~TriObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual void shade(vec3,vec3,color_t*,Light,int);
    virtual vec3 reflectedRay(vec3,vec3);
    virtual vec3 refractedRay(vec3,vec3,float*, float*);
    virtual void printID();
    vec3 getLoc(int);
    void setLoc(int,vec3);
    vec3 getIntersect(){return triIntersect;};

  private:
    vec3 v1, v2, v3; //triangle vertices
    vec3 triIntersect; //intersection point on triangle
};
#pragma once

#include "GeomObj.h"

class SphereObj: public GeomObj{
  public:
    SphereObj();
    SphereObj(int id);
    ~SphereObj();
    virtual void parse(ifstream&);
    virtual void intersect();
    virtual void shade();
    virtual void printID();
    float getRadius();
    void setRadius(float);
    vec3 getLoc();
    void setLoc(vec3);

  private:
    float radius;
    vec3 loc;

};
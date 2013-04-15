#pragma once

#include "GeomObj.h"

class BoxObj: public GeomObj{
  public:
    BoxObj();
    BoxObj(int id);
    ~BoxObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual void shade();
    virtual void printID();
    vec3 getCorner(int);
    void setCorner(int, vec3);

  private:
    vec3 c1; //corners
    vec3 c2;
};
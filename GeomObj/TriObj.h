#pragma once

#include "GeomObj.h"

class TriObj: public GeomObj{
  public:
    TriObj();
    TriObj(int id);
    ~TriObj();
    virtual void parse(ifstream&);
    virtual void intersect();
    virtual void shade();
    virtual void printID();
    vec3 getLoc(int);
    void setLoc(int, vec3);

  private:
    vec3 v1;
    vec3 v2;
    vec3 v3;
};
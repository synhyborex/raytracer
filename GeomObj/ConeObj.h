#pragma once

#include "GeomObj.h"

class ConeObj: public GeomObj{
  public:
    ConeObj();
    ConeObj(int id);
    ~ConeObj();
    virtual void parse(ifstream&);
    virtual bool intersect(vec3,vec3,float*);
    virtual void shade(vec3,vec3,color_t*,Light,int);
    virtual vec3 reflectedRay(vec3,vec3);
    virtual void printID();
    vec3 getLoc(int);
    void setLoc(int, vec3);
    float getRad(int);
    void setRad(int, float);

  private:
    vec3 end1; //location of first end
    float rad1; //radius of first end
    vec3 end2; //location of second end
    float rad2; //radius of second end

};
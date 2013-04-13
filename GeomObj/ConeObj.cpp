#include "ConeObj.h"

ConeObj::ConeObj(){objID = -1;}
ConeObj::ConeObj(int id){objID = id;}
ConeObj::~ConeObj(){}

void ConeObj::parse(ifstream&){}
void ConeObj::intersect(){}
void ConeObj::shade(){}
void ConeObj::printID(){cout << "Cone " << objID << endl;};

vec3 ConeObj::getLoc(int end){
  if(end == 1)
    return end1;
  else if(end == 2)
    return end2;

  return vec3(-100);
}

void ConeObj::setLoc(int end, vec3 loc){
  if(end == 1)
    end1 = loc;
  else if(end == 2)
    end2 = loc;
}

float ConeObj::getRad(int rad){
  if(rad == 1)
    return rad1;
  else if(rad == 2)
    return rad2;

  return -1;
}

void ConeObj::setRad(int rad, float r){
  if(rad == 1)
    rad1 = r;
  else if(rad == 2)
    rad2 = r;
}
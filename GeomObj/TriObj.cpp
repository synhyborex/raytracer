#include "TriObj.h"

TriObj::TriObj(){objID = -1;}
TriObj::TriObj(int id){objID = id;}
TriObj::~TriObj(){}

void TriObj::parse(ifstream&){}
void TriObj::intersect(){}
void TriObj::shade(){}
void TriObj::printID(){cout << "Tri " << objID << endl;};

vec3 TriObj::getLoc(int v){
  if(v == 1)
    return v1;
  else if(v == 2)
    return v2;
  else if(v == 3)
    return v3;

  return vec3(-100);
}

void TriObj::setLoc(int v, vec3 vec){
  if(v == 1)
    v1 = vec;
  else if(v == 2)
    v2 = vec;
  else if(v == 3)
    v3 = vec;
}
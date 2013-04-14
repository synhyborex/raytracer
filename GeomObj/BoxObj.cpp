#include "BoxObj.h"

BoxObj::BoxObj(){objID = 1;}
BoxObj::BoxObj(int id){objID = id;}
BoxObj::~BoxObj(){}

void BoxObj::parse(ifstream&){}
void BoxObj::intersect(){}
void BoxObj::shade(){}
void BoxObj::printID(){cout << "Box " << objID << endl;};

vec3 BoxObj::getCorner(int id){
  if(id == 1)
    return c1;
  else if(id == 2)
    return c2;

  return vec3(-100);
}

void BoxObj::setCorner(int id, vec3 v){
  if(id == 1)
    c1 = v;
  else if(id == 2)
    c2 = v;
}
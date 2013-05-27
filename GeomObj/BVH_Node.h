#pragma once
#include "GeomObj.h"
#include <algorithm>
#include <list>

class BVH_Node{
  public:
    BVH_Node();
    BVH_Node(vector<GeomObj*>,int);
    BVH_Node(GeomObj*);
    ~BVH_Node();
    BVH_Node* left; //left child
    BVH_Node* right; //right child
    BBox bb; //bounding box
    GeomObj* obj; //the object itself
    bool moreNodes; //nodes following this one or not

    //functions
    BBox combineBoxes(BBox,BBox);
    BVH_Node* makeLeaf(GeomObj*);
    void printTree();
    void printTree(BVH_Node*);
    bool intersect(vec3,vec3,BVH_Node*,float*);
    static bool compareByX(GeomObj*,GeomObj*);
    static bool compareByY(GeomObj*,GeomObj*);
    static bool compareByZ(GeomObj*,GeomObj*);
};
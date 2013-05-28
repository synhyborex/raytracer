#include "BVH_Node.h"

BVH_Node::BVH_Node(){
  obj = NULL;
  moreNodes = true;
}
BVH_Node::BVH_Node(GeomObj* o){
  obj = o;
  left = NULL;
  right = NULL;
  moreNodes = false;
  visited = false;
}
int treesize = 0;
BVH_Node::BVH_Node(vector<GeomObj*> list, int axis){
  treesize++;
  int size = list.size(); //number of elements in list
  this->obj = NULL; //no obj, not a leaf
  this->left = NULL;
  this->right = NULL;
  this->visited = false;
  if(size > 0)
    this->moreNodes = true;
  else this->moreNodes = false;
  if(size == 1){
    this->left = makeLeaf(list[0]);
    this->right = makeLeaf(NULL);
    this->bb = list[0]->bb;
    return;
  }
  if(size == 2){    
    this->left = makeLeaf(list[0]);
    this->right = makeLeaf(list[1]);
    this->bb = combineBoxes(list[0]->bb,list[1]->bb);
    return;
  }
  //sort list
  switch(axis){
    case '0':
      std::sort(list.begin(),list.end(),BVH_Node::compareByX);
    case '1':
      std::sort(list.begin(),list.end(),BVH_Node::compareByY);
    case '2':
      std::sort(list.begin(),list.end(),BVH_Node::compareByZ);
  }

  vector<GeomObj*> firstHalf;
  vector<GeomObj*> secondHalf;
  for(int i = 0; i <= (size/2)-1;i++){
    firstHalf.push_back(list[i]);
  }
  for(int i = size/2; i < size; i++){
    secondHalf.push_back(list[i]);
  }

  if(size > 0)
    left = new BVH_Node(firstHalf,(axis+1)%3);
  if(size > 0)
    right = new BVH_Node(secondHalf,(axis+1)%3);
  bb = combineBoxes(left->bb,right->bb);
}
BVH_Node::~BVH_Node(){}

void BVH_Node::printTree(){
  printTree(this);
}

void BVH_Node::printTree(BVH_Node* head){
  /*std::list<BVH_Node*> stack;
  BVH_Node* cur;
  stack.push_front(this);
  while(!stack.empty()){
    cur = stack.front();
    if(cur != NULL){
      if(!cur->visited){
        stack.push_front(cur->left);
      }
      else{
        if(cur->obj)
          cout << cur->obj->objID << endl;
        stack.pop_front();
        stack.push_front(cur->right);
      }
    }
    else{
      stack.pop_front();
      if(!stack.empty())
        stack.front()->visited = true;
    }
  }*/
  BVH_Node* cur;
  cur = head;
  if(cur == NULL)
    return; 
  printTree(cur->left);
  cur->visited = true;
  if(cur->obj)
    cout << cur->obj->objID << endl;
  printTree(cur->right);
}

BVH_Node* BVH_Node::makeLeaf(GeomObj* v){return new BVH_Node(v);}

bool BVH_Node::intersect(BVH_Node* head, vec3 ray, vec3 origin,
  BVH_Node* n, float* tMain){
  BVH_Node* cur;
  cur = head;
  float tLeft = INT_MAX, tRight = INT_MAX, tPass = INT_MAX;
  bool hitLeft = false, hitRight = false, hit = false;
  BVH_Node* leftRet = NULL;
  BVH_Node* rightRet = NULL;
  BVH_Node* ret = NULL;

  /*if(cur == NULL || !cur->bb.intersect(ray,origin)) return false;
  //check if leaf
  if(!cur->moreNodes && cur->obj){
    if(cur->obj->bb.intersect(ray,origin)){
      if(cur->obj->intersect(ray,origin,&tPass)){
        if(tPass < *tMain){
          *tMain = tPass;
          *n = *cur;
          return true;
        }
      }
    }
  }

  hitLeft = cur->intersect(cur->left,ray,origin,leftRet,&tLeft);
  hitRight = cur->intersect(cur->right,ray,origin,rightRet,&tRight);

  if(hitLeft && hitRight){
    if(tLeft <= tRight){
      *n = *leftRet;
      *tMain = tLeft;
    }
    else{
      *n = *rightRet;
      *tMain = tRight;
    }
  }
  else if(hitLeft){
    *n = *leftRet;
    *tMain = tLeft;
  }
  else if(hitRight){
    *n = *rightRet;
    *tMain = tRight;
  }*/

  std::list<BVH_Node*> stack;

  //traverse tree
  stack.push_front(this);
  while(!stack.empty()){
    cur = stack.front();
    /*if(cur != NULL && cur->bb.intersect(ray,origin)){
      if(!cur->visited && cur->moreNodes){
        stack.push_front(cur->left);
      }
      else{
        stack.pop_front();
        if(cur->moreNodes)
          stack.push_front(cur->right);
      }
    }
    else{
      stack.pop_front();
      if(!stack.empty())
        stack.front()->visited = true;
    }*/


    stack.pop_front();
    //not a leaf
    if(cur->moreNodes && cur->bb.intersect(ray,origin)){
      //left is leaf
      if(!cur->left->moreNodes && cur->left->obj){
        if(cur->left->obj->bb.intersect(ray,origin)){
          if(cur->left->obj->intersect(ray,origin,&tLeft)){
            if(tLeft < *tMain)
              *tMain = tLeft;
            leftRet = cur->left;
            hitLeft = true;
          }
        }
      }
      //left not leaf, go down
      else{
        stack.push_front(cur->left);
        //hitLeft = false;
      } 
      //right is leaf
      if(!cur->right->moreNodes && cur->right->obj){
        if(cur->right->obj->bb.intersect(ray,origin)){
          if(cur->right->obj->intersect(ray,origin,&tRight)){
            if(tRight < *tMain)
              *tMain = tRight;
            rightRet = cur->right;
            hitRight = true;
          }
        }
      }
      //right not leaf, go down
      else{
        stack.push_front(cur->right);
        //hitRight = false;
      } 
    }
  }
  if(hitLeft && hitRight){
    if(tLeft <= tRight){
      *n = *leftRet;
      //*tMain = tLeft;
    }
    else{
      *n = *rightRet;
      //*tMain = tRight;
    }
  }
  else if(hitLeft){
    *n = *leftRet;
    //*tMain = tLeft;
  }
  else if(hitRight){
    *n = *rightRet;
    //*tMain = tRight;
  }

  /*float tLeft=INT_MAX, tRight=INT_MAX;
  BVH_Node* leftRet;
  BVH_Node* rightRet;*/
  /*float hack;
  if(moreNodes && bb.intersect(ray,origin,&hack)){
    //left is leaf
    if(!left->moreNodes && left->obj){
      //cout << cur->left->obj->objID << endl;
      if(left->obj->bb.intersect(ray,origin,&tLeft)){
        //cout << "yee buddy left" << endl;
        leftRet = left;
        hitLeft = true;
      }
    }
    //left not leaf, go down
    else{
      stack.push_front(cur->left);
      //hitLeft = false;
    } 
    //right is leaf
    if(!cur->right->moreNodes && cur->right->obj){
      //cout << cur->right->obj->objID << endl;
      if(cur->right->obj->bb.intersect(ray,origin,&tRight)){
        //cout << "yee buddy RIGHT" << endl;
        rightRet = cur->right;
        hitRight = true;
      }
    }
    //right not leaf, go down
    else{
      stack.push_front(cur->right);
      //hitRight = false;
    } 
  }
  else cout << " hello " << obj->objID << endl;
  if(hitLeft && hitRight){
    *n = *leftRet;
  }
  else if(hitLeft){
    *n = *leftRet;
  }
  else if(hitRight){
    *n = *rightRet;
  }*/

  return (hitLeft || hitRight);
}

BBox BVH_Node::combineBoxes(BBox one, BBox two){
  BBox box;
  float xmin=std::min(one.min.x,two.min.x),
    ymin=std::min(one.min.y,two.min.y),
    zmin=std::min(one.min.z,two.min.z);
  float xmax=std::max(one.max.x,two.max.x),
    ymax=std::max(one.max.y,two.max.y),
    zmax=std::max(one.max.z,two.max.z);
  box.min = vec3(xmin,ymin,zmin);
  box.max = vec3(xmax,ymax,zmax);
  box.pivot = (box.min+box.max)/2.0f;
  return box;
}

bool BVH_Node::compareByX(GeomObj* one, GeomObj* two){
  return one->bb.pivot.x < two->bb.pivot.x;
}
bool BVH_Node::compareByY(GeomObj* one, GeomObj* two){
  return one->bb.pivot.y < two->bb.pivot.y;
}
bool BVH_Node::compareByZ(GeomObj* one, GeomObj* two){
  return one->bb.pivot.z < two->bb.pivot.z;
}
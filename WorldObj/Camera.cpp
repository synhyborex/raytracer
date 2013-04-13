#include "Camera.h"

Camera::Camera(){
  up = vec3(0);
  right = vec3(0);
  lookAt = vec3(0);
}

Camera::~Camera(){}

void Camera::parse(ifstream &infile){
  char* nextString;
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "CAMERA - Could not allocate memory for next string" << endl;
  }

  infile.getline(nextString,10); //skip rest of line
  while(strcmp(nextString,"}")){
    infile >> nextString; //get first string on line

    //location option
    if(!strcmp(nextString,"location")){
      //location on x axis
      infile.getline(nextString,15,','); //go until first comma
      while(nextString[0] == ' ' || nextString[0] == '<') //get to value
        nextString = nextString+1;
      loc.x = strtod(nextString,NULL); //set x position

      //location on y axis
      infile.getline(nextString,15,','); //go until second comma
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      loc.y = strtod(nextString,NULL); //set y position

      //location on z axis
      infile.getline(nextString,15,'>'); //go until end of line
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      loc.z = strtod(nextString,NULL); //set z position
    }

    //up option
    else if(!strcmp(nextString,"up")){
      //location on x axis
      infile.getline(nextString,15,','); //go until first comma
      while(nextString[0] == ' ' || nextString[0] == '<') //get to value
        nextString = nextString+1;
      up.x = strtod(nextString,NULL); //set x position

      //location on y axis
      infile.getline(nextString,15,','); //go until second comma
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      up.y = strtod(nextString,NULL); //set y position

      //location on z axis
      infile.getline(nextString,15,'>'); //go until end of line
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      up.z = strtod(nextString,NULL); //set z position
    }

    //right option
    else if(!strcmp(nextString,"right")){
      //location on x axis
      infile.getline(nextString,15,','); //go until first comma
      while(nextString[0] == ' ' || nextString[0] == '<') //get to value
        nextString = nextString+1;
      right.x = strtod(nextString,NULL); //set x position

      //location on y axis
      infile.getline(nextString,15,','); //go until second comma
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      right.y = strtod(nextString,NULL); //set y position

      //location on z axis
      infile.getline(nextString,15,'>'); //go until end of line
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      right.z = strtod(nextString,NULL); //set z position
    }

    //lookAt option
    else if(!strcmp(nextString,"look_at")){
      //location on x axis
      infile.getline(nextString,15,','); //go until first comma
      while(nextString[0] == ' ' || nextString[0] == '<') //get to value
        nextString = nextString+1;
      lookAt.x = strtod(nextString,NULL); //set x position

      //location on y axis
      infile.getline(nextString,15,','); //go until second comma
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      lookAt.y = strtod(nextString,NULL); //set y position

      //location on z axis
      infile.getline(nextString,15,'>'); //go until end of line
      while(nextString[0] == ' ') //get to value
        nextString = nextString+1;
      lookAt.z = strtod(nextString,NULL); //set z position
    }
  }
}

vec3 Camera::getUp(){return up;}
void Camera::setUp(vec3 v){up = v;}

vec3 Camera::getRight(){return right;}
void Camera::setRight(vec3 v){right = v;}

vec3 Camera::getLook(){return lookAt;}
void Camera::setLook(vec3 v){lookAt = v;}
#include "TriObj.h"

TriObj::TriObj(){objID = -1;}
TriObj::TriObj(int id){objID = id;}
TriObj::~TriObj(){}

void TriObj::parse(ifstream& infile){
  char* nextString;
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "TRIANGLE - Could not allocate memory for next string" << endl;
  }

  //vertex 1 option
    infile.getline(nextString,10,'<'); //go to first value
    //location on x axis
    infile.getline(nextString,25,','); //go until first comma
    v1.x = strtod(nextString,NULL); //set x position

    //location on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v1.y = strtod(nextString,NULL); //set y position

    //location on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v1.z = strtod(nextString,NULL); //set z position

  //vertex 2 option
    infile.getline(nextString,10,'<'); //go to first value
    //location on x axis
    infile.getline(nextString,25,','); //go until first comma
    v2.x = strtod(nextString,NULL); //set x position

    //location on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v2.y = strtod(nextString,NULL); //set y position

    //location on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v2.z = strtod(nextString,NULL); //set z position

  //vertex 3 option
    infile.getline(nextString,10,'<'); //go to first value
    //location on x axis
    infile.getline(nextString,25,','); //go until first comma
    v3.x = strtod(nextString,NULL); //set x position

    //location on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v3.y = strtod(nextString,NULL); //set y position

    //location on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    v3.z = strtod(nextString,NULL); //set z position

  bool pad = false; //padding
  while(strcmp(nextString,"}")){
    if(!pad){ //padding check
      infile >> nextString; //get option on next line
    }
    pad = false;

    //pigment option
    if(!strcmp(nextString,"pigment")){
      infile.getline(nextString,10,'{'); //skip open bracket
      infile >> nextString; //get option
      //color option
      if(!strcmp(nextString,"color")){
        //color options
          infile >> nextString;
          //rgb colors
          if(!strcmp(nextString,"rgb")){
            //amount of red
            infile.getline(nextString,10,'<'); //skip until number
            infile.getline(nextString,15,','); //get value
            rgbColor.x = strtod(nextString,NULL); //assign value

            //amount of green
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            infile.getline(nextString,15,','); //get value
            rgbColor.y = strtod(nextString,NULL); //assign value

            //amount of blue
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            infile.getline(nextString,15,'>'); //get value
            rgbColor.z = strtod(nextString,NULL); //assign value

            infile.getline(nextString,15); //throw away rest of line
            //check for padding
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            if(nextString[0] == '}'){
              infile >> nextString;
              pad = true;
            }
          }
          //rgbf colors
          else if(!strcmp(nextString,"rgbf")){
            //amount of red
            infile.getline(nextString,10,'<'); //skip until number
            infile.getline(nextString,15,','); //get value
            rgbfColor.x = strtod(nextString,NULL); //assign value

            //amount of green
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            infile.getline(nextString,15,','); //get value
            rgbfColor.y = strtod(nextString,NULL); //assign value

            //amount of blue
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            infile.getline(nextString,15,','); //get value
            rgbfColor.z = strtod(nextString,NULL); //assign value

            //alpha value
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            infile.getline(nextString,15,'>'); //get value
            rgbfColor[3] = strtod(nextString,NULL); //assign value

            infile.getline(nextString,15); //throw away rest of line
            //check for padding
            while(nextString[0] == ' ') //get to value
              nextString = nextString+1;
            if(nextString[0] == '}'){
              infile >> nextString;
              pad = true;
            }
          }
      }
    }
    //finish option
    else if(!strcmp(nextString,"finish")){
      infile.getline(nextString,10,'{'); //skip over bracket
      while(strcmp(nextString,"}")){
          infile >> nextString; //get option

        //ambient
        if(!strcmp(nextString,"ambient")){
          infile >> nextString; //get value
          ambient = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //diffuse
        else if(!strcmp(nextString,"diffuse")){
          infile >> nextString; //get value
          diffuse = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //specular
        else if(!strcmp(nextString,"specular")){
          infile >> nextString; //get value
          specular = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //roughness
        else if(!strcmp(nextString,"roughness")){
          infile >> nextString; //get value
          roughness = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //reflection
        else if(!strcmp(nextString,"reflection")){
          infile >> nextString; //get value
          reflection = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //refraction
        else if(!strcmp(nextString,"refraction")){
          infile >> nextString; //get value
          refraction = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
        //index of refraction
        else if(!strcmp(nextString,"ior")){
          infile >> nextString; //get value
          ior = strtod(nextString,NULL);
          if(nextString[strlen(nextString)-1] == '}'){
            break;
          }
        }
      }
    }
    //check for transforms
    else{
      //scale
      if(!strcmp(nextString,"scale")){
        infile.getline(nextString,10,'<'); //go to first value
        //scale on x axis
        infile.getline(nextString,25,','); //go until first comma
        scale.x = strtod(nextString,NULL); //set x position

        //scale on y axis
        infile.getline(nextString,25,','); //go until second comma
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        scale.y = strtod(nextString,NULL); //set y position

        //scale on z axis
        infile.getline(nextString,25,'>'); //go until end of line
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        scale.z = strtod(nextString,NULL); //set z position
      }
      //translate
      else if(!strcmp(nextString,"translate")){
        infile.getline(nextString,10,'<'); //go to first value
        //scale on x axis
        infile.getline(nextString,25,','); //go until first comma
        translate.x = strtod(nextString,NULL); //set x position

        //scale on y axis
        infile.getline(nextString,25,','); //go until second comma
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        translate.y = strtod(nextString,NULL); //set y position

        //scale on z axis
        infile.getline(nextString,25,'>'); //go until end of line
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        translate.z = strtod(nextString,NULL); //set z position
      }
      //rotate
      else if(!strcmp(nextString,"rotate")){
        infile.getline(nextString,10,'<'); //go to first value
        //scale on x axis
        infile.getline(nextString,25,','); //go until first comma
        rotate.x = strtod(nextString,NULL); //set x position

        //scale on y axis
        infile.getline(nextString,25,','); //go until second comma
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        rotate.y = strtod(nextString,NULL); //set y position

        //scale on z axis
        infile.getline(nextString,25,'>'); //go until end of line
        while(nextString[0] == ' ') //get to value
          nextString = nextString+1;
        rotate.z = strtod(nextString,NULL); //set z position
      }
    }
  }
}

bool TriObj::intersect(vec3 ray, vec3 cam, float *t){return true;}
void TriObj::shade(vec3 ray, vec3 worldPos, color_t *clr, Light l, int shade){}
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
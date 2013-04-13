#include "Light.h"

Light::Light(){
  rgbColor = vec3(-1); //-1 indicates color not present
  rgbfColor = vec4(-1);
}

Light::~Light(){}

void Light::parse(ifstream &infile){
  char* nextString;
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "LIGHT - Could not allocate memory for next string" << endl;
  }

  infile.getline(nextString,10,'<'); //skip line until first number

  //location option
    //location on x axis
    infile.getline(nextString,15,','); //go until first comma
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

    //color option
    infile >> nextString;
    if(!strcmp(nextString,"color")){
      infile >>nextString;
      //color options
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
        }
    }
}

vec3 Light::getRGBColor(){return rgbColor;}
void Light::setRGBColor(vec3 v){rgbColor = v;}

vec4 Light::getRGBFColor(){return rgbfColor;}
void Light::setRGBFColor(vec4 v){rgbfColor = v;}
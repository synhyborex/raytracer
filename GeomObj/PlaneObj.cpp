#include "PlaneObj.h"

PlaneObj::PlaneObj(){objID = -1;}
PlaneObj::PlaneObj(int id){objID = id;}
PlaneObj::~PlaneObj(){}

void PlaneObj::parse(ifstream &infile){
  char* nextString;
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "PLANE - Could not allocate memory for next string" << endl;
  }

  //normal option
    infile.getline(nextString,10,'<'); //go to first value
    //direction on x axis
    infile.getline(nextString,25,','); //go until first comma
    normal.x = strtod(nextString,NULL); //set x position

    //direction on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    normal.y = strtod(nextString,NULL); //set y position

    //direction on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    normal.z = strtod(nextString,NULL); //set z position

  //distance option
    infile.getline(nextString,20,','); //discard commas
    infile >> nextString; //get distance value
    distance = strtod(nextString,NULL); //set value

    bool pad = false; //pad check
    while(strcmp(nextString,"}")){
      if(!pad){ //padding check
        infile >> nextString; //get option on next line
        pad = false;
      }

      //pigment option
      if(!strcmp(nextString,"pigment")){
        infile.getline(nextString,10,'{'); //skip bracket
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
          }
          //diffuse
          else if(!strcmp(nextString,"diffuse")){
            infile >> nextString; //get value
            diffuse = strtod(nextString,NULL);
          }
          //specular
          else if(!strcmp(nextString,"specular")){
            infile >> nextString; //get value
            specular = strtod(nextString,NULL);
          }
          //roughness
          else if(!strcmp(nextString,"roughness")){
            infile >> nextString; //get value
            roughness = strtod(nextString,NULL);
          }
          //reflection
          else if(!strcmp(nextString,"reflection")){
            infile >> nextString; //get value
            reflection = strtod(nextString,NULL);
          }
          //refraction
          else if(!strcmp(nextString,"refraction")){
            infile >> nextString; //get value
            refraction = strtod(nextString,NULL);
          }
          //ior
          else if(!strcmp(nextString,"ior")){
            infile >> nextString; //get value
            ior = strtod(nextString,NULL);
          }
        }
      }
    }
}

bool PlaneObj::intersect(vec3 ray, vec3 cam, float *t){
  float denom = dot(ray,normal);
  vec3 p = normalize(normal)*distance;

  if(denom == 0)
    return false;
  
  *t = dot(p-cam,normal)/denom;

  if(*t > 0){
    return true;
  }
  else{
    return false;
  }
}
void PlaneObj::shade(vec3 ray, vec3 worldPos, color_t *clr, Light l, int shade){
  vec3 N = normalize(normal); //normal vector
  vec3 L = normalize((l.loc-worldPos)); //light vector
  vec3 V = normalize(-ray); //view vector
  vec3 H = normalize(L+V); //halfway vector
  vec3 R; //reflection vector
  vec4 lightColor; //color of light
  float diffuseRed, diffuseBlue, diffuseGreen;
  float specRed, specBlue, specGreen;

  //get the color of the light
  if(l.getRGBColor() != vec3(-1)){
    lightColor = vec4(l.getRGBColor(),0.0f);
  }
  else if(l.getRGBFColor() != vec4(-1)){
    lightColor = l.getRGBFColor();
  }

  //calculate R
  R = vec3(-1.0 * L.x, -1.0 * L.y, -1.0 * L.z);
  float temp = 2.0*dot(L,N);
  vec3 tempR = vec3(temp * N.x, temp * N.y, temp * N.z);
  R = vec3(R.x + tempR.x, R.y + tempR.y, R.z + tempR.z);
  R = normalize(R);

  //diffuse calculations
  float tempD = std::max(dot(N,L),0.0f);
  diffuseRed = diffuse*tempD*lightColor[0];
  diffuseBlue = diffuse*tempD*lightColor[1];
  diffuseGreen = diffuse*tempD*lightColor[2];
  //need to do something for alpha value

  //specular calculations
  float tempS;
  switch(shade){
    case 0: //Phong
      tempS = std::max(dot(V,R),0.0f);
      if(roughness > 0.0f)
        tempS = std::pow(tempS,1/roughness);
      break;
    case 1: //Gaussian
      float theta;
      if(roughness == 0.0f)
        roughness += 0.00001;
      theta = acos(dot(N,H)/(length(N)*length(H)));
      tempS = exp(-pow(theta/roughness,2));
      break;
  }
  specRed = specular*tempS*lightColor[0];
  specBlue = specular*tempS*lightColor[1];
  specGreen = specular*tempS*lightColor[2];

  clr->r = clr->r*diffuseRed + clr->r*specRed + clr->r*ambient;
  clr->g = clr->g*diffuseGreen + clr->g*specGreen + clr->g*ambient;
  clr->b = clr->b*diffuseBlue + clr->b*specBlue + clr->b*ambient;
}

vec3 PlaneObj::reflectedRay(vec3 ray, vec3 origin){
  vec4 tempNorm = glm::transpose(glm::inverse(composite))*vec4(normal,0);
  vec3 norm; //3-component version of transformed normal
  for(int i = 0; i < norm.length(); i++){
    norm[i] = tempNorm[i];
  }
  return ray - 2*(dot(ray,norm))*norm;
}

vec3 PlaneObj::refractedRay(vec3 ray, vec3 origin, float *cos, float *r0){
  vec4 tempNorm = glm::transpose(glm::inverse(composite))*vec4(normal,0);
  float n1, n2; //indicies of refraction
  vec3 norm; //3-component version of transformed normal
  for(int i = 0; i < norm.length(); i++){
    norm[i] = tempNorm[i];
  }
  //into air out of obj
  if(dot(ray,norm) < 0){
    n1 = ior;
    n2 = 1.0f;
  }
  //into obj out of air
  else{
    n1 = 1.0f;
    n2 = ior;
    norm = -norm;
  }

  //check value under sqrt
  float disc = 1-(pow((n1/n2),2)*(1-pow(dot(ray,norm),2)));
  if(disc < 0){
    return vec3(-1);
  }

  //calculate values needed for Schlick
  *cos = dot(ray,-norm);
  *r0 = pow((n1-n2)/(n1+n2),2);

  return (n1/n2)*(ray-norm*dot(ray,norm))-norm*sqrt(disc);
}

void PlaneObj::printID(){cout << "Plane " << objID << endl;};

vec3 PlaneObj::getNormal(){return normal;}
void PlaneObj::setNormal(vec3 v){
  normal = v;
}

float PlaneObj::getDist(){return distance;}
void PlaneObj::setDist(float f){
  distance = f;
}
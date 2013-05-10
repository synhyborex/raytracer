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

        //add transform to composite matrix
        mat4 scaleMat = glm::scale(mat4(1.0f),scale);
        if(scaleMat != mat4(1.0f))
          composite = scaleMat*composite;
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

        //add transform to composite matrix
        mat4 transMat = glm::translate(mat4(1.0f),translate);
        if(transMat != mat4(1.0f))
          composite = transMat*composite;
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

        //add transform to composite matrix
        float degree;
        vec3 axis;
        if(rotate.x != 0.0f){
          degree = rotate.x;
          axis = vec3(1,0,0);
        }
        else if(rotate.y != 0.0f){
          degree = rotate.y;
          axis = vec3(0,1,0);
        }
        else if(rotate.z != 0.0f){
          degree = rotate.z;
          axis = vec3(0,0,1);
        }

        mat4 rotMat = glm::rotate(mat4(1.0f),degree,axis);
        if(rotMat != mat4(1.0f))
          composite = rotMat*composite;
      }
    }
  }
}

bool TriObj::intersect(vec3 ray, vec3 origin, float *t){
  if(composite != mat4(1)){
    vec4 ray2 = glm::inverse(composite)*vec4(ray,0);
    vec4 origin2 = glm::inverse(composite)*vec4(origin,1);
    for(int i = 0; i < ray.length(); i++){
      ray[i] = ray2[i];
      origin[i] = origin2[i];
    }
  }
  float gamma, beta; //boundary values
  vec3 u = v1-v2;
  vec3 v = v1-v3;
  vec3 toTri = v1-origin;

  //make matrices out of the above vectors
  glm::mat3 A(u,v,ray);
  glm::mat3 betaMat(toTri,v,ray);
  glm::mat3 gammaMat(u,toTri,ray);
  glm::mat3 tMat(u,v,toTri);

  //Cramer's rule to get beta and gamma
  float detA = determinant(A);
  float detBeta = determinant(betaMat);
  float detGamma = determinant(gammaMat);
  float detT = determinant(tMat);

  beta = detBeta/detA;
  if(beta < 0 || beta > 1) //check for validity
    return false;

  gamma = detGamma/detA;
  if(gamma < 0 || gamma > 1) //check for validity
    return false;

  //make sure beta and gamma aren't too big
  if(gamma+beta <= 1){
    intersection = v1+(beta*(u))+(gamma*(v));
    *t = detT/detA;
    return true;
  }

  return false;
}

void TriObj::shade(vec3 ray, vec3 worldPos, color_t *clr, Light l, int shade){
  vec3 N = normalize(cross(v2-v1,v3-v1)); //normal vector
  if(composite != mat4(1)){
    vec4 tempNorm = glm::transpose(glm::inverse(composite))*vec4(N,0);
    for(int i = 0; i < N.length(); i++){
      N[i] = tempNorm[i];
    }
  }
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

  //set color
  clr->r = clr->r*diffuseRed + clr->r*specRed + clr->r*ambient;
  clr->g = clr->g*diffuseGreen + clr->g*specGreen + clr->g*ambient;
  clr->b = clr->b*diffuseBlue + clr->b*specBlue + clr->b*ambient;
}

vec3 TriObj::reflectedRay(vec3 ray, vec3 origin){
  vec3 normal = cross(v2-v1,v3-v1); //triangle normal
  if(composite != mat4(1)){
    vec4 tempNorm = glm::transpose(glm::inverse(composite))*vec4(normal,0);
    for(int i = 0; i < normal.length(); i++){
      normal[i] = tempNorm[i];
    }
  }
  ray = normalize(ray);
  normal = normalize(normal);
  return ray - 2*(dot(ray,normal))*normal;
}

vec3 TriObj::refractedRay(vec3 ray, vec3 origin, vec3 *offsetOrig, float *cos, float *r0){
  float n1, n2; //indicies of refraction
  vec3 normal = cross(v2-v1,v3-v1); //triangle normal
  if(composite != mat4(1)){
    vec4 tempNorm = glm::transpose(glm::inverse(composite))*vec4(normal,0);
    for(int i = 0; i < normal.length(); i++){
      normal[i] = tempNorm[i];
    }
  }
  //ray = normalize(ray);
  //normal = normalize(normal);
  //into obj out of air
  if(dot(ray,normal) < 0){
    n1 = 1.0f;
    n2 = ior;
    //normal = -normal;
  }
  //into air out of obj
  else{
    n1 = ior;
    n2 = 1.0f;  
    normal = -normal;
  }

  //calculate values needed for Schlick
  *cos = dot(ray,-normal);
  //*r0 = pow((n1-n2)/(n1+n2),2);

  //check value under sqrt
  float nRatio = n1/n2;
  float disc = 1-(pow(nRatio,2)*(1-pow(*cos,2)));
  if(disc < 0){ //total internal reflection
    *offsetOrig = origin + normal*.01f; //set offset origin
    return ray - 2*-(*cos)*normal; //reflection vector
  }

  *offsetOrig = origin - normal*.01f; //set offset origin
  return (nRatio*ray)+(((nRatio*(*cos))-sqrt(disc))*normal);
}

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
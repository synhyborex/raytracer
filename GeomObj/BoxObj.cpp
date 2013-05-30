#include "BoxObj.h"

BoxObj::BoxObj(){objID = -1;}

BoxObj::BoxObj(int id){objID = id;}

BoxObj::~BoxObj(){}

void BoxObj::parse(ifstream& infile){
  char* nextString;
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "BOX - Could not allocate memory for next string" << endl;
  }

  //corner 1 option
    infile.getline(nextString,10,'<'); //go to first value
    //location on x axis
    infile.getline(nextString,25,','); //go until first comma
    c1.x = strtod(nextString,NULL); //set x position

    //location on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    c1.y = strtod(nextString,NULL); //set y position

    //location on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    c1.z = strtod(nextString,NULL); //set z position

  //corner 2 option
    infile.getline(nextString,10,'<'); //go to first value
    //location on x axis
    infile.getline(nextString,25,','); //go until first comma
    c2.x = strtod(nextString,NULL); //set x position

    //location on y axis
    infile.getline(nextString,25,','); //go until second comma
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    c2.y = strtod(nextString,NULL); //set y position

    //location on z axis
    infile.getline(nextString,25,'>'); //go until end of line
    while(nextString[0] == ' ') //get to value
      nextString = nextString+1;
    c2.z = strtod(nextString,NULL); //set z position

  //create min and max values
  float xmin=std::min(c1.x,c2.x),
    ymin=std::min(c1.y,c2.y),zmin=std::min(c1.z,c2.z);
  float xmax=std::max(c1.x,c2.x),
    ymax=std::max(c1.y,c2.y),zmax=std::max(c1.z,c2.z);
  min = vec3(xmin,ymin,zmin);
  max = vec3(xmax,ymax,zmax);
  bb.min = min;
  bb.max = max;
  bb.pivot = (bb.min+bb.max)/2.0f;

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
  //apply transforms to bounding box
  bb.max = transformBB(0);
  bb.min = transformBB(1);
  //apply inverse to composite
  composite = glm::inverse(composite);
}

bool BoxObj::intersect(vec3 ray, vec3 origin, float *t){
  if(composite != mat4(1)){
    ray = vec3(composite*vec4(ray,0));
    origin = vec3(composite*vec4(origin,1));
  }

  float tMax = INT_MAX;
  float tMin = INT_MIN;
  float t1,t2;

  for(int i = 0; i < ray.length(); i++){
    t1 = (min[i]-origin[i])/ray[i];
    t2 = (max[i]-origin[i])/ray[i];
    if(t2<t1) swap(t1,t2);
    if(t1>tMin) tMin=t1;
    if(t2<tMax) tMax=t2;
  }

  if(tMin > tMax || tMax < 0){
    return false;
  }

  *t = tMin;
  intersection = origin + (*t)*ray;
  return true;
}

void BoxObj::shade(vec3 ray,vec3 worldPos,color_t* clr,Light l, int shade){
  vec3 N = normalize(getNormal(worldPos)); //normal vector
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
      theta = acosf(dot(N,H)/(length(N)*length(H)));
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

vec3 BoxObj::getNormal(vec3 worldPos){
  vec3 center = vec3((min.x+max.x)/2,(min.y+max.y)/2,(min.z+max.z)/2);
  vec3 N = worldPos-center;
  if(abs(N.x) >= abs(N.y) && abs(N.x) >= abs(N.z))
    N = vec3(N.x,0,0);
  else if(abs(N.y) >= abs(N.x) && abs(N.y) >= abs(N.z))
    N = vec3(0,N.y,0);
  else if(abs(N.z) >= abs(N.y) && abs(N.z) >= abs(N.x))
    N = vec3(0,0,N.z);
  if(composite != mat4(1)){
    N = vec3(glm::transpose(composite)*vec4(N,0));
  }

  return N;
}

vec3 BoxObj::reflectedRay(vec3 ray, vec3 origin){
  vec3 normal = getNormal(origin);
  ray = normalize(ray);
  normal = normalize(normal);
  return normalize(ray - 2*(dot(ray,normal))*normal);
}

vec3 BoxObj::refractedRay(vec3 ray, vec3 origin, vec3 *offsetOrig, float *cos, float *r0){
  float n1, n2; //indicies of refraction
  vec3 normal = getNormal(origin);
  ray = normalize(ray);
  normal = normalize(normal);
  //into obj out of air
  if(dot(ray,normal) < 0){
    n1 = 1.0f;
    n2 = ior;
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
    *offsetOrig = origin + normal*epsilon; //set offset origin
    return ray - 2*-(*cos)*normal; //reflection vector
  }

  *offsetOrig = origin - normal*.01f; //set offset origin
  return normalize((nRatio*ray)+(((nRatio*(*cos))-sqrt(disc))*normal));
}

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
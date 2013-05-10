#include "raytrace.h"

int main(int argc, char* argv[]){
  //program run timers
  clock_t t1, t2;
  //start timer
  t1 = clock();

  //initialize scene objects
  totalSize = 0; //number of objects
  camera = new Camera(); //camera
  light = new Light(); //light

  //initialize file variables
  bool fileAvail = false; //check for file option

  int next; //which argv to reference in strncpy
  bool error = false; //print error or not
  if(argc > 1){
    //argument checks
    if(argc > 5){
      cout << "Too many arguments. Exiting program." << endl;
      return 0;
    }

    //check for shading flag
    if(argv[argc-1][0] == '-' || argv[argc-1][0] == '.'){
      cout << "Shading not specified. Using Phong." << endl;
      shade = 0;
    }
    else{
      shade = strtod(argv[argc-1],NULL);
      //make sure it's a valid option
      if(shade > 1 || shade < 0){
        cout << "Invalid shading option. Using Phong." << endl;
        shade = 0;
      }
    }

    //look for image flag
    for(int i = 0; i < argc; i++){
      //image name
      if(!fileAvail && argv[i][0] == '-' && argv[i][1] == 'I'){
        int minusLength;
        fileAvail = true;
        char* point; //points to start of file name
        if(strlen(argv[i]) == 2){ //if file option is "-I <file>"
          point = argv[i+1];
          minusLength = 0;
          next = 1;
        }
        else { //file option is "-I<file>"
          point = argv[i]+2;
          minusLength = 2;
          next = 0;
        } 

        //check safe malloc return and assign file name
        if((filename = (char*)malloc(sizeof(char*)*strlen(argv[i+next]))) != NULL){
          strncpy(filename,point,strlen(argv[i+next])-minusLength); //set file name
        }
        else cout << "Could not allocate memory for file name" << endl;
      }
    }
    //missing dimension argument
    if(argc == 3 && !strcmp(argv[0],"-I")){
      cout << "Missing dimension. Exiting program." << endl;
      return 0;
    }
    //get dimensions
    else if(argc == 3 && !fileAvail){
      imageWidth = strtod(argv[1],NULL);
      imageHeight = strtod(argv[2],NULL);
    }
    if(argc > 2 && fileAvail){ //all options are there
      imageWidth = strtod(argv[1],NULL);
      imageHeight = strtod(argv[2],NULL);
    }
    //no dimensions/bad dimensions
    else if(argc == 2){
      if(fileAvail){ //no dimensions
        cout << "No dimensions found. Using default." << endl;
        imageWidth = 640;
        imageHeight = 480;
      }
      else{ //bad dimensions
        cout << "Bad dimensions. Using default." << endl;
        imageWidth = 640;
        imageHeight = 480;
      }
    }
  }
  //no options chosen
  else{
    cout << "No options chosen. Using default." << endl;
    error = true;
    filename = (char*)"simple.pov";
    imageWidth = 640;
    imageHeight = 480;
  }

  //in case something was missed
  if(imageWidth == 0 || imageHeight == 0){
    imageWidth = 640;
    imageHeight = 480;
  }

  //default case if dimensions, but no file option
  if(!fileAvail && !error){
    cout << "No filename found. Using default." << endl;
    filename = (char*)"simple.pov";
  }

  //try opening file
  infile.open(filename,ifstream::in);
  if(infile.is_open())
    cout << "Successfully opened file " << filename << " for reading" << endl;
  else {
    cout << "Could not open file " << filename;
    cout << ". Exiting program." << endl;
    return 0;
  }

  //holds next string in file
  char* nextString;
  if((nextString = (char*)malloc(150)) == NULL){
    cout << "Could not allocate memory for next string" << endl;
  }

  while(!infile.eof()){
    infile >> nextString; //get object type

    //check if comment
    if(nextString[0] == '/'){
      infile.getline(nextString,150); //ignore line
    }
    //check if camera
    else if(!strcmp(nextString,"camera")){
      camera->parse(infile);
    }
    //check if light
    else if(!strcmp(nextString,"light_source")){
      light = new Light();
      light->parse(infile);
      lightList.push_back(light);
    }
    //check if plane
    else if(!strcmp(nextString,"plane")){
      plane = new PlaneObj(1);
      plane->parse(infile);
      objList.push_back(plane);
      totalSize++;
    }
    //check if sphere
    else if(!strcmp(nextString,"sphere")){
      sphere = new SphereObj(2);
      sphere->parse(infile);
      objList.push_back(sphere);
      totalSize++;
    }
    //check if cone
    else if(!strcmp(nextString,"cone")){
      cone = new ConeObj(3);
      cone->parse(infile);
      objList.push_back(cone);
      totalSize++;
    }
    //check if box
    else if(!strcmp(nextString,"box")){
      box = new BoxObj(4);
      box->parse(infile);
      objList.push_back(box);
      totalSize++;
    }
    //check if triangle
    else if(!strcmp(nextString,"triangle")){
      tri = new TriObj(5);
      tri->parse(infile);
      objList.push_back(tri);
      totalSize++;
    }
  }
  cout << "File parsing complete." << endl;
  infile.close(); //close file

  //demo purposes
  cout << "Number of lights in the scene: " << lightList.size() << endl;
  cout << "Number of objects in the scene: " << totalSize << endl;

  /**************Image Processing*******************/
  //create image object
  //Image img(imageWidth, imageHeight);
  img = new Image(imageWidth, imageHeight);

  //set camera space bounding box
  leftB = (-(float)imageWidth/imageHeight)/2.0f; //left of near plane
  rightB = ((float)imageWidth/imageHeight)/2.0f; //right of near plane
  topB = 1/1.5f; //top of near plane
  botB = -1/1.5f; //bottom of near plane

  //per pixel calculations
  cout << "Rendering image. This may take a while..." << endl;
  for(int x = 0; x < imageWidth; x++){ //x of image
    for(int y = 0; y < imageHeight; y++){ //y of image
      //print loading stuff (to do)
      //covert to camera space
      vec3 camSpace; //camera space coordinates
      camSpace.x = leftB+((rightB-leftB)*((x+0.5)/imageWidth));
      camSpace.y = botB+((topB-botB)*((y+0.5)/imageHeight));
      camSpace.z = -1;

      //convert to world space
      vec3 worldSpace; //world space coordinates
      worldSpace = camera->loc + (camSpace.x*camera->getRight())
        +(camSpace.y*camera->getUp())
        +(camSpace.z*cross(camera->getRight(),camera->getUp()));

      //create primary ray
      Ray primaryRay(camera->loc,worldSpace - primaryRay.orig);
      
      //set color of pixel
      recursionDepth = 6;
      //set background color
      background.r = 0; //black
      background.g = 0;
      background.b = 0;
      clr = raytrace(primaryRay);
      img->pixel(x,y,clr);
    }
  }

  // write the targa file to disk
  img->WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

  //free memory
  delete camera;
  delete light;
  delete plane;
  delete sphere;
  delete tri;
  delete cone;
  delete box;
  delete img;

  //end timer
  t2 = clock();
  //calculate run time
  float diff = (float)t2 - (float)t1;
  float seconds = diff / CLOCKS_PER_SEC;
  int minutes = 0;
  while(seconds-60 >= 0){
    minutes++;
    seconds -= 60;
  }
  printf("Program run time: %d minutes, %.2lf seconds\n",minutes,seconds);

  return 0;
}

float world_to_pixel_x(float height, float width, float x){
  float d = (width-1)/2;
  float c = d;

  return (c*x+d)*height/width; //adjust for scaling
}

float world_to_pixel_y(float height, float width, float y){
  float f = (height-1)/2;
  float e = f;

  return e*y+f;
}

color_t raytrace(Ray ray){
  color_t clr; //color to return
  float t = INT_MAX; //interpolation value
  float minDist = INT_MAX; //smallest distance
  int bestObj = -1; //closest object. -1 means no intersect
  float epsilon = 0.0001f; //self-avoidance offset

  recursionDepth--;
  if(recursionDepth >= 0){ //still more recursions to go
    //check primary ray against each object
    for(int index = 0; index < objList.size(); index++){
      //if intersect
      if(objList[index]->intersect(ray.dir,ray.orig,&t)){
        if(t > epsilon && t < minDist){ //check depth
          minDist = t; //update depth
          bestObj = index; //update closest object
        }
      }
    }

    //figure out what to draw, if anything
    color_t shadeColor; //light-based color contribution
    if(bestObj != -1){ //valid object
      //calculate point of intersection
      vec3 intersection;
      if(objList[bestObj]->objID == 5){
        intersection = objList[bestObj]->intersection;
      } 
      else intersection = ray.orig + minDist*ray.dir;
      
      //get base color
      //using rgb color
      if(objList[bestObj]->rgbColor != vec3(-1)){
        shadeColor.r = objList[bestObj]->rgbColor.x;
        shadeColor.g = objList[bestObj]->rgbColor.y;
        shadeColor.b = objList[bestObj]->rgbColor.z;
        shadeColor.f = 0.0f;
      }
      //using rgbf color
      else if(objList[bestObj]->rgbfColor != vec4(-1)){
        shadeColor.r = objList[bestObj]->rgbfColor.x;
        shadeColor.g = objList[bestObj]->rgbfColor.y;
        shadeColor.b = objList[bestObj]->rgbfColor.z;
        shadeColor.f = objList[bestObj]->rgbfColor[3];
      }
      //else invalid color
      else{
        cout << "Invalid color." << endl;
      }

      //reflection
      color_t reflColor; //reflection-based color contribution
      float reflection = objList[bestObj]->reflection; //reflection coeff
      if(reflection > 0.0f){ //the surface is reflective
        //calculate reflection vector
        Ray reflect(intersection,
          objList[bestObj]->reflectedRay(ray.dir,intersection));
        //recurse
        reflColor = raytrace(reflect); //recurse
      }
      else{ //no reflection
        reflColor = background;
      }

      //refraction
      color_t refrColor; //refraction-based color contribution
      float cos_theta = -1.0f; //Schlick cos(theta) term
      float R0 = -1.0f; //R0 for Schlick math
      vec3 offsetOrig = vec3(0); //origin offset based on ray
      float refraction = objList[bestObj]->refraction; //refraction coeff
      if(refraction > 0.0f){ //the surface is refractive
        //calculate refraction vector
        Ray refract(intersection,
          objList[bestObj]->refractedRay(
            ray.dir,intersection,&offsetOrig,&cos_theta,&R0));
        //update origin based on which way the ray went
        refract.orig = offsetOrig;
        //recurse
        refrColor = raytrace(refract);
      }
      else{ //no refraction
        refrColor = background;
      }

      //check for shadows
      Ray shadowRay(intersection,light->loc - intersection); //shadow vector
      float tShadow; //range check
      bool shadow = false; //no shadows

      //intersect shadow feeler with geometry
      for(int index = 0; index < objList.size(); index++){
        //if intersection
        if(objList[index]->intersect(shadowRay.dir,
          shadowRay.orig+(shadowRay.dir*epsilon),&tShadow)){
          shadow = true;
          break;
        }
      }
      if(!shadow){ //no shadows
        objList[bestObj]->shade(ray.dir,intersection,&shadeColor,*light,shade);
      }
      else{ //shadows
        //set to ambient color
        shadeColor.r = shadeColor.r*objList[bestObj]->ambient;
        shadeColor.g = shadeColor.g*objList[bestObj]->ambient;
        shadeColor.b = shadeColor.b*objList[bestObj]->ambient;
      }

      //Schlick's approximation
      /*float R; //reflectance term
      if(R0 == -1.0f || cos_theta == -1.0f){
        R = 1.0f;
      }
      else R = R0 + (1-R0)*pow(1-cos_theta,5);*/

      //update color with all values
      //Schlick
      /*clr.r = R*reflColor.r + (1-R)*refrColor.r;
      clr.g = R*reflColor.g + (1-R)*refrColor.g;
      clr.b = R*reflColor.b + (1-R)*refrColor.b;*/

      //local color
      clr.r = (1-reflection-shadeColor.f)*shadeColor.r;
      clr.g = (1-reflection-shadeColor.f)*shadeColor.g;
      clr.b = (1-reflection-shadeColor.f)*shadeColor.b;

      //reflection
      clr.r += reflection*reflColor.r;
      clr.g += reflection*reflColor.g;
      clr.b += reflection*reflColor.b;

      //refraction
      clr.r += shadeColor.f*refrColor.r;
      clr.g += shadeColor.f*refrColor.g;
      clr.b += shadeColor.f*refrColor.b;
    }
    else clr = background; //nothing to draw at that pixel
  }
  else clr = background; //nothing to draw at that pixel
  recursionDepth++;

  return clr;
}

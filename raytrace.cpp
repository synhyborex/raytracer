#include "raytrace.h"

int main(int argc, char* argv[]){
  //initialize scene objects
  totalSize = 0; //number of objects
  camera = new Camera(); //camera
  light = new Light(); //light
  plane = new PlaneObj(); //plane
  sphere = new SphereObj(); //sphere
  tri = new TriObj(); //triangle
  cone = new ConeObj(); //cone
  box = new BoxObj(); //box
  
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
      if(shade > 1){
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
    filename = "bunny_small.pov";
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
    filename = "bunny_small.pov";
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
  if((nextString = (char*)malloc(100)) == NULL){
    cout << "Could not allocate memory for next string" << endl;
  }

  while(!infile.eof()){
    infile >> nextString; //get object type

    //check if comment
    if(!strcmp(nextString,"//")){
      infile.getline(nextString,100,'\n'); //ignore line
    }
    //check if camera
    else if(!strcmp(nextString,"camera")){
      camera->parse(infile);
    }
    //check if light
    else if(!strcmp(nextString,"light_source")){
      light->parse(infile);
    }
    //check if plane
    else if(!strcmp(nextString,"plane")){
      plane->parse(infile);
      PlaneList.push_back(plane);
      totalSize++;
    }
    //check if sphere
    else if(!strcmp(nextString,"sphere")){
      sphere->parse(infile);
      SphereList.push_back(sphere);
      totalSize++;
    }
    //check if cone
    else if(!strcmp(nextString,"cone")){
      cone->parse(infile);
      ConeList.push_back(cone);
      totalSize++;
    }
    //check if box
    else if(!strcmp(nextString,"box")){
      box->parse(infile);
      BoxList.push_back(box);
      totalSize++;
    }
    //check if triangle
    else if(!strcmp(nextString,"triangle")){
      tri->parse(infile);
      TriList.push_back(tri);
      totalSize++;
    }
  }
  cout << "File parsing complete." << endl;

  //demo purposes
  cout << "Size of list: " << totalSize << endl;

  /**Image Processing**/
  //create image object
  Image img(imageWidth, imageHeight);

  //set camera space bounding box
  leftB = (-(float)imageWidth/imageHeight)/2.0f; //left of near plane
  rightB = ((float)imageWidth/imageHeight)/2.0f; //right of near plane
  topB = -1/1.5f; //top of near plane
  botB = 1/1.5f; //bottom of near plane

  //initialize depth buffer
  float depth[imageWidth][imageHeight];
  //float bestT[imageWidth][imageHeight];
  for (int i=0; i<imageWidth; i++){
    for (int j=0; j<imageHeight; j++){
      depth[i][j] = INT_MAX;
    }
  }

  //per pixel calculations
  for(int x = 0; x < imageWidth; x++){ //x of image
    for(int y = 0; y < imageHeight; y++){ //y of image 
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

      //create ray
      vec3 ray; //ray to cast
      ray = worldSpace - camera->loc;
      ray = normalize(ray);

      //per object calculations
      //box
      for(int size = 0; size < BoxList.size(); size++){
        //do nothing for now
      }
      //sphere
      for(int size = 0; size < SphereList.size(); size++){
        //if intersect
        if(SphereList[size]->intersect(ray,camera->loc,&t)){
          if(t < depth[x][y]){ //check depth
            depth[x][y] = t; //update depth
            //using rgb color
            if(SphereList[size]->rgbColor != vec3(-1)){
              clr.r = SphereList[size]->rgbColor.x;
              clr.g = SphereList[size]->rgbColor.y;
              clr.b = SphereList[size]->rgbColor.z;
            }
            //else using rgbf color
            else if(SphereList[size]->rgbfColor != vec3(-1)){
              clr.r = SphereList[size]->rgbfColor.x;
              clr.g = SphereList[size]->rgbfColor.y;
              clr.b = SphereList[size]->rgbfColor.z;
            }
            //else invalid color
            else{
              cout << "Invalid color." << endl;
            }
          }
          //set color
          img.pixel(x,y,clr);
        }
      }
      //cone
      for(int size = 0; size < ConeList.size(); size++){
        //do nothing for now
      }
      //plane
      for(int size = 0; size < PlaneList.size(); size++){
        //if intersect
        if(PlaneList[size]->intersect(ray,camera->loc,&t)){
          if(t < depth[x][y]){ //check depth
            depth[x][y] = t; //update depth
            //using rgb color
            if(PlaneList[size]->rgbColor != vec3(-1)){
              clr.r = PlaneList[size]->rgbColor.x;
              clr.g = PlaneList[size]->rgbColor.y;
              clr.b = PlaneList[size]->rgbColor.z;
            }
            //else using rgbf color
            else if(PlaneList[size]->rgbfColor != vec3(-1)){
              clr.r = PlaneList[size]->rgbfColor.x;
              clr.g = PlaneList[size]->rgbfColor.y;
              clr.b = PlaneList[size]->rgbfColor.z;
            }
            //else invalid color
            else{
              cout << "Invalid color." << endl;
            }
          }
          //set color
          img.pixel(x,y,clr);
        }
      }
      //triangle
      for(int size = 0; size < TriList.size(); size++){
        //do nothing for now
      }
    }
  }

  // write the targa file to disk
  img.WriteTga((char *)"awesome.tga", true); 
  // true to scale to max color, false to clamp to 1.0

  //free memory
  infile.close();
  delete camera;
  delete light;
  delete plane;
  delete sphere;
  delete tri;
  delete cone;
  delete box;

  return 0;
}

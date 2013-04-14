#include "raytrace.h"

int main(int argc, char* argv[]){
  /*GeomObj *s1 = new SphereObj();
  GeomObj *s2 = new SphereObj(5);
  GeomObj *c1 = new ConeObj(-4);
  GeomObj *c2 = new ConeObj();
  GeomObj *p1 = new PlaneObj(1);
  GeomObj *p2 = new PlaneObj();
  GeomObj *t1 = new TriObj(1);
  GeomObj *t2 = new TriObj();

  objectList.push_back(s1);
  objectList.push_back(s2);
  objectList.push_back(c1);
  objectList.push_back(p1);
  s1 = new SphereObj(1);
  objectList.push_back(s1);

  for(int i = 0; i < 5; i++){
    objectList[i]->printID();
  }

  vec3 bob = vec3(0,0,0);
  delete s1;
  delete s2;
  delete c1;*/

  //initialize scene objects
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
    if(argc > 4){
      cout << "Too many arguments. Exiting program." << endl;
      return 0;
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
    if(argc == 3 && fileAvail){
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

  //default case if dimensions, but no file option
  if(!fileAvail && !error){
    cout << "No filename found. Using default." << endl;
    filename = "bunny_small.pov";
  }

  //create image object
  Image img(imageWidth, imageHeight);

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
      objectList.push_back(plane);
    }
    //check if sphere
    else if(!strcmp(nextString,"sphere")){
      sphere->parse(infile);
      objectList.push_back(sphere);
    }
    //check if cone
    else if(!strcmp(nextString,"cone")){
      cone->parse(infile);
      objectList.push_back(cone);
    }
    //check if box
    else if(!strcmp(nextString,"box")){
      box->parse(infile);
      objectList.push_back(box);
    }
    //check if triangle
    else if(!strcmp(nextString,"triangle")){
      tri->parse(infile);
      objectList.push_back(tri);
    }
  }
  cout << "File parsing complete." << endl;

  //demo purposes
  //cout << "size of list: " << objectList.size() << endl;

  //image processing

  //image variables
  float convLoc[3]; //coverted location
  color_t clr; //color
  float max_x, max_y, min_x, min_y; //bounding box

  //convert locations for each object
  for(int list = 0; list < objectList.size(); list++){
    if(objectList->objID == 0)

    convLoc[0] = world_to_pixel_x(imageHeight, imageWidth, convLoc[0]);
    convLoc[1] = world_to_pixel_y(imageHeight, imageWidth, convLoc[1]);
    convLoc[2] *= -1;
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
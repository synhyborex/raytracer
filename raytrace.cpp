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

  //filename type
  if(strstr(filename,(char*)".pov") != NULL)
    useRaster = false;
  else if(strstr(filename,(char*)".m") != NULL)
    useRaster = true;

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

  if(!useRaster){
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
        plane = new PlaneObj(PLANE);
        plane->parse(infile);
        planeList.push_back(plane);
        totalSize++;
      }
      //check if sphere
      else if(!strcmp(nextString,"sphere")){
        sphere = new SphereObj(SPHERE);
        sphere->parse(infile);
        objList.push_back(sphere);
        totalSize++;
      }
      //check if cone
      else if(!strcmp(nextString,"cone")){
        cone = new ConeObj(CONE);
        cone->parse(infile);
        objList.push_back(cone);
        totalSize++;
      }
      //check if box
      else if(!strcmp(nextString,"box")){
        box = new BoxObj(BOX);
        box->parse(infile);
        objList.push_back(box);
        totalSize++;
      }
      //check if triangle
      else if(!strcmp(nextString,"triangle")){
        tri = new TriObj(TRIANGLE);
        tri->parse(infile);
        objList.push_back(tri);
        totalSize++;
      }
    }
    cout << "File parsing complete." << endl;

    //demo purposes
    cout << "Number of lights in the scene: " << lightList.size() << endl;
    cout << "Number of objects in the scene: " << totalSize << endl;
  }
  infile.close(); //close file

  /**************Image Processing*******************/
  //create image object
  img = new Image(imageWidth, imageHeight);
  if(!useRaster){ //raytrace object
    bvh = new BVH_Node(objList,0);
    //bvh->printTree(bvh);

    //set camera space bounding box
    leftB = (-(float)imageWidth/imageHeight)/2.0f; //left of near plane
    rightB = ((float)imageWidth/imageHeight)/2.0f; //right of near plane
    topB = 1/1.5f; //top of near plane
    botB = -1/1.5f; //bottom of near plane

    //per pixel calculations
    cout << "Rendering image. This may take a while..." << endl;
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

        //create primary ray
        Ray primaryRay(camera->loc,worldSpace - camera->loc);
        
        //set recursion depth
        recursionDepth = 6;
        //set background color
        background.r = 0.0f; //gray
        background.g = 0.0f;
        background.b = 0.0f;
        usebvh = true;
        clr = raytrace(primaryRay,usebvh,6,1);
        img->pixel(x,y,clr);
      }
    }
  }
  else{ //rasterize object
    InitGeom(filename);

    // holds a triangle's 3 vertices' x, y, z
    float arr[3][3];
    int size = -1;  //used to detect TheMesh->GetVertex error

    //initialize depth buffer
    float depth[imageWidth][imageHeight];
    for (int i=0; i<imageWidth; i++){
      for (int j=0; j<imageHeight; j++){
        depth[i][j] = INT_MAX;
      }
    }

    while(++size > -1){
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          arr[j][i] = TheMesh->GetVertex(i, j, size);
          if(arr[j][i] == -2){  //getVertex returned in error
            size = -2;
          }
        }
      }

      if(size == -2){
        break;
      }

      arr[0][0] = world_to_pixel_x(imageHeight, imageWidth, arr[0][0]);
      arr[1][0] = world_to_pixel_y(imageHeight, imageWidth, arr[1][0]);
      arr[2][0] *= -1;

      arr[0][1] = world_to_pixel_x(imageHeight, imageWidth, arr[0][1]);
      arr[1][1] = world_to_pixel_y(imageHeight, imageWidth, arr[1][1]);
      arr[2][1] *= -1;

      arr[0][2] = world_to_pixel_x(imageHeight, imageWidth, arr[0][2]);
      arr[1][2] = world_to_pixel_y(imageHeight, imageWidth, arr[1][2]);
      arr[2][2] *= -1;
        
      // make a color
      color_t clr_a, clr_b, clr_c;

      clr_a.r = TheMesh->Triangles[size].Color.Red;
      clr_a.g = TheMesh->Triangles[size].Color.Green;
      clr_a.b = TheMesh->Triangles[size].Color.Blue;

      clr_b.r = TheMesh->Triangles[size].Color.Red;
      clr_b.g = TheMesh->Triangles[size].Color.Green;
      clr_b.b = TheMesh->Triangles[size].Color.Blue;
        
      clr_c.r = TheMesh->Triangles[size].Color.Red;
      clr_c.g = TheMesh->Triangles[size].Color.Green;
      clr_c.b = TheMesh->Triangles[size].Color.Blue;

      // set a square to be the color above

      //set bounding box
      float max_x = std::max(arr[0][0], arr[0][1]);
      max_x = std::max(max_x, arr[0][2]);
      float max_y = std::max(arr[1][0], arr[1][1]);
      max_y = std::max(max_y, arr[1][2]);
      float min_x = std::min(arr[0][0], arr[0][1]);
      min_x = std::min(min_x, arr[0][2]);
      float min_y = std::min(arr[1][0], arr[1][1]);
      min_y = std::min(min_y, arr[1][2]);
        
      for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
          float beta = getBeta(i, j, arr);
          float area = getArea(i, j, arr);
          beta /= area;
          float gamma = getGamma(i, j, arr);
          gamma /= area;
          float alpha = 1.0 - beta - gamma;
          if (beta <= 1 && beta >= 0){
            if (gamma <= 1 && gamma >= 0){
              if (alpha <= 1 && alpha >= 0){
                float curZ = alpha*arr[2][0] + beta*arr[2][1] + gamma*arr[2][2];
                if(depth[i][j] > curZ){
                  color_t clr;
                  clr.r = alpha*clr_a.r + beta*clr_b.r + gamma*clr_c.r;
                  clr.r *= (1-curZ)/2; //adjusted for proper shading

                  clr.g = alpha*clr_a.g + beta*clr_b.g + gamma*clr_c.g;
                  clr.g *= (1-curZ)/2;

                  clr.b = alpha*clr_a.b + beta*clr_b.b + gamma*clr_c.b;
                  clr.b *= (1-curZ)/2;

                  img->pixel(i, j, clr);
                  depth[i][j] = curZ;
                }
              }
            }
          }
        }
      }
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
  delete bvh;

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
  printf("Image rendered in %d minutes and %.2lf seconds\n",minutes,seconds);

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

void sampleDisk(float u1, float u2, float* Dx, float* Dy){
  float r = sqrt(u1);
  float theta = 2.0f*M_PI*u2;
  *Dx = r*cosf(theta);
  *Dy = r*sinf(theta);
}

vec3 diskToHemisphere(float u1, float u2){
  float r = sqrt(1-u1);
  float theta = 2 * M_PI * u2;

  float x = r * cosf(theta);
  float y = r * sinf(theta);

  return vec3(x, y, sqrt(u1));
}

color_t raytrace(Ray ray, bool usebvh, int recursionDepth, int GIdepth){
  color_t clr; //color to return
  float t = INT_MAX; //bvh interpolation value
  float p = INT_MAX; //plane list interp value
  float minDist = INT_MAX; //smallest distance
  BVH_Node bestNode; //closest node
  GeomObj* traceObj = NULL;

  if(recursionDepth >= 0){ //still more recursions to go
    //check primary ray against BVH
    if(usebvh){ //use bvh
      if(bvh->intersect(bvh,ray.dir,ray.orig,&bestNode,&t)){
        if(t > epsilon && t < minDist){ //check depth
          minDist = t; //update depth
          traceObj = bestNode.obj; //update closest object
        }
      }
    }
    else{ //don't use bvh
      for(int index = 0; index < objList.size(); index++){
        //if intersect
        if(objList[index]->intersect(ray.dir,ray.orig,&t)){
          if(t > epsilon && t < minDist){ //check depth
            minDist = t; //update depth
            traceObj = objList[index]; //update closest object
          }
        }
      }
    }
    //go over planes
    for(int index = 0; index < planeList.size(); index++){
      //if intersect
      if(planeList[index]->intersect(ray.dir,ray.orig,&p)){
        if(p > epsilon && p < minDist){ //check depth
          minDist = p; //update depth
          traceObj = planeList[index]; //update closest object
        }
      }
    }

    //figure out what to draw, if anything
    color_t shadeColor = background; //light-based color contribution
    if(traceObj != NULL){ //valid object
      //object space intersection point
      vec3 intersection = traceObj->intersection;
      //world space intersection point
      vec3 worldPos = ray.orig + minDist*ray.dir;
      if(traceObj->objID == TRIANGLE){
        worldPos = vec3(inverse(traceObj->composite)*vec4(worldPos,1));
        //worldPos = traceObj->intersection;
      }

      //Monte Carlo recursion
      color_t GIcolor = background; //total indirect lighting
      //GIdepth = 0;
      if(GIdepth > 0){
        int n = 256;
        for(int i = 0; i < n; i++){
          float dx, dy;
          float u1 = rand()/RAND_MAX, u2 = rand()/RAND_MAX;
          sampleDisk(u1,u2,&dx,&dy);
          vec3 hDir = diskToHemisphere(dx,dy); //direction of ray in hemisphere
          //rotate ray
          vec3 norm = traceObj->getNormal(intersection); //object normal
          float angle = acosf(dot(hDir,norm)); //angle of rotation
          vec3 axis = cross(hDir,norm); //axis of rotation
          vec3 hDirRot = hDir*cosf(angle)+ (cross(axis,hDir))*sinf(angle)
            + axis*(dot(axis,hDir))*(1-cosf(angle));
          //create ray and recurse
          Ray monteCarlo(worldPos,hDirRot); //the ray to recurse with
          color_t catchCol = raytrace(monteCarlo,usebvh,recursionDepth,GIdepth-1);
          catchCol /= (float)n;
          //catchCol /= minDist;
          GIcolor += catchCol;
          //GIcolor += raytrace(monteCarlo,usebvh,recursionDepth,GIdepth-1);
          //GIcolor /= n;
          //cout << GIcolor.r << " " << GIcolor.g << " " << GIcolor.b << endl;
        }
        //GIcolor /= ((float)n)*minDist;;
      }
      
      //get base color
      //using rgb color
      if(traceObj->rgbColor != vec3(-1)){
        shadeColor.r = traceObj->rgbColor.x;
        shadeColor.g = traceObj->rgbColor.y;
        shadeColor.b = traceObj->rgbColor.z;
        shadeColor.f = 0.0f;
      }
      //using rgbf color
      else if(traceObj->rgbfColor != vec4(-1)){
        shadeColor.r = traceObj->rgbfColor.x;
        shadeColor.g = traceObj->rgbfColor.y;
        shadeColor.b = traceObj->rgbfColor.z;
        shadeColor.f = traceObj->rgbfColor[3];
      }
      //else invalid color
      else{
        cout << "Invalid color." << endl;
      }

      //reflection
      color_t reflColor; //reflection-based color contribution
      float reflection = traceObj->reflection; //reflection coeff
      if(reflection > 0.0f){ //the surface is reflective
        //calculate reflection vector
        Ray reflect(worldPos,
          traceObj->reflectedRay(ray.dir,intersection));
        //recurse
        reflColor = raytrace(reflect,usebvh,recursionDepth-1,GIdepth); //recurse
      }
      else{ //no reflection
        reflColor = background;
      }

      //refraction
      color_t refrColor; //refraction-based color contribution
      float cos_theta = -1.0f; //Schlick cos(theta) term
      float R0 = -1.0f; //R0 for Schlick math
      vec3 offsetOrig = vec3(0); //origin offset based on ray
      float refraction = traceObj->refraction; //refraction coeff
      if(refraction > 0.0f){ //the surface is refractive
        //calculate refraction vector
        Ray refract(worldPos,
          traceObj->refractedRay(
            ray.dir,intersection,&offsetOrig,&cos_theta,&R0));
        //update origin based on which way the ray went
        refract.orig = offsetOrig;
        //recurse
        refrColor = raytrace(refract,usebvh,recursionDepth-1,GIdepth);
      }
      else{ //no refraction
        refrColor = background;
      }

      //multiple lights
      /**in progress**/
      for(int lightIdx = 0; lightIdx < lightList.size(); lightIdx++){
        //check for shadows
        Ray shadowRay(worldPos,
          lightList[lightIdx]->loc - intersection); //shadow vector
        float tShadow = -INT_MAX; //range check
        bool shadow = false; //no shadows
        BVH_Node shadowNode;

        //intersect shadow feeler with geometry
        //shadeColor = background;
        if(usebvh){ //use bvh
          if(bvh->intersect(bvh,shadowRay.dir,shadowRay.orig
            +(shadowRay.dir*epsilon),&shadowNode,&tShadow)){
            shadow = true;
          }
        }
        else{ //don't use bvh
          for(int index = 0; index < objList.size(); index++){
            //if intersection
            if(objList[index]->intersect(shadowRay.dir,
              shadowRay.orig+(shadowRay.dir*epsilon),&tShadow)){
              shadow = true;
              break;
            }
          }
        }
        //go over planes
        for(int index = 0; index < planeList.size(); index++){
          //if intersection
          if(planeList[index]->intersect(shadowRay.dir,
            shadowRay.orig+(shadowRay.dir*epsilon),&tShadow)){
            shadow = true;
            break;
          }
        }
        if(!shadow){ //no shadows
          if(lightList.size() > 1)
            shadeColor += 
              traceObj->shade(ray.dir,intersection,shadeColor,*light,shade);
          else shadeColor = 
            traceObj->shade(ray.dir,intersection,shadeColor,*light,shade);
        }
        else{ //shadows
          //set to ambient color
          shadeColor = GIcolor;
        } 
      }

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

      //global illumination
      clr.r += GIcolor.r;
      clr.g += GIcolor.g;
      clr.b += GIcolor.b;

      if(GIdepth == 0)
        clr /= minDist;
    }
    else clr = background; //nothing to draw at that pixel
  }
  else clr = background; //nothing to draw at that pixel

  return clr;
}

/***RASTERIZER STUFF***/
/* code to parse through a .m file and write the data into a mesh */
int loadASCIIMesh(std::string const & fileName, CMesh *Mesh) {
    std::ifstream File;
    File.open(fileName.c_str());

    if (! File.is_open())
    {
        std::cerr << "Unable to open mesh file: " << fileName << std::endl;
        return 0;
    }

    //CMesh * Mesh = new CMesh();

    while (File)
    {
        std::string ReadString;
        std::getline(File, ReadString);

        std::stringstream Stream(ReadString);

        std::string Label;
        Stream >> Label;

        if (Label.find("#") != std::string::npos)
        {
            // Comment, skip
            continue;
        }

        if ("Vertex" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            SVector3 Position;
            Stream >> Position.X;
            Stream >> Position.Y;
            Stream >> Position.Z;

            SVertex Vertex;
            Vertex.Position = Position;

            Mesh->Vertices.push_back(Vertex);
        }
        else if ("Face" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            int Vertex1, Vertex2, Vertex3;
            Stream >> Vertex1;
            Stream >> Vertex2;
            Stream >> Vertex3;

            CMesh::STriangle Triangle;
            Triangle.VertexIndex1 = Vertex1 - 1;
            Triangle.VertexIndex2 = Vertex2 - 1;
            Triangle.VertexIndex3 = Vertex3 - 1;

            size_t Location;
            if ((Location = ReadString.find("{")) != std::string::npos) // there is a color
            {
                Location = ReadString.find("rgb=(");
                Location += 5; // rgb=( is 5 characters

                ReadString = ReadString.substr(Location);
                std::stringstream Stream(ReadString);
                float Color;
                Stream >> Color;
                Triangle.Color.Red = Color;
                Stream >> Color;
                Triangle.Color.Green = Color;
                Stream >> Color;
                Triangle.Color.Blue = Color;
            }

            Mesh->Triangles.push_back(Triangle);
        }
        else if ("" == Label)
        {
            // Just a new line, carry on...
        }
        else if ("Corner" == Label)
        {
            // We're not doing any normal calculations... (oops!)
        }
        else
        {
            std::cerr << "While parsing ASCII mesh: Expected 'Vertex' or 'Face' label, found '" << Label << "'." << std::endl;
        }
    }

    if (! Mesh->Triangles.size() || ! Mesh->Vertices.size())
    {
        delete Mesh;
        return 0;
    }

    return 1;
}

/* Just an example of how to iterate over the mesh triangles */
void CMesh::PrintMesh() {
    for(unsigned int j = 0; j < Triangles.size(); j++)
    {
        SVertex Vertex;
        cout << "New Vertices from triangle " << j << endl;
        Vertex = Vertices[Triangles[j].VertexIndex1];
        cout << "V1 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
        Vertex = Vertices[Triangles[j].VertexIndex2];
        cout << "V2 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
        Vertex = Vertices[Triangles[j].VertexIndex3];
        cout << "V3 " << Vertex.Position.X << " " << Vertex.Position.Y << " " << Vertex.Position.Z << endl;
    }
}

/* center the mesh */
void CMesh::centerMeshByExtents(SVector3 const & CenterLocation) {
  
    if (Vertices.size() < 2)
        return;

    SVector3 Min, Max;
    {
        std::vector<SVertex>::const_iterator it = Vertices.begin();
        Min = it->Position;
        Max = it->Position;
        for (; it != Vertices.end(); ++ it)
        {
            if (Min.X > it->Position.X)
                Min.X = it->Position.X;
            if (Min.Y > it->Position.Y)
                Min.Y = it->Position.Y;
            if (Min.Z > it->Position.Z)
                Min.Z = it->Position.Z;

            if (Max.X < it->Position.X)
                Max.X = it->Position.X;
            if (Max.Y < it->Position.Y)
                Max.Y = it->Position.Y;
            if (Max.Z < it->Position.Z)
                Max.Z = it->Position.Z;
        }
    }

    SVector3 Center = (Max + Min) / 2;

    SVector3 VertexOffset = CenterLocation - Center;
    for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
        it->Position += VertexOffset;
}

/* resize the mesh */
void CMesh::resizeMesh(SVector3 const & Scale)
{
    if (Vertices.size() < 2)
        return;

    SVector3 Min, Max;
    {
        std::vector<SVertex>::const_iterator it = Vertices.begin();
        Min = it->Position;
        Max = it->Position;
        for (; it != Vertices.end(); ++ it)
        {
            if (Min.X > it->Position.X)
                Min.X = it->Position.X;
            if (Min.Y > it->Position.Y)
                Min.Y = it->Position.Y;
            if (Min.Z > it->Position.Z)
                Min.Z = it->Position.Z;

            if (Max.X < it->Position.X)
                Max.X = it->Position.X;
            if (Max.Y < it->Position.Y)
                Max.Y = it->Position.Y;
            if (Max.Z < it->Position.Z)
                Max.Z = it->Position.Z;
        }
    }

    SVector3 Extent = (Max - Min);
    SVector3 Resize = Scale / std::max(Extent.X, std::max(Extent.Y, Extent.Z));
    for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
        it->Position *= Resize;
}

float CMesh::GetVertex(int i, int j, unsigned int size){
  if(size < Triangles.size())
  {
    SVertex Vertex;
    if(i == 0){
      Vertex = Vertices[Triangles[size].VertexIndex1];

      if(j == 0){
            return Vertex.Position.X;
        }
        else if(j == 1){
            return Vertex.Position.Y;
        }
        else if(j == 2){
        return Vertex.Position.Z;
      }
    }
    else if(i == 1){
        Vertex = Vertices[Triangles[size].VertexIndex2];
        
        if(j == 0){
            return Vertex.Position.X;
        }
        else if(j == 1){
            return Vertex.Position.Y;
      }
      else if(j == 2){
        return Vertex.Position.Z;
      }
    }
    else if(i == 2){
        Vertex = Vertices[Triangles[size].VertexIndex3];
        
      if(j == 0){
            return Vertex.Position.X;
        }
      else if(j == 1){
        return Vertex.Position.Y;
      }
      else if(j == 2){
        return Vertex.Position.Z;
      }
    }
  }

  return -2;
}

/* initialize the geometry 
   Change file name to load a different mesh file
*/
void InitGeom(char* modelName){
  TheMesh = new CMesh();
  std::string model = std::string(modelName);
  assert(loadASCIIMesh(model, TheMesh));
  TheMesh->resizeMesh(SVector3(1));
  TheMesh->centerMeshByExtents(SVector3(0));
}

float getBeta(float x, float y, float arr[3][3]){
  float beta = arr[0][0] - arr[0][2];
  beta *= y - arr[1][2];
  float temp = x - arr[0][2];
  temp *= arr[1][0] - arr[1][2];
  beta -= temp;
  beta *= 0.5;
  return beta;
}

float getArea(float x, float y, float arr[3][3]){
  float area = arr[0][2] - arr[0][0];
  area *= arr[1][1] - arr[1][0];
  float temp = arr[0][1] - arr[0][0];
  temp *= arr[1][2] - arr[1][0];
  area -= temp;
  area *= 0.5;
  if (area < 0) area *= -1;
  return area;
}

float getGamma(float x, float y, float arr[3][3]){
  float gamma = arr[0][1] - arr[0][0];
  gamma *= y - arr[1][0];
  float temp = x - arr[0][0];
  temp *= arr[1][1] - arr[1][0];
  gamma -= temp;
  gamma *= 0.5;
  return gamma;
}
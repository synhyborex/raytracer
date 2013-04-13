#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "../glm/gtc/type_ptr.hpp" //value_ptr
#include <fstream>

using namespace std;
using namespace glm;

class WorldObj{
  public:
    WorldObj();
    ~WorldObj();
    virtual void parse(ifstream&) =0;
    vec3 loc; //location
};
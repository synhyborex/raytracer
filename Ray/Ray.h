#pragma once

#include <stdio.h>
#include <vector>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "../glm/gtc/type_ptr.hpp" //value_ptr

using namespace glm;

class Ray{
  public:
    Ray();
    Ray(vec3,vec3);
    ~Ray();
    vec3 dir; //direction of ray
    vec3 orig; //ray origin
};
#include "WorldObj.h"

class Camera: public WorldObj{
  public:
    Camera();
    ~Camera();
    virtual void parse(ifstream&);
    vec3 getUp();
    void setUp(vec3);
    vec3 getRight();
    void setRight(vec3);
    vec3 getLook();
    void setLook(vec3);

  private:
    vec3 up;
    vec3 right;
    vec3 lookAt;
};
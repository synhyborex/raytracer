#include "WorldObj.h"

class Light: public WorldObj{
  public:
    Light();
    ~Light();
    virtual void parse(ifstream&);
    vec3 getRGBColor();
    void setRGBColor(vec3);
    vec4 getRGBFColor();
    void setRGBFColor(vec4);

  private:
    vec3 rgbColor; //rgb color
    vec4 rgbfColor; //rgbf color
};
#ifndef __TYPES_H__
#define __TYPES_H__

/* Color struct */
struct color_t {
  double r;
  double g;
  double b;
  double f; // "filter" or "alpha"

  color_t& operator+=(const color_t& a){
    r = r + a.r;
    g = g + a.g;
    b = b + a.b;
    f = f + a.f;
    return *this;
  }

  color_t& operator/=(const double& a){
    r = r / a;
    g = g / a;
    b = b / a;
    f = f / a;
    return *this;
  }

  color_t& operator=(const double& a){
    r = a;
    g = a;
    b = a;
    f = a;
    return *this;
  }
};

#endif

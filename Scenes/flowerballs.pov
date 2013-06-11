// cs174, assignment 1 sample file (RIGHT HANDED)
// petals periwinkle/ stem forest green/ center robin's egg blue
// ground goldenrod/ sky gray

camera {
  location  <0, 0, 10>
  up        <0, 1, 0>
  right     <1.33333, 0, 0>
  look-at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

//ground
plane {<0, 1, 0>, -4
      pigment {color rgb <0.855, 0.647, 0.125>}
      finish {ambient 0.4 diffuse 0.8 reflection 0.6}
}

//stem
triangle {
     <-0.5,-1 ,0 >,
     <-0.5, -4,0 >,
     <0.5,-4 ,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
}

triangle {
     <0.5,-1,0 >,
     <-0.5,-1,0 >,
     <0.5,-4,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
}

//center
sphere { <0, 0.5, -0.1>, 0.75
  pigment { color rgb <0.0, 0.8, 0.8>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.01 reflection 0.5}
}

//petals
//left side
sphere { <-0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

sphere { <-1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

sphere { <-0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

//right side
sphere { <0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

sphere { <1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

sphere { <0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <0.8, 0.8, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
}

//walls
// left wall
plane {<.707, 0, .707>, -8 
pigment {color rgb <0.8, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2}  }

// back wall
plane {<-.707, 0, -.707>, 30  
pigment {color rgb <0.8, 0.4, 0.2>}
finish {ambient 0.4 diffuse 0.2 reflection 0.2} }

// back wall on the right
plane {<-.34, 0, -.94>, 30  
pigment {color rgb <0.0, 0.2, 0.2>}
finish {ambient 0.4 diffuse 0.8 reflection 0.2} }


// random balls
sphere { <4.5, 2, -1>, 2
pigment {color rgbf <1.0, 1.0, 1.0, 0.8>}
finish {ambient 0.2 diffuse 0.8 refraction 1.0 ior 1.333}
}

sphere { <3.5, -1.5, -3.5>, 2
pigment {color rgb <1.0, 1.0, 1.0>}
finish {ambient 0.2 diffuse 0.8 specular 1.0 roughness 0.01 reflection 1.0}
}
// cs174, assignment 1 sample file (RIGHT HANDED)
// petals periwinkle/ stem forest green/ center robin's egg blue
// ground goldenrod/ sky gray

camera {
  location  <15, 6, 30>
  up        <0, 1, 0>
  right     <1.33333, 0, 0>
  look-at   <15, 0, 0>
}

light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

//ground
plane {<0, 1, 0>, -4
  pigment {color rgb <0, 1, 0.15>}
  finish {ambient 0.4 diffuse 0.8 reflection 0.2}
}

//box cross
box { <-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>
  pigment { color rgb <0.45, 0.69, 0.69>}
  finish {ambient 0.1 diffuse 0.4}
  scale <10, 3.5, 3.5>
  rotate <45, 0, 0>
  rotate <0, 0, 10.5>
  translate <20, 5, -10>
}

box { <-0.5, -0.5, -0.5>, <0.5, 0.5, 0.5>
  pigment { color rgb <0.078, 0.8, 0.8>}
  finish {ambient 0.1 diffuse 0.4}
  scale <3.5, 3.5, 10>
  rotate <45, 0, 0>
  rotate <0, 0, 10.5>
  translate <20, 5, -10>
}

//BLUE FLOWER
//stem
triangle {
     <-0.5,-1-1,0 >,
     <-0.5,-4-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
}

triangle {
     <0.5,-1-1,0 >,
     <-0.5,-1-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
}

//center
sphere { <0, 0.5, -0.1>, 0.75
  pigment { color rgb <0.0, 0.8, 0.8>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.01}
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

//RED FLOWER
//stem
triangle {
     <-0.5,-1-1,0 >,
     <-0.5,-4-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
     translate <15,0,-5>
}

triangle {
     <0.5,-1-1,0 >,
     <-0.5,-1-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
     translate <15,0,-5>
}

//center
sphere { <0, 0.5, -0.1>, 0.75
  pigment { color rgb <1.0, 0.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.01}
  translate <15,0,-5>
}

//petals
//left side
sphere { <-0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

sphere { <-1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

sphere { <-0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

//right side
sphere { <0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

sphere { <1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

sphere { <0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.25 roughness 0.7}
  translate <15,0,-5>
}

//YELLOW FLOWER
//stem
triangle {
     <-0.5,-1-1,0 >,
     <-0.5,-4-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
     translate <21,0,6.5>
}

triangle {
     <0.5,-1-1,0 >,
     <-0.5,-1-1,0 >,
     <0.5,-4-1,0 >
     pigment {color rgb <0.133, 0.525, 0.133>}
     finish {ambient 0.3 diffuse 0.4 specular 0.4 roughness 0.5 reflection 0.2}
     translate <21,0,6.5>
}

//center
sphere { <0, 0.5, -0.1>, 0.75
  pigment { color rgb <1.0, 1.0, 0.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.1 roughness 0.01}
  translate <21,0,6.5>
}

//petals
//left side
sphere { <-0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}

sphere { <-1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}

sphere { <-0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}

//right side
sphere { <0.6, -0.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}

sphere { <1.2, 0.5, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}

sphere { <0.6, 1.6, -0.1>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4}
  translate <21,0,6.5>
}
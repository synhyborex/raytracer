// Cornell Box
// Adapted from original
// Author: Ryan Schmitt

camera {
  location  <0, 5, 15.5>
  up        <0,  1,  0>
  right     <1, 0,  0>
  look_at   <0, 5, 0>
}

//light_source {<0, 5, 15> color rgb <0.1, 0.1, 0.1>}
light_source {<0, 9.5, 0> color rgb <1.0, 1.0, 1.0>}


// THE ROOM
//the sphere
sphere { <3, -1, 4>, 1
  pigment { color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
}

// floor @ y=0
triangle { <-5,0,5>, <5,0,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-5,0,5>, <5,0,5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}

// right wall
triangle { <5,0,5>, <5,10,5>, <5,0,-5>
   pigment { color rgb <1,0,0> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,10,5>, <5,10,-5>, <5,0,-5>
   pigment { color rgb <1,0,0> }
   finish { ambient 0 diffuse 0.5 }
}

// left wall
triangle { <-5,0,5>, <-5,0,-5>, <-5,10,-5>
   pigment { color rgb <0,1,0> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-5,10,5>, <-5,0,5>, <-5,10,-5>
   pigment { color rgb <0,1,0> }
   finish { ambient 0 diffuse 0.5 }
}

// back wall
triangle { <5,10,-5>, <-5,10,-5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,0,-5>, <-5,10,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}

// ceiling @ y=10, w/ a 1x1 hole in the middle
//big left part
triangle { <-5,10,5>, <-5,10,-5>, <-1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,5>, <-5,10,-5>, <-1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//big right part
triangle { <5,10,5>, <1,10,5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,10,5>, <1,10,-5>, <5,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//little front part
triangle { <-1,10,5>, <1,10,1>, <1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,5>, <-1,10,1>, <1,10,1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//little back part
triangle { <-1,10,-1>, <1,10,-5>, <1,10,-1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,-1>, <-1,10,-5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}

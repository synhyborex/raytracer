// cs174, assignment 1 sample file (RIGHT HANDED)

camera {  location  <4, 0, 14>
up        <0,  1,  0>
right     <1.5, 0,  0>
look_at   <0, 0, 0>}

//light_source {<-5, 3, 5> color rgb <1.0, 1.0, 1.0>}
light_source {<0, 5, 14> color rgb <7.0, 7.0, 7.0>}

//ground
plane {<0, 1, 0>, -4
      pigment {color rgb <1.0, 1.0, 1.0>}
      finish {ambient 0.4 diffuse 1.0}
}

//walls
// left wall
plane {<-1, 0, 0>, -8 
pigment {color rgb <0.8, 0.2, 0.2>}
finish {ambient 0.4 diffuse 1.0}  }

// back wall
//plane {<0, 0, 1>, 30  
//pigment {color rgb <0.8, 0.4, 0.2>}
//finish {ambient 0.4 diffuse 1.0} }

// back wall on the right
//plane {<-.34, 0, -.94>, 30  
//pigment {color rgb <0.0, 0.2, 0.2>}
//finish {ambient 0.4 diffuse 1.0} }


// random balls
//top right
sphere { <6, 2, 0>, 1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 1.0 specular 0.5 roughness 0.05}
}

//top left
sphere { <4, 1, 0>, 1
  pigment { color rgb <0.0, 0.0, 1.0>}
  finish {ambient 0.2 diffuse 1.0 specular 0.5 roughness 0.01}
}

//bottom
sphere { <5.5, -1, -4>, 2
pigment {color rgb <0.0, 1.0, 0.0>}
finish {ambient 0.2 diffuse 1.0}
}
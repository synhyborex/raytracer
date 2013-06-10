// cs174, assignment 1 sample file (RIGHT HANDED)

//camera {
//  location  <0, 0, 14>
//  up        <0,  1,  0>
//  right     <1.33333, 0, 0>
//  look_at   <0, 0, 0>
//}

camera {
  location  <3, -3.5, -1>
  up        <0,  1,  0>
  right     <-1.33333, 0, 0>
  look_at   <0, 0, 0>
}

//camera {
//location  <7, 0,7> 
//up        <0,  1,  0>
//right     <.94, 0,  -.94>
//look_at   <0, 0, 0>
//}


light_source {<100, 100, -100> color rgb <1.5, 1.5, 1.5>}
//light_source {<10, 10, 10> color rgb <0.0, 0.0, 0.0>}

//sphere { <0, -1, -1>, 1
//  pigment { color rgb <1.0, 0.0, 1.0>}
//  finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05 reflection 0.5}
//}

//triangle {
//  <-0.57735, 0.18759, 0.7946499999999999>,
//  <-0.35682, -0.49112, 0.7946499999999999>,
//  <0.35682, -0.49112, 0.7946499999999999>
//  pigment {color rgb <0.9, 0.9, 0.0>}
//  finish {ambient 0.4 diffuse 0.1}
//}

//box { <-2, -2, -2>, <2, 2, 2>
//  pigment { color rgb <1.0, 0.2, 1.0>}
//  finish {ambient 0.2 diffuse 0.8}
//}

//white sphere
sphere { <3, -3, 4>, 1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05}
}

// floor
plane {<0, 1, 0>, -4
  pigment {color rgb <0.2, 0.2, 0.8>}
  finish {ambient 0.4 diffuse 0.6}
  translate <0, -1, 0>
}

// left wall
//plane {<1, 0, 0>, -4
//  pigment {color rgb <0.8, 0.2, 0.2>}
//  finish {ambient 0.4 diffuse 0.2}
//}

// right wall
//plane {<-1, 0, 0>, -4
//  pigment {color rgb <0.8, 0.2, 0.2>}
//  finish {ambient 0.4 diffuse 0.2}
//}
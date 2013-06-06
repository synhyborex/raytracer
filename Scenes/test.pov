//default camera pointing down negative z - case 0
//camera {
//location  <0, 0, 20>
//up        <0,  1,  0>
//right     <1.33333, 0,  0>
//look_at   <0, 0, 0>
//}

//camera pointing down positive x - case 1
//camera {
//location  <-14, 0,0> 
//up        <0,  1,  0>
//right     <0, 0,  1.3333>
//look_at   <0, 0, 0>
//}

//camera pointing down negative x - case 2
//camera {
//location  <14, 0,0> 
//up        <0,  1,  0>
//right     <0, 0,  -1.3333>
//look_at   <0, 0, 0>
//}

//camera pointing around 45 degrees
camera {
location  <14, 0,14> 
up        <0,  1,  0>
right     <.94, 0,  -.94>
look_at   <0, 0, 0>
}


light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8 reflection 0.4}
}

//box { <-2, -2, -2>, <2, 2, 2>
//  pigment { color rgb <1.0, 0.2, 1.0>}
//  finish {ambient 0.2 diffuse 0.8}
//}


box { <-2, -2, -2>, <2, 2, 2>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  rotate <0, -90, 0>
  translate <3, 0, -5>
}
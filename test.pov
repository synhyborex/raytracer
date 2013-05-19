camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}

box { <-2, -2, -2>, <4, 3, 3>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
}


//box { <-2, -5, -5>, <2, 5, 5>
//  pigment { color rgbf <1.0, 0.2, 1.0, 0.6>}
//  finish {ambient 0.2 diffuse 0.8 reflection 0.2 refraction 1.0 ior 1.9}
//  rotate <0, -45, 0>
//  translate <3, 0, -5>
//}
GEOMOBJ=GeomObj/GeomObj.cpp GeomObj/SphereObj.cpp GeomObj/PlaneObj.cpp \
	GeomObj/TriObj.cpp GeomObj/ConeObj.cpp GeomObj/BoxObj.cpp
BVH=GeomObj/BVH_Node.cpp
WORLDOBJ=WorldObj/Camera.cpp WorldObj/Light.cpp WorldObj/WorldObj.cpp
IMAGE=Image/Image.cpp
RAY=Ray/Ray.cpp
FLAGS=-c -g -pg

default:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(IMAGE)
	g++ $(FLAGS) $(RAY)
	g++ $(FLAGS) $(WORLDOBJ)
	g++ $(FLAGS) $(BVH)
	g++ $(FLAGS) $(GEOMOBJ)
	g++ *.o -o render

run:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(IMAGE)
	g++ $(FLAGS) $(RAY)
	g++ $(FLAGS) $(WORLDOBJ)
	g++ $(FLAGS) $(BVH)
	g++ $(FLAGS) $(GEOMOBJ)
	g++ *.o -o render
	./render -I simple.pov 

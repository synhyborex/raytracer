OBJECTS=GeomObj/GeomObj.cpp GeomObj/SphereObj.cpp GeomObj/PlaneObj.cpp \
	GeomObj/TriObj.cpp GeomObj/ConeObj.cpp GeomObj/BoxObj.cpp \
	WorldObj/Camera.cpp WorldObj/Light.cpp WorldObj/WorldObj.cpp \
	Image/Image.cpp Ray/Ray.cpp
FLAGS=-c -g -pg -o3

default:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(OBJECTS)
	g++ *.o -o render

run:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(OBJECTS)
	g++ *.o -o render
	./render -Isimple.pov 

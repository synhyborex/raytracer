OBJECTS=GeomObj/GeomObj.cpp GeomObj/SphereObj.cpp GeomObj/PlaneObj.cpp \
	GeomObj/TriObj.cpp GeomObj/ConeObj.cpp GeomObj/BoxObj.cpp \
	WorldObj/Camera.cpp WorldObj/Light.cpp WorldObj/WorldObj.cpp \
	Image/Image.cpp
FLAGS=-c -g -Wall

default:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(OBJECTS)
	g++ *.o -o render

run:
	g++ $(FLAGS) raytrace.cpp
	g++ $(FLAGS) $(OBJECTS)
	g++ *.o -o render
	./render
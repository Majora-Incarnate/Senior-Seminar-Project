CXX 		= 	g++
EXE 		= 	Project
CXXFLAGS 	= 	-fopenmp -g -Wall -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net -lGLEW -lGL -lGLU -std=c++11
OBJDIR 		= 	Source
OBJECTS 	= 	Application.o Application_Event.o Event_Handler.o \
		        Clock.o System.o \
		        Object.o Collider.o Quad_Tree.o \
		        Color.o Video_Engine.o

all:
	make build
	$(CXX) -o $(EXE) Main.cpp $(OBJDIR)/*.o $(CXXFLAGS)

build:	$(addprefix $(OBJDIR)/, $(OBJECTS))

$(addprefix $(OBJDIR)/, $(OBJECTS)): %.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

run:
	./$(EXE)

r:
	./$(EXE)

clean:
	rm -f Source/*.o
	rm -f $(EXE)

c:
	rm -f Source/*.o
	rm -f $(EXE)

debug:
	#

d:
	#

pull:
	git pull

push:
	git push https://github.com/Majora-Incarnate/Senior-Seminar-Project.git

commit:
	git commit -a

add:
	git add -A

push_all:
	git add -A
	git commit -a
	git push https://github.com/Majora-Incarnate/Senior-Seminar-Project.git

force_pull:
	git reset --hard HEAD
	git pull

#removes all the ~ files, which are just backups
cleanup:
	find ./ -name '*~' | xargs rm
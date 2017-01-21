# Define a variable of all the .cpp files so that we don't have to modify this
# file every time a new file is added.
#
# Works by using the wildcard function to find all *.cpp files in the src
# directory, and then the patsubst function replaces every src/%.cpp with 
# obj/%.o to produce the desired list of required objects.
#
# www.gnu.org/software/make/manual/make.html#Wildcard-Function
objects = $(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))

all: clean project

project: objDir binDir $(objects)
	g++ -Wall $(objects) -o bin/project 

# Define a single rule for building objects so that the file doesn't need to be
# updated every single time a new class is added.
#
# Implicit variables $< = src/%.cpp and $@ = obj/%.o
#
# www.gnu.org/software/make/manual/make.html#Pattern-Examples
obj/%.o: src/%.cpp
	g++ -I./include -g -Wall -Wno-unused-variable -Wno-narrowing -Wno-sign-compare -c $< -o $@

objDir:
	mkdir -p ./obj

binDir:
	mkdir -p ./bin

clean:
	rm -rf obj
	rm -rf bin

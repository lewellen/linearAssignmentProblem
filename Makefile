libObjs = $(patsubst lib/%.cpp, obj/lib/%.o, $(wildcard lib/*.cpp))
bins = $(patsubst src/%.cpp, bin/%, $(wildcard src/*.cpp))

cppTool = g++
#cppFlags = -g -DDEBUG -Wall -std=c++14
cppFlags = -O3 -Wall -std=c++14

.PHONY: all clean

all: $(bins)

bin/document.pdf: doc/document.tex | bin
	pdflatex --output-directory=bin doc/document.tex

bin/%: obj/src/%.o obj/lib.o | bin
	$(cppTool) $(cppFlaggs) obj/lib.o $< -o $@

bin:
	mkdir -p ./bin

obj/lib.o: $(libObjs)
	ld -r $(libObjs) -o obj/lib.o

obj/src/%.o: src/%.cpp | obj/src
	$(cppTool) $(cppFlags) -I./include -c $< -o $@

obj/lib/%.o: lib/%.cpp | obj/lib
	$(cppTool) $(cppFlags) -I./include -c $< -o $@

obj/src: | obj
	mkdir -p ./obj/src

obj/lib: | obj
	mkdir -p ./obj/lib

obj:
	mkdir -p ./obj

clean:
	rm -rf obj
	rm -rf bin

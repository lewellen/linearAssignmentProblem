libObjs = $(patsubst lib/%.cpp, obj/lib/%.o, $(wildcard lib/*.cpp))
bins = $(patsubst src/%.cpp, bin/%, $(wildcard src/*.cpp))
figs = $(patsubst doc/%.gpi, obj/%.tex, $(wildcard doc/*.gpi))

cppTool = g++
#cppFlags = -g -DDEBUG -Wall -std=c++14
cppFlags = -O3 -Wall -std=c++14
cppLibs = -pthread

.PHONY: all clean
.PRECIOUS: obj/src/%.o obj/%.dat obj/%-summary.dat obj/%.tex obj/%.eps

all: $(bins)


bin/document.pdf: doc/document.tex $(figs) | bin
	pdflatex --output-directory=bin doc/document.tex

obj/%.tex: obj/%-summary.dat doc/%.gpi | obj
	gnuplot -e "argInput='$<'; argOutput='$@'" $(word 2, $^)

obj/%-summary.dat: analysis/%.py obj/%.dat | obj
	python $< $(word 2, $^) > $@

obj/%.dat: bin/% | obj
	$< > $@



bin/%: obj/src/%.o obj/lib.o | bin
	$(cppTool) $(cppFlaggs) $(cppLibs) obj/lib.o $< -o $@

bin:
	mkdir -p ./bin

obj/lib.o: $(libObjs)
	ld -r $(libObjs) -o obj/lib.o

obj/src/%.o: src/%.cpp | obj/src
	$(cppTool) $(cppFlags) $(cppLibs) -I./include -c $< -o $@

obj/lib/%.o: lib/%.cpp | obj/lib
	$(cppTool) $(cppFlags) $(cppLibs) -I./include -c $< -o $@

obj/src: | obj
	mkdir -p ./obj/src

obj/lib: | obj
	mkdir -p ./obj/lib

obj:
	mkdir -p ./obj

clean:
	rm -rf obj
	rm -rf bin

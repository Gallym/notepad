COMPILER = g++
COMPILEFLAGS = -std=c++17 -Wall -pedantic
VALGRINDFLAFS = --leak-check=full --show-leak-kinds=all
LINKLIBRARY = -lncurses -I/usr/include/libxml2 -lxml2
FILES := $(wildcard src/*.cpp src/windows/*.cpp src/notes/*.cpp)

%.o: %.cpp
	@echo "Building " $@
	@$(COMPILER) $(COMPILEFLAGS) -c -o $@ -c $< $(LINKLIBRARY)
	
compile: $(FILES:.cpp=.o)
	@echo "Compiling..."
	@$(COMPILER) -std=c++17 $(FILES:.cpp=.o) -o dosmagal $(LINKLIBRARY)
	@echo "Compiled."

memcheck: clean compile
	@echo "Compiling, running valgrind.."
	@$(COMPILER) $(COMPILEFLAGS) -g $(FILES:.cpp=.o) -o dosmagal $(LINKLIBRARY)
	valgrind $(VALGRINDFLAGS) ./dosmagal 

clean:
	@echo "Cleaning generated files.."
	@rm -f -- src/*.o
	@rm -f -- src/notes/*.o
	@rm -f -- src/windows/*.o
	@rm -rf -- build/
	@rm -rf -- doc/
	@rm -rf -- dosmagal
	@rm -rf -- error_log
	@echo "Cleaning done."

run:
	@echo "Running executable.."
	./dosmagal 

all: doc compile

doc:
	@echo "Generating docs.."
	@doxygen Doxyfile
	@echo "Generating done."

git: clean
	git add -A
	git commit -m "commit generated with makefile: $m"
	git push
#g++ -g -std=c++14 -lncurses -I/usr/include/libxml2 -lxml2 src/*.cpp src/windows/*.cpp src/notes/*.cpp
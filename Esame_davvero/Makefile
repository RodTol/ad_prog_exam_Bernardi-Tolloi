CXX = g++
CXXFLAGS = -Wall -Wextra

SRC = main.cpp \
	 benchmark-bst.cpp

EXE = $(SRC:.cpp=.x)

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .x

all: $(EXE)

.PHONY: all

%.x: %.cpp 
	$(CXX) $< -o $@ $(CXXFLAGS)

clean:
		rm -f $(EXE) *~

.PHONY: clean

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

main.x: include/iterator.hpp include/node.hpp include/bst.hpp
benchmark-bst.x: include/iterator.hpp include/node.hpp include/bst.hpp



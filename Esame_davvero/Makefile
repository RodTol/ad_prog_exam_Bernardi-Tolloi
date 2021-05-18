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

main.x: iterator.hpp node.hpp bst.hpp
benchmark-bst.x: iterator.hpp node.hpp bst.hpp
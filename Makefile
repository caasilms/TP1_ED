CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -Iinclude
TARGET := bin/tp1.out
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin obj:
	mkdir -p $@

clean:
	$(if $(ComSpec),del /Q obj\\*.o bin\\tp1.out 2>NUL || exit 0,rm -f obj/*.o $(TARGET))

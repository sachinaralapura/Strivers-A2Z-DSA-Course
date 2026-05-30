CXX = g++

CXXFLAGS = -std=c++20 \
			-Wall \
			-Wextra \
			-Wshadow \
			-Wconversion \
			-pedantic \
			-Iinclude \
			-g

SRC = $(shell find src -name '*.cpp')

OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

TARGET = bin/app

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build bin

.PHONY: all run clean

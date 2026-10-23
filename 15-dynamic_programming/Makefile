CXX = clang++

CXXFLAGS = -std=c++20 \
           -Wall -Wextra -Wshadow -Wconversion -pedantic \
           -Iinclude \
           -g \
           -O0

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

debug: all
	lldb ./$(TARGET)

clean:
	rm -rf build bin

.PHONY: all run debug clean

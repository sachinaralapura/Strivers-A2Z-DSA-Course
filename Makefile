# Define compiler and archiver
CXX = g++ -std=c++20
AR = ar

# Define build directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib

# Define include directory
INCLUDE_DIR = include

# Define C++ standard
CXXFLAGS = -std=c++20 # Added C++20 standard flag

# Define source directories (where .cpp files are located)
# Using `shell find` to dynamically get all subdirectories containing .cpp files
# This is more robust if you add new subfolders in the future
CPP_SRC_DIRS := $(shell find . -type d -path "./0*" -exec test -n "$(find {} -maxdepth 1 -name '*.cpp' -print -quit)" \; -print)
# Filter out 01-sorting and 05-linkedList as they only contain headers or other language files in your structure
CPP_SRC_DIRS := $(filter-out ./01-sorting ./05-linkedList,$(CPP_SRC_DIRS))
# Add hardcoded dirs if find misses any or you prefer explicit listing
CPP_SRC_DIRS += 02-arrays/easy 02-arrays/hard 02-arrays/medium \
                03-BinarySearch/Array1D 03-BinarySearch/Array2D 03-BinarySearch/OnAnswer \
                04-strings/easy 04-strings/medium \
                06-recursion/easy 06-recursion/hard 06-recursion/subsequencePatterns \
                07-bit_manipulation/easy 07-bit_manipulation/math 07-bit_manipulation/medium \
                08-stackQueues/easy 08-stackQueues/important 08-stackQueues/medium


# Get all .cpp files recursively from the source directories
SRCS = $(foreach dir, $(CPP_SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Define the library name
STATIC_LIB = $(LIB_DIR)/libmyalgorithms.a
DYNAMIC_LIB = $(LIB_DIR)/libmyalgorithms.so # If you plan to build a dynamic library

# Define the name of the executable for main.cpp
MAIN = $(BUILD_DIR)/main # Renamed from 'main' to avoid conflict if you have a file called 'main'
                                  # or if 'main' is reserved by system. 'main_app' is safer.

# Default target: build static library and then the main application
.PHONY: all static dynamic clean debug run

all: static $(MAIN)

# Target to build the static library
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	@echo "Creating static library: $(STATIC_LIB)"
	@mkdir -p $(@D) # Ensure the library output directory exists
	$(AR) rcs $@ $(OBJS)
	@echo "Static library created successfully."

# Target to build the dynamic library (optional)
dynamic: $(DYNAMIC_LIB)

$(DYNAMIC_LIB): $(OBJS)
	@echo "Creating dynamic library: $(DYNAMIC_LIB)"
	@mkdir -p $(@D) # Ensure the library output directory exists
	$(CXX) $(CXXFLAGS) -shared -o $@ $(OBJS)
	@echo "Dynamic library created successfully."

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: %.cpp
	@echo "Compiling $< to $@"
	@mkdir -p $(@D) # Ensure the subdirectory for the object file exists
	$(CXX) $(CXXFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

# Target to build the main application (my_application.cpp)
# This will first ensure the static library is built
$(MAIN): main.cpp $(STATIC_LIB)
	@echo "Building main application: $(MAIN)"
	@mkdir -p $(@D) # Ensure the build directory exists for the executable
	$(CXX) $(CXXFLAGS) main.cpp -o $@ -I$(INCLUDE_DIR) -L$(LIB_DIR) -lmyalgorithms
	@echo "Main application 'main.cpp' built successfully."

# Target to run the main application
run: $(MAIN)
	@echo "Running $(MAIN)..."
	@./$(MAIN)

# Clean up build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete."

# Print variables for debugging (useful if something isn't working as expected)
debug:
	@echo "CPP_SRC_DIRS: $(CPP_SRC_DIRS)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "STATIC_LIB: $(STATIC_LIB)"
	@echo "DYNAMIC_LIB: $(DYNAMIC_LIB)"
	@echo "MAIN_APP: $(MAIN)"

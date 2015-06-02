# Compiler
CC=g++

# Locations
BUILD=./build
SRC=./src
LIBRARY=-L "./lib" -L "./build"
INCLUDE=-I "./include" -I "./src/Renderer/include"

# Specific Locations
BUILD_BIN=$(BUILD)/bin
BUILD_OBJ=$(BUILD)/obj
BUILD_INCLUDE=$(BUILD)/include
SRC_INTERFACE=$(SRC)/Interface
SRC_INCLUDE=$(SRC)/Renderer/include
SRC_RENDERER=$(SRC)/Renderer/source

SRC_RENDERER_SOURCES=$(wildcard $(SRC_RENDERER)/*.cpp)
SRC_RENDERER_OBJECTS=$(addprefix $(BUILD_OBJ)/, $(notdir $(SRC_RENDERER_SOURCES:.cpp=.o)))

# Specific links
LINK_RENDERER=
LINK_CLI=
LINK_GUI=-lglfw3 -lopengl32 -lgdi32

all: Folders Pineapple cli
	# Finished!

Folders:
	# Make build folders
	mkdir -p $(BUILD)
	mkdir -p $(BUILD_BIN)
	mkdir -p $(BUILD_OBJ)
	mkdir -p $(BUILD_INCLUDE)

$(BUILD_OBJ)/%.o: $(SRC_RENDERER)/%.cpp
	$(CC) -c -D BUILD_DLL $(INCLUDE) $< -o $@

Pineapple: $(SRC_RENDERER_OBJECTS)
	# Compile shared library
	#$(CC) -o "$(SRC_RENDERER_OBJECTS)" -c -D BUILD_DLL $(INCLUDE) "./src/Renderer/Pineapple.cpp"
	$(CC) -o "$(BUILD_BIN)/Pineapple.dll" -shared $(SRC_RENDERER_OBJECTS)

	# Copy include files
	cp -r "$(SRC_INCLUDE)" "$(BUILD)/"

cli:
	# Make cli
	$(CC) -o "$(BUILD_BIN)/Pineapple-cli.exe" -I "$(BUILD_INCLUDE)" -L "$(BUILD_BIN)" "$(SRC_INTERFACE)/main-cli.cpp" -lPineapple

gui:
	#$(CC) -o "./build/bin/Pineapple-gui.exe" -I "./build/include" -L "./build/bin" "./src/Interface/main-gui.cpp" -lPineapple

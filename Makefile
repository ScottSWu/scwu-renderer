# Compiler
CC=g++

# Locations
BUILD=./build
SRC=./src
LIBRARY=./lib
INCLUDE=./include

# Specific Locations
BUILD_BIN=$(BUILD)/bin
BUILD_OBJ=$(BUILD)/obj
SRC_INTERFACE=$(SRC)/Interface
SRC_RENDERER=$(SRC)/Renderer

SRC_RENDERER_SOURCES=$(wildcard $(SRC_RENDERER)/*.cpp)
SRC_RENDERER_OBJECTS=$(addprefix $(BUILD_OBJ)/, $(notdir $(SRC_RENDERER_SOURCES:.cpp=.o)))

# Specific links
LINK_RENDERER=-lglfw3 -lopengl32 -lglu32 -lgdi32
LINK_CLI=-lPineapple
LINK_GUI=-lPineapple -lglfw3 -lopengl32 -lglu32 -lgdi32

all: Folders Pineapple cli gui
	# Finished!

Folders:
	# Make build folders
	mkdir -p $(BUILD)
	mkdir -p $(BUILD_BIN)
	mkdir -p $(BUILD_OBJ)

$(BUILD_OBJ)/%.o: $(SRC_RENDERER)/%.cpp
	$(CC) -c -I "$(INCLUDE)" $< -o $@ $(LINK_RENDERER)

Pineapple: $(SRC_RENDERER_OBJECTS)
	# Compile shared library
	# $(CC) -o "$(BUILD_BIN)/Pineapple.dll" -shared $(SRC_RENDERER_OBJECTS)

	# Compile static library
	ar rcs "$(BUILD_BIN)/libpineapple.a" $(SRC_RENDERER_OBJECTS)

cli:
	# Make cli
	$(CC) -o "$(BUILD_BIN)/Pineapple-cli.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" "$(SRC_INTERFACE)/main-cli.cpp" $(LINK_CLI)

gui:
	$(CC) -o "$(BUILD_BIN)/Pineapple-gui.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" -L "$(LIBRARY)" "$(SRC_INTERFACE)/main-gui.cpp" $(LINK_GUI)

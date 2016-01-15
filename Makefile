# Project
NAME=Pineapple

# Programs
CC="C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe"
CFLAGS=-std=c++11 -g -O3
WR=windres
AR="C:\msys64\mingw64\bin\ar.exe"

# Locations
BUILD=./build
SRC=./src
LIBRARYD=./lib/dynamic
LIBRARYS=./lib/static
INCLUDE=./include
RESOURCES=./res

# Specific Locations
BUILD_BIN=$(BUILD)/bin
BUILD_OBJ=$(BUILD)/obj
SRC_INTERFACE=$(SRC)/Interface
SRC_RENDERER=$(SRC)/$(NAME)

SRC_RENDERER_SOURCES=$(wildcard $(SRC_RENDERER)/*.cpp)
SRC_RENDERER_OBJECTS=$(addprefix $(BUILD_OBJ)/, $(notdir $(SRC_RENDERER_SOURCES:.cpp=.o)))

# Specific links
LINK_RENDERER=-lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32 -lFreeImage -ljsoncpp -lstdc++
LINK_CLI=-l$(NAME) $(LINK_RENDERER)
LINK_GUI=-l$(NAME) $(LINK_RENDERER) -lComdlg32

all: Folders Resources $(NAME) Libraries cli gui
	# Finished!

new: clean all
	# Good as new!

Folders:
	# Make build folders
	mkdir -p $(BUILD)
	mkdir -p $(BUILD_BIN)
	mkdir -p $(BUILD_OBJ)

Resources:
	# Copy resources
	cp -r $(RESOURCES) $(BUILD_BIN)

$(NAME): $(SRC_RENDERER_OBJECTS)
	# Compile static library
	$(AR) rcs "$(BUILD_BIN)/lib$(NAME).a" $(SRC_RENDERER_OBJECTS)

$(BUILD_OBJ)/%.o: $(SRC_RENDERER)/%.cpp
	$(CC) $(CFLAGS) -c -I "$(INCLUDE)" "$<" -o "$@"

Libraries:
	# Copy dynamic Libraries
	cp $(LIBRARYD)/* $(BUILD_BIN)

cli: $(NAME)
	# Make cli
	$(CC) $(CFLAGS) -o "$(BUILD_BIN)/$(NAME)-cli.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" "$(SRC_INTERFACE)/main-cli.cpp" $(LINK_CLI)

gui: $(NAME)
	# Compile resource file
	$(WR) -I "$(INCLUDE)" "$(SRC_INTERFACE)/resources.rc" "$(BUILD_OBJ)/resources.o"
	
	# Make gui
	$(CC) $(CFLAGS) -o "$(BUILD_BIN)/$(NAME)-gui.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" -L "$(LIBRARYD)" -L "$(LIBRARYS)" "$(SRC_INTERFACE)/main-gui.cpp" "$(BUILD_OBJ)/resources.o" $(LINK_GUI)

clean:
	# Cleaning build
	-rm -r $(BUILD)/*

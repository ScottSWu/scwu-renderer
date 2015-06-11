define \n


endef

# Project
NAME=Pineapple

# Compiler
CC=g++ -g -O0

# Archiver
AR=ar

# Locations
BUILD=./build
SRC=./src
LIBRARY=./lib/dynamic
INCLUDE=./include

# Specific Locations
BUILD_BIN=$(BUILD)/bin
BUILD_OBJ=$(BUILD)/obj
SRC_INTERFACE=$(SRC)/Interface
SRC_RENDERER=$(SRC)/$(NAME)

SRC_RENDERER_SOURCES=$(shell find "$(SRC_RENDERER)" -name "*.cpp" -type f)
SRC_RENDERER_OBJECTS=$(addprefix $(BUILD_OBJ)/, $(notdir $(SRC_RENDERER_SOURCES:.cpp=.o)))

# Specific links
LINK_RENDERER=-lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32
LINK_CLI=-l$(NAME)
LINK_GUI=-l$(NAME) -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32

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
	# TODO Copy resources to build directory

$(BUILD_OBJ)/%.o: $(SRC_RENDERER)/%.cpp
	$(CC) -c -I "$(INCLUDE)" $< -o $@ $(LINK_RENDERER)

$(NAME):
	# Compile source files
	$(foreach source, \
		$(SRC_RENDERER_SOURCES), \
		$(CC) -c -I "$(INCLUDE)" $(source) -o "$(BUILD_OBJ)/$(notdir $(source:.cpp=.o))" $(LINK_RENDERER) \
	;${\n})
	
	# Compile shared library
	# $(CC) -o "$(BUILD_BIN)/$(NAME).dll" -shared $(SRC_RENDERER_OBJECTS)

	# Compile static library
	$(AR) rcs "$(BUILD_BIN)/lib$(NAME).a" $(SRC_RENDERER_OBJECTS)

Libraries:
	# Copy dynamic Libraries
	cp $(LIBRARY)/* $(BUILD_BIN)

cli:
	# Make cli
	$(CC) -o "$(BUILD_BIN)/$(NAME)-cli.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" "$(SRC_INTERFACE)/main-cli.cpp" $(LINK_CLI)

gui:
	$(CC) -o "$(BUILD_BIN)/$(NAME)-gui.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" -L "$(LIBRARY)" "$(SRC_INTERFACE)/main-gui.cpp" $(LINK_GUI)

clean:
	# Cleaning build
	-rm -r "$(BUILD_BIN)"
	-rm -r "$(BUILD_OBJ)"

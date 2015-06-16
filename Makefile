define \n


endef

# Project
NAME=Pineapple

# Programs
CC=g++ -g -O0
WR=windres
AR=ar
FIND=$(shell where find | tr '\\' '/' | grep MinGW | head -n 1)

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

SRC_RENDERER_SOURCES=$(shell $(FIND) "$(SRC_RENDERER)" -name "*.cpp" -type f)
SRC_RENDERER_OBJECTS=$(addprefix $(BUILD_OBJ)/, $(notdir $(SRC_RENDERER_SOURCES:.cpp=.o)))

# Specific links
LINK_RENDERER=-lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32
LINK_CLI=-l$(NAME)
LINK_GUI=-l$(NAME) -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglew32 -ltinyobjloader -lComdlg32

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

$(NAME):
	# Compile source files
	$(foreach source, \
		$(SRC_RENDERER_SOURCES), \
		$(CC) -c -I "$(INCLUDE)" "$(source)" -o "$(BUILD_OBJ)/$(notdir $(source:.cpp=.o))" \
	;${\n})
	
	# Compile shared library
	# $(CC) -o "$(BUILD_BIN)/$(NAME).dll" -shared $(SRC_RENDERER_OBJECTS)

	# Compile static library
	$(AR) rcs "$(BUILD_BIN)/lib$(NAME).a" $(SRC_RENDERER_OBJECTS)

Libraries:
	# Copy dynamic Libraries
	cp $(LIBRARYD)/* $(BUILD_BIN)

cli:
	# Make cli
	$(CC) -o "$(BUILD_BIN)/$(NAME)-cli.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" "$(SRC_INTERFACE)/main-cli.cpp" $(LINK_CLI)

gui:
	# Compile resource file
	$(WR) -I "$(INCLUDE)" "$(SRC_INTERFACE)/resources.rc" "$(BUILD_OBJ)/resources.o"
	
	# Make gui
	$(CC) -o "$(BUILD_BIN)/$(NAME)-gui.exe" -I "$(INCLUDE)" -L "$(BUILD_BIN)" -L "$(LIBRARYD)" -L "$(LIBRARYS)" "$(SRC_INTERFACE)/main-gui.cpp" "$(BUILD_OBJ)/resources.o" $(LINK_GUI)

clean:
	# Cleaning build
	-rm -r $(BUILD)/*

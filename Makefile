# Compiler
CC=g++

# Locations
BUILD=./build
SRC=./src
LIBRARY=-L "./lib" -L "./build"
INCLUDE=-I "./include" -I "./src/Renderer/include"

# Specific files
LINK_GUI=-lglfw3 -lopengl32 -lgdi32
LINK_CLI=
LINK_RENDERER=

OUTPUT=Pineapple

all: Folders Pineapple cli

Folders:
	# Make build folders
	mkdir -p "./build"
	mkdir -p "./build/bin"
	mkdir -p "./build/include"

Pineapple:
	# Compile shared library
	$(CC) -o "./build/bin/Pineapple.o" -c -D BUILD_DLL $(INCLUDE) "./src/Renderer/Pineapple.cpp"
	$(CC) -o "./build/bin/Pineapple.dll" -shared "./build/bin/Pineapple.o"

	# Copy include files
	cp -r "./src/Renderer/include" "./build/"

cli:
	# Make cli
	$(CC) -o "./build/bin/Pineapple-cli.exe" -I "./build/include" -L "./build/bin" "./src/Interface/main-cli.cpp" -lPineapple

gui:
	#$(CC) -o "./build/bin/Pineapple-gui.exe" -I "./build/include" -L "./build/bin" "./src/Interface/main-gui.cpp" -lPineapple

# scwu-renderer

Personal multipurpose offline renderer

Layout:
- include - Headers
- src - Source files
    - Interface - cli and gui
    - Renderer - Actual renderer stuff
- lib - External libraries, shared and static
- build - Build files
    - bin - Executables and libraries
    - obj - Object file byproducts

Currently using:
- Windows API, may or may not try Qt
- A modified glfw3native header and library to expose its Windows callback function (see "include/GLFW/glfw3native.h" line 158)
- MinGW-g++
- Eclipse, which still seems to use sh and make. Effects of find, mkdir and rm may vary.
	- I tried to resolve this by detecting the mingw "find" program
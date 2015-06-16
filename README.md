# scwu-renderer

Layout:
- include - Headers
- src - Source files
    - Interface - cli and gui
    - Renderer - Actual renderer code
- lib - External libraries, shared and static
- build - Build files
    - bin - Executables and libraries
    - obj - Object file byproducts
- res - Additional resources
- obj - Some sample obj files and materials

Currently using:
- Windows API
- MinGW-g++
- Eclipse, which still seems to use sh and make. Effects of find, mkdir and rm may vary.
    - I tried to resolve this by detecting the mingw "find" program
- A modified glfw3native header and library to expose its Windows callback function (see "include/GLFW/glfw3native.h" line 158)

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
- MinGW-g++ and MSYS-make, so effects of mkdir and rm may vary
- Eclipse, which still seems to do different things with the make environment
- A modified glfw3native header and library to expose its Windows callback function

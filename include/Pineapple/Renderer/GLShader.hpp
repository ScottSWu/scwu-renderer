#ifndef _Pineapple_Object_GLShader
#define _Pineapple_Object_GLShader

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * Defines shader programs and their uniforms.
 */
class GLShader {
    protected:
        /** Shader program location */
        GLuint programId;
        /** Vertex shader location */
        GLuint vertexId;
        /** Fragment shader location */
        GLuint fragmentId;
    public:
        /**
         * Initialize a new shader program.
         */
        GLShader();

        /** Uniform location for viewport information (width, height, fov) */
        GLint vViewportId;
        /**  Uniform location for camera position */
        GLint vCameraPositionId;
        /**  Uniform location for camera direction */
        GLint vCameraDirectionId;
        /** Uniform location for the projection view matrix */
        GLint mProjectionViewId;
        /** Uniform location for the projection matrix */
        GLint mProjectionId;
        /** Uniform location for the view matrix */
        GLint mViewId;
        /** Uniform location for the transformation matrix */
        GLint mTransformId;
        /** Uniform location for the inverse transpose matrix */
        GLint mTransformITId;
        /** Uniform location for textures */
        GLint sTextureId[8];
        /** Uniform location for number of lights */
        GLint iLightCountId;
        /** Uniform location for light positions */
        GLint vLightPositionId;
        /** Uniform location for light colors */
        GLint vLightColorId;

        /**
         * Load vertex and fragment shader code by filename.
         *
         * @param vertexFile    Path to vertex code file
         * @param fragmentFile    Path to fragment code file
         */
        void load(std::string, std::string);
        /**
         * Bind this shader and its uniforms to the current gl context.
         */
        void bind();
        /**
         * Unbind this shader from the current gl context.
         */
        void unbind();
        /**
         * Get a shader uniform location by name.
         *
         * @param name  Uniform name
         * @return  Uniform location int
         */
        GLint getUniformLocation(const char *);
};

#endif

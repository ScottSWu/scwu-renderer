#ifndef _Pineapple_Renderer_GLUniforms
#define _Pineapple_Renderer_GLUniforms

class Camera;
class GLShader;
class Scene;

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class GLUniforms {
    private:
        glm::vec3 vViewport;
        glm::vec3 vCameraPosition;
        glm::vec3 vCameraDirection;
        glm::mat4 mProjection;
        glm::mat4 mView;
        glm::mat4 mProjectionView;

        int iLightCount;
        std::vector<glm::vec4> vLightPosition;
        std::vector<glm::vec4> vLightColor;
    public:
        /**
         * Initialize new uniforms from a scene.
         *
         * @param scene     The scene to set uniforms with
         * @param camera    The camera associated with the scene
         */
        GLUniforms(Scene *, Camera *);

        /**
         * Bind uniform data to a shader.
         *
         * @param shader    The shader to bind to
         */
        void bind(const GLShader &);
};

#endif

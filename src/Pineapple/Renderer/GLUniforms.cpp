#include "Pineapple/Renderer/GLUniforms.hpp"

#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Scene.hpp"

GLUniforms::GLUniforms(Scene * scene, Camera * camera) :
        vViewport((float) camera->viewport.x, (float) camera->viewport.y, 0.f), vCameraPosition(camera->position), vCameraDirection(
                glm::normalize(camera->target - camera->position)), mProjection(camera->computeProjectionMatrix()), mView(
                camera->computeCameraMatrix()), mProjectionView(mProjection * mView) {
    PerspectiveCamera * pcamera = dynamic_cast<PerspectiveCamera *>(camera);
    if (pcamera != 0) {
        vViewport.z = pcamera->fov;
    }
}

void GLUniforms::bind(const GLShader & shader) {
    glUniform3fv(shader.vViewportId, 1, &vViewport[0]);
    glUniform3fv(shader.vCameraPositionId, 1, &vCameraPosition[0]);
    glUniform3fv(shader.vCameraDirectionId, 1, &vCameraDirection[0]);
    glUniformMatrix4fv(shader.mProjectionViewId, 1, GL_FALSE, &mProjectionView[0][0]);
    glUniformMatrix4fv(shader.mProjectionId, 1, GL_FALSE, &mProjection[0][0]);
    glUniformMatrix4fv(shader.mViewId, 1, GL_FALSE, &mView[0][0]);
}

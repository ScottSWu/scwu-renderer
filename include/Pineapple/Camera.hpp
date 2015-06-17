#ifndef _Pineapple_Camera
#define _Pineapple_Camera

#include <glm/glm.hpp>

/**
 * Defines a camera.
 */
class Camera {
    public:
        /**
         * Initialize a default camera.
         */
        Camera(int width = 320, int height = 320, float near = 0.1f, float far = 100.f);

        /**
         * Destructor
         */
        virtual ~Camera();

        /** Positive viewport width and height */
        glm::ivec2 viewport;
        /** Near and far planes */
        glm::vec2 planes;

        // Camera position
        glm::vec3 position;
        // Camera lookAt target
        glm::vec3 target;
        // Camera up orientation
        glm::vec3 up;

        /**
         * Compute the camera matrix to transform into camera space.
         *
         * @return     4x4 camera transformation matrix
         */
        glm::mat4 computeCameraMatrix();
        /**
         * Compute the projection matrix to transform into normalized space.
         *
         * @return     4x4 projection matrix
         */
        virtual glm::mat4 computeProjectionMatrix();

        /**
         * Set the viewport size.
         *
         * @param width    Viewport width
         * @param height   Viewport height
         */
        void setViewport(int, int);
        /**
         * Set the position.
         *
         * @param x    x coordinate
         * @param y    y coordinate
         * @param z    z coordinate
         */
        void setPosition(float, float, float);
        /**
         * Set the viewing target.
         *
         * @param x    x coordinate
         * @param y    y coordinate
         * @param z    z coordinate
         */
        void setTarget(float, float, float);

        /**
         * Translate (pan) the camera by the specified mouse movement.
         *
         * @param mx    Mouse x movement
         * @param my    Mouse y movement
         */
        void translate(float, float);
        /**
         * Rotate (orbit) the camera around its target by the specified mouse movement.
         *
         * @param mx    Mouse x movement
         * @param my    Mouse y movement
         */
        void rotate(float, float);
        /**
         * Zoom the camera by the specified mouse movement.
         *
         * @param mx    Mouse x movement
         * @param my    Mouse y movement
         */
        void zoom(float, float);

        /**
         * Move (fly) the camera by the specified mouse movement.
         *
         * @param mx    Mouse x movement
         * @param my    Mouse y movement
         */
        void move(float, float);
        /**
         * Rotate (look around) the camera by the specified mouse movement.
         *
         * @param mx    Mouse x movement
         * @param my    Mouse y movement
         */
        void look(float, float);
};

#endif

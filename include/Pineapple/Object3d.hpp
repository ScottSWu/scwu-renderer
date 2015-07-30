#ifndef _Pineapple_Object3d
#define _Pineapple_Object3d

#include "Pineapple/BoundingBox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <vector>
#include <string>
#include <map>

class Intersection;
class Ray;

/**
 * Defines an object in the scene.
 */
class Object3d {
    protected:
    public:
        /**
         * Initialize a new object.
         */
        Object3d();
        /**
         * Destructor
         */
        virtual ~Object3d();

        /** Whether or not the object properties have been updated */
        bool needsUpdate;
        /** Whether or not the object is visible */
        bool visible;
        /** Whether or not the object is a wireframe */
        bool wireframe;
        /** Local transformation matrix */
        glm::mat4 transform;

        /** List of children */
        std::vector<Object3d *> children;
        /** Indexed locations for multiple renderers */
        std::vector<int> rendererIndex;
        /** Additional properties */
        std::map<std::string, std::string> properties;

        /** Computed complete transformation matrix */
        glm::mat4 worldTransform;
        /** Inverse of the transformation matrix */
        glm::mat4 worldTransformI;
        /** Inverse transpose of the complete transformation matrix */
        glm::mat4 worldTransformIT;

        /** The bounding box of the object */
        BoundingBox boundingBox;
        /** The bounding box of the object and all of its children */
        BoundingBox totalBoundingBox;

        /**
         * Add a child object.
         *
         * @param object   Object to add
         */
        void addChild(Object3d *);
        /**
         * Remove a child object.
         *
         * @param object   Object to remove
         */
        void removeChild(Object3d *);

        /**
         * Recursively compute the world transform.
         *
         * @param parentTransform   Transformation matrix of the parent object
         * @param parentUpdate      Whether or not the parent has been updated
         */
        void computeTransform(glm::mat4, bool);

        /**
         * Compute the local bounding box of this object.
         *
         * @param recursive     Whether or not to compute the bounding box of children as well.
         *                      Children are computed before this object is, and are consequently
         *                      used to compute this object's bounding box. (default true)
         */
        virtual BoundingBox computeBoundingBox(bool recursive = true);

        /**
         * Intersect a ray with this object.
         *
         * @param result        A vector of intersections
         * @param ray           The ray to intersect with
         * @param recursive     Whether or not to test children as well (default false)
         * @param limit         Maximum number of intersections (default 0, no maximum)
         * @return  The number of intersections recorded
         */
        virtual int intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive = false, int limit =
                0);
};

#endif

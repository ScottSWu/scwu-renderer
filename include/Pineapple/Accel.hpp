#ifndef _Pineapple_Accel
#define _Pineapple_Accel

#include "Pineapple/BoundingBox.hpp"

#include <vector>

/**
 * Defines an acceleration structure.
 */
class Accel {
    public:
        /**
         * Whether or not this node is a leaf node.
         */
        bool isLeaf;

        /**
         * The bounding box of this node.
         */
        BoundingBox boundingBox;

        /**
         * A list of contained indices. This list must be populated for leaf nodes,
         * but may be empty for non-leaf nodes.
         */
        std::vector<int> indices;

        /**
         * A list of child nodes.
         */
        std::vector<Accel *> children;
};

#endif

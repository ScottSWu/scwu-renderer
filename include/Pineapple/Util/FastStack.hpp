#ifndef _Pineapple_Util_FastStack
#define _Pineapple_Util_FastStack

#include <vector>

template<class T> class FastStack {
    private:
        /**
         * Pointer to data.
         */
        std::vector<T> data;
        /**
         * Reserved size of the stack.
         */
        unsigned int dataSize;
        /**
         * Top of the stack.
         */
        unsigned int dataTop;
    public:
        /**
         * Initialize a new fast stack.
         */
        FastStack() :
                dataSize(32), dataTop(0) {
            data.reserve(dataSize);
        }

        /**
         * Destructor.
         */
        ~FastStack() {
        }

        /**
         * Push an item onto the stack.
         *
         * @param item      The item to push
         */
        void push(const T & item) {
            if (dataTop >= dataSize) {
                dataSize = dataSize * 2;
                data.resize(dataSize);
            }
            data[dataTop] = item;
            dataTop++;
        }

        /**
         * Get the item at the top of the stack.
         *
         * @return      The item at the top of the stack
         */
        const T & top() {
            if (dataTop > 0) {
                return data[dataTop - 1];
            }
            else {

            }
        }

        /**
         * Pop and item off the stack.
         */
        void pop() {
            if (dataTop > 0) {
                dataTop--;
            }
        }

        /**
         * Returns whether or not the stack is empty.
         *
         * @return      If the stack is empty
         */
        bool empty() {
            return dataTop == 0;
        }

        /**
         * Returns the number of elements in the stack.
         *
         * @return      Number of elements in the stack
         */
        unsigned int size() {
            return dataTop;
        }
};

#endif

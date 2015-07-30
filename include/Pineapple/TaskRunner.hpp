#ifndef _Pineapple_Task_Runner
#define _Pineapple_Task_Runner

class Renderer;

#include <map>
#include <string>

/**
 * Defines a task runner.
 */
class TaskRunner {
    protected:
        /**
         * Renderer used.
         */
        Renderer * currentRenderer;
    public:
        /**
         * Initialize a new task runner.
         *
         * @param renderer      The renderer to run tasks on
         * @param parameters    A set of parameters
         */
        TaskRunner(Renderer *, std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        virtual ~TaskRunner();

        /**
         * Run all tasks provided by the renderer.
         */
        virtual void run();
};

#endif

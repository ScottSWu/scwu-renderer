#ifndef _Pineapple_Task_Multiprocessing
#define _Pineapple_Task_Multiprocessing

class RenderTask;

#include "Pineapple/TaskRunner.hpp"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <map>
#include <string>
#include <thread>
#include <vector>

class MPTaskRunner: public TaskRunner {
    protected:
        /**
         * Number of available cores.
         */
        int cores;
        /**
         * Run a local instance of the render function.
         */
        void localRun(RenderTask *, bool *);

        /**
         * Instance mutex.
         */
        std::mutex mutex;
        /**
         * Notification condition variable.
         */
        std::condition_variable cv;
    public:
        /**
         * Initialize a new task runner.
         *
         * @param renderer      The renderer to run tasks on
         * @param cores         The number of cores available
         * @param parameters    A set of parameters
         */
        MPTaskRunner(Renderer *, int cores = 1,
                std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        ~MPTaskRunner();

        /**
         * Run tasks.
         */
        void run();
};

#endif

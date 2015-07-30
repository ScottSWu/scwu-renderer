#include "Pineapple/Task/MPTaskRunner.hpp"

#include "Pineapple/RenderTask.hpp"
#include "Pineapple/Renderer.hpp"

MPTaskRunner::MPTaskRunner(Renderer * inRenderer, int inCores, std::map<std::string, std::string> parameters) :
        TaskRunner(inRenderer, parameters), cores(inCores) {

}

MPTaskRunner::~MPTaskRunner() {

}

void MPTaskRunner::run() {
    std::unique_lock<std::mutex> lock(mutex, std::defer_lock);

    std::thread * workers[cores];
    RenderTask * tasks[cores];
    bool * flags[cores];

    for (int i = 0; i < cores; i++) {
        workers[i] = 0;
        tasks[i] = 0;
        flags[i] = 0;
    }

    bool finished = false;
    while (!finished) {
        finished = true;
        for (int i = 0; i < cores; i++) {
            if (workers[i] == 0) {
                if (currentRenderer->hasTask()) {
                    RenderTask * task = currentRenderer->getTask();
                    bool * finish = new bool(false);
                    std::thread localThread(&MPTaskRunner::localRun, this, task, finish);
                    localThread.detach();
                    workers[i] = &localThread;
                    tasks[i] = task;
                    flags[i] = finish;

                    finished = false;
                }
            }
            else if (flags[i] != 0 && *flags[i]) {
                RenderTask * task = tasks[i];
                currentRenderer->process(task);

                // Clean up
                workers[i] = 0;
                delete tasks[i];
                tasks[i] = 0;
                delete flags[i];
                flags[i] = 0;

                finished = false;
            }
            else {
                finished = false;
            }
        }

        cv.wait_for(lock, std::chrono::milliseconds(1));
    }
}

void MPTaskRunner::localRun(RenderTask * task, bool * finish) {
    currentRenderer->render(task);

    finish[0] = true;
    cv.notify_all();
}

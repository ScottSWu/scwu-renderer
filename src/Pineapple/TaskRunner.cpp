#include "Pineapple/TaskRunner.hpp"

#include "Pineapple/Renderer.hpp"
#include "Pineapple/RenderTask.hpp"

TaskRunner::TaskRunner(Renderer * inRenderer, std::map<std::string, std::string> parameters) :
        currentRenderer(inRenderer) {

}

TaskRunner::~TaskRunner() {

}

void TaskRunner::run() {
    while (currentRenderer->hasTask()) {
        RenderTask * task = currentRenderer->getTask();
        currentRenderer->render(task);
        currentRenderer->process(task);
    }
}

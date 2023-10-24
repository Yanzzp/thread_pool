#include "TaskQueue.h"

TaskQueue::TaskQueue() = default;

TaskQueue::~TaskQueue() = default;

void TaskQueue::addTask(Task task) {
    mutex.lock();
    tasksQueue.push(task);
    mutex.unlock();
}

void TaskQueue::addTask(callback function, void *args) {
    mutex.lock();
//    tasksQueue.push(Task(function, args));
    /*使用 emplace 的好处是它允许“就地构造”，即对象直接在容器中被构造，
    而不是先在外部构造然后再复制或移动到容器中。
    这可以减少一些不必要的对象创建和销毁操作，特别是在涉及到大对象或复杂对象时。*/
    tasksQueue.emplace(function, args);

    mutex.unlock();
}


Task TaskQueue::takeTask() {


    if (!tasksQueue.empty()) {
        mutex.lock();
        Task temp;
        temp = tasksQueue.front();
        tasksQueue.pop();
        mutex.unlock();
        return temp;
    }

}


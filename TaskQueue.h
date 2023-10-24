#ifndef THREADPOOL_TASKQUEUE_H
#define THREADPOOL_TASKQUEUE_H

#include <queue>
#include <mutex>
using callback = void (*)(void *);

struct Task {

    Task() {
        function = nullptr;
        args = nullptr;
    }

    Task(callback function, void *args) : function(function), args(args) {}

    callback function;

    void *args;
};

class TaskQueue {
private:
    std::queue<Task> tasksQueue;
    std::mutex mutex;
public:
    TaskQueue();
    ~TaskQueue();

    void addTask(Task task);
    void addTask(callback function, void *args);

    Task takeTask();

    inline int taskNumber() { return tasksQueue.size(); }

};


#endif //THREADPOOL_TASKQUEUE_H

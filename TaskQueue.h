#ifndef THREADPOOL_TASKQUEUE_H
#define THREADPOOL_TASKQUEUE_H

#include <queue>
#include <pthread.h>
#include <mutex>


// 定义任务结构体
using callback = void (*)(void *);

struct Task {
    callback function;
    void *arg;

    Task() {
        function = nullptr;
        arg = nullptr;
    }

    Task(callback f, void *arg) {
        function = f;
        this->arg = arg;
    }

};

// 任务队列
namespace pthread{
    class TaskQueue {
    public:
        TaskQueue();

        ~TaskQueue();

        // 添加任务
        void addTask(Task &task);

        void addTask(callback func, void *arg);

        // 取出一个任务
        Task takeTask();

        // 获取当前队列中任务个数
        inline int taskNumber() {
            return m_queue.size();
        }

    private:
        pthread_mutex_t m_mutex;    // 互斥锁
        std::queue<Task> m_queue;   // 任务队列
    };
}

class TaskQueue {
private:
    std::mutex m_mutex;    // 互斥锁
    std::queue<Task> m_queue;   // 任务队列
public:
    TaskQueue()=default;

    ~TaskQueue()=default;

    // 添加任务
    void addTask(Task &task);

    void addTask(callback func, void *arg);

    void getTask(Task &task);

    // 获取当前队列中任务个数
    inline int taskNumber() {
        return m_queue.size();
    }
};



#endif //THREADPOOL_TASKQUEUE_H

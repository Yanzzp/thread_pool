#include "TaskQueue.h"

pthread::TaskQueue::TaskQueue()
{
    // 初始化互斥锁
    pthread_mutex_init(&m_mutex, NULL);
}

pthread::TaskQueue::~TaskQueue()
{
    // 销毁互斥锁
    pthread_mutex_destroy(&m_mutex);
}

void pthread::TaskQueue::addTask(Task& task)
{
    // 添加任务
    pthread_mutex_lock(&m_mutex);
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);
}

void pthread::TaskQueue::addTask(callback func, void* arg)
{
    pthread_mutex_lock(&m_mutex);
    Task task;
    task.function = func;
    task.arg = arg;
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);
}

Task pthread::TaskQueue::takeTask()
{
    Task t;
    pthread_mutex_lock(&m_mutex);
    if (m_queue.size() > 0)
    {
        t = m_queue.front();
        m_queue.pop();
    }
    pthread_mutex_unlock(&m_mutex);
    return t;
}

void TaskQueue::addTask(Task &task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(task);
}

void TaskQueue::addTask(callback func, void *arg) {
    std::lock_guard<std::mutex> lock(m_mutex);
    Task task;
    task.function = func;
    task.arg = arg;
    m_queue.push(task);
}

void TaskQueue::getTask(Task &task) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.size() > 0) {
        task = m_queue.front();
        m_queue.pop();
    }
}

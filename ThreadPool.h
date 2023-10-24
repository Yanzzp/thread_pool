#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <condition_variable>
#include "TaskQueue.h"

class ThreadPool {
private:
    Task taskQueue;

    pthread_mutex_t m_lock;
    pthread_cond_t m_notEmpty;
    pthread_t *threadIDs;
    pthread_t managerID;

    int minNum;
    int maxNum;
    int busyNum;
    int aliveNum;
    int exitNum;

    std::mutex mutexPool;

    std::condition_variable notEmpty;

    bool shutdown;

    // 工作的线程(消费者线程)任务函数
    void *worker(void *arg);

// 管理者线程任务函数
    void *manager(void *arg);

// 单个线程退出
    void threadExit();
public:

// 创建线程池并初始化
    ThreadPool(int min, int max);

// 销毁线程池
    ~ThreadPool();

// 给线程池添加任务
    void addTask(Task task);

// 获取线程池中工作的线程的个数
    int getBusyNum();

// 获取线程池中活着的线程的个数
    int getAliveNum();




};


#endif //THREADPOOL_THREADPOOL_H

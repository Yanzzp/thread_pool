#pragma once
#include "TaskQueue.h"
#include <cstring>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <functional>

namespace pthread {
    class ThreadPool {
    private:
        pthread_mutex_t m_lock;
        pthread_cond_t m_notEmpty;
        pthread_t *m_threadIDs;
        pthread_t m_managerID;
        TaskQueue *m_taskQ;
        int m_minNum;
        int m_maxNum;
        int m_busyNum;
        int m_aliveNum;
        int m_exitNum;
        bool m_shutdown = false;

    private:
        // 工作的线程的任务函数
        static void *worker(void *arg);

        // 管理者线程的任务函数
        static void *manager(void *arg);

        void threadExit();

    public:
        ThreadPool(int min, int max);

        ~ThreadPool();

        // 添加任务
        void addTask(Task task);

        // 获取忙线程的个数
        int getBusyNumber();

        // 获取活着的线程个数
        int getAliveNumber();

    };
}

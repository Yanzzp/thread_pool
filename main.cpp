#include <iostream>
#include <csignal>
#include "ThreadPool.h"

void simpleTask(void* arg) {
    int* x = (int*)arg;
    std::cout << "Task " << *x << " is being processed by thread: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟耗时操作
}

int main() {
    ThreadPool pool(4);  // 创建一个包含4个线程的线程池



    std::vector<int> taskIds(10);
    for(int i = 0; i < 10; ++i) {
        taskIds[i] = i + 1;
        pool.addTask(simpleTask, &taskIds[i]);
    }

    // 等待所有任务都被处理
    std::this_thread::sleep_for(std::chrono::seconds(10));

    pool.shutdown();  // 关闭线程池

    std::cout << "All tasks are done!" << std::endl;

    return 0;
}



#include <iostream>
#include "ThreadPool.h"
#include "multithread.h"

void simpleTask(int &x) {

    std::cout << "Task " << x << " is being processed by thread: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));  // 模拟耗时操作
}

int main() {
    int x = 1;
    multithreads(simpleTask(x);, true);
    return 0;
}



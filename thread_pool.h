#ifndef THREAD_POOL_H
#define THREAD_POOL_H


#include <vector>
#include <thread>
#include <atomic>
#include "queue.h"
#include "client_data.h"

class ThreadPool
{
    std::vector<std::thread> threads;
    std::atomic<bool> isStopped = false;
    Queue socketQueue;

public:
    ThreadPool();
    ~ThreadPool();
    void start();
    void add_client(const ClientData& client);
    void stop();
};


#endif //THREAD_POOL_H

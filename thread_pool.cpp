#include "thread_pool.h"
#include "client_handler.h"

#define THREAD_COUNT 4

ThreadPool::ThreadPool() {}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::start()
{
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back([this]() {
            while (!isStopped.load())
            {
                ClientData client = socketQueue.pop();
                ClientHandler handler(client.socket, client.ip, client.port);
                handler();
            }
        });
    }
}

void ThreadPool::add_client(const ClientData& client)
{
    socketQueue.push(client);
}

void ThreadPool::stop()
{
    isStopped.store(true);
    socketQueue.notifyAll();

    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }
}

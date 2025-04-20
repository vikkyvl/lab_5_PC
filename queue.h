#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "client_data.h"

class Queue
{
public:
    void push(const ClientData& clientData);
    ClientData pop();
    void notifyAll();

private:
    std::queue<ClientData> socket_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_notifier;
};

#endif //QUEUE_H

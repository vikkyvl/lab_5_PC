#include "queue.h"

void Queue::push(const ClientData& clientData)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    socket_queue.push(clientData);
    queue_notifier.notify_one();
}

ClientData Queue::pop()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    queue_notifier.wait(lock, [this] { return !socket_queue.empty(); });

    ClientData client = socket_queue.front();
    socket_queue.pop();
    return client;
}

void Queue::notifyAll()
{
    queue_notifier.notify_all();
}

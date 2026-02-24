#ifndef TASK_GRAPH__H_
#define TASK_GRAPH__H_

#include "Task.h"

#include <queue>
#include <vector>

class TaskGraph
{

public:
    TaskGraph() = default;
    TaskGraph(TaskGraph const& other) = delete;
    TaskGraph(TaskGraph&& other) noexcept = delete;

    TaskGraph& operator=(TaskGraph const& other) = delete;
    TaskGraph& operator=(TaskGraph&& other) = delete;
    ~TaskGraph() = default;

    void AddTask(Task const& task);
    void Execute();

private:
    // Using a custom function object to compare elements.
    struct Comparator
    {
        bool operator()(const Task* l, const Task* r) const { return l->GetDegree() > r->GetDegree(); }
    };

    std::priority_queue<Task const*, std::vector<Task const*>, Comparator> m_taskQueue;
};

#endif

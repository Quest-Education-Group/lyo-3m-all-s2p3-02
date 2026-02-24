#include "Multithreading/TaskGraph.h"

void TaskGraph::AddTask(Task const& task)
{
    m_taskQueue.push(&task);
}

void TaskGraph::Execute()
{
    while(m_taskQueue.empty() == false)
    {
        //TODO Multithread this my g
        m_taskQueue.top()->TaskFunction();
        m_taskQueue.pop();
    }
}

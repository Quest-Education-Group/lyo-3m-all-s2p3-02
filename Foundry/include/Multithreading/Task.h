#ifndef TASK__H_
#define TASK__H_

#include <functional>
#include <string_view>

using TaskFunc = std::function<void()>;

enum class TaskState
{
    WAITING,
    IDLE,
    BUSY
};

//Multi threaded task
struct Task
{
    std::string_view Name;
    TaskFunc TaskFunction;
    TaskState State;

    void AddDependency(Task& dependency){ dependency.m_degree++; }
    int GetDegree() const { return m_degree; }

private:
    //std::vector<Task*> m_dependOn;
    int m_degree = 0;
};

#endif

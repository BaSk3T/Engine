#ifndef TASKTHREAD_H
#define TASKTHREAD_H

class Task;

#include <thread>
#include <mutex>

#include "../LockFreeDataStructures/LockFreeStack.h"

class TaskThread
{
public:
	TaskThread();
	~TaskThread();
	
	void Wake();
	void Sync();
	bool IsAwake() const;

private:
	void Entry();

	std::mutex m_Mutex;
	std::thread m_Thread;
	std::condition_variable m_ConditionVariable;

	LockFreeStack<Task*> m_AssignedTasks;
	bool m_Quit;
	bool m_IsAwake;
};

#endif // !TASKTHREAD_H

#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

class Task;
class TaskThread;

#include <vector>
#include "../Types.h"
#include "../LockFreeDataStructures/LockFreeStack.h"

class TaskScheduler
{
public:
	TaskScheduler();
	~TaskScheduler();

	bool HasTasks();
	void WakeWorkerThreads();
	void SyncWorkerThreads();
	void WaitForWorkerThreadsToFinish();
	void AddTask(Task* task);

	void AddThreads(UI32 numberOfThreads);

	void SetTasksPerThread(UI32 tasksPerThread);

	// Assigns task to thread
	// if successful returns true otherwise returns false
	bool AssignPendingTasks(LockFreeStack<Task*>& tasks);

	static TaskScheduler& GetInstance() { return ms_Instance; };

private:
	void DeleteThreads();

	static TaskScheduler ms_Instance;

	LockFreeStack<Task*> m_Tasks;
	std::vector<TaskThread*> m_Threads;

	UI32 m_TasksPerThread;
};

#endif // !TASKSCHEDULER_H
#include "TaskScheduler.h"

#include "Task.h"
#include "TaskThread.h"

TaskScheduler TaskScheduler::ms_Instance;

TaskScheduler::TaskScheduler()
	: m_TasksPerThread(0)
{
}

TaskScheduler::~TaskScheduler()
{
	DeleteThreads();
}

void TaskScheduler::AddThreads(UI32 numberOfThreads)
{
	for (UI32 i = 0; i < numberOfThreads; i++)
	{
		m_Threads.push_back(new TaskThread());
	}
}

void TaskScheduler::SetTasksPerThread(UI32 tasksPerThread)
{
	m_TasksPerThread = tasksPerThread;
}

bool TaskScheduler::AssignPendingTasks(LockFreeStack<Task*>& tasks)
{
	if (m_Tasks.IsEmpty())
	{
		return false;
	}

	for (UI32 i = 0; i < m_TasksPerThread; ++i)
	{
		Task* task;
		bool popped = m_Tasks.Pop(task);

		if (!popped && tasks.IsEmpty()) // no tasks left and nothing was added to thread tasks -> return false
		{
			return false;
		}

		if (!popped) //  no tasks left but tasks were already added to thread -> return true
		{
			return true;
		}

		tasks.Push(task);
	}

	return true;
}

bool TaskScheduler::HasTasks()
{
	return !m_Tasks.IsEmpty();
}

void TaskScheduler::WakeWorkerThreads()
{
	for (auto th : m_Threads)
	{
		th->Wake();
	}
}

void TaskScheduler::SyncWorkerThreads()
{
	for (auto th : m_Threads)
	{
		th->Sync();
	}
}

void TaskScheduler::WaitForWorkerThreadsToFinish()
{
	while (true)
	{
		bool threadsAreAwake = false;

		for (auto th : m_Threads)
		{
			// if thread is awake threadsAreAwake = true;
			if (th->IsAwake())
			{
				threadsAreAwake = true;
			}
		}

		std::this_thread::yield();

		// if !threadsAreAwake -> no thread is awake thus return
		if (!threadsAreAwake)
		{
			return;
		}
	}
}

void TaskScheduler::AddTask(Task* task)
{
	m_Tasks.Push(task);
}

void TaskScheduler::DeleteThreads()
{
	for (auto th : m_Threads)
	{
		delete th;
	}
}
#include "TaskThread.h"

#include "Task.h"
#include "TaskScheduler.h"

TaskThread::TaskThread()
	: m_Quit(false)
{
	m_Thread = std::thread(&TaskThread::Entry, this);
}

TaskThread::~TaskThread()
{
	// to be removed later
	m_Thread.join();
}

void TaskThread::Entry()
{
	TaskScheduler& ts = TaskScheduler::GetInstance();

	while (!m_Quit)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);

		m_ConditionVariable.wait(lock, [this]()
		{
			TaskScheduler& ts = TaskScheduler::GetInstance();
			return ts.HasTasks() || m_Quit;
		});

		while (ts.AssignPendingTasks(m_AssignedTasks))
		{
			while (!m_AssignedTasks.IsEmpty())
			{
				Task* task;

				m_AssignedTasks.Pop(task);
				task->Complete();
			}
		}

		lock.unlock();
	}
}

void TaskThread::Wake()
{
	m_ConditionVariable.notify_one();
}

void TaskThread::Sync()
{
	m_Quit = true;
	Wake();
}
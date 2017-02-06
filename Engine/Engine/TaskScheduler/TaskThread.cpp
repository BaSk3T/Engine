#include "TaskThread.h"

#include "Task.h"
#include "TaskScheduler.h"

TaskThread::TaskThread()
	: m_Quit(false),
	m_IsAwake(false)
{
	m_Thread = std::thread(&TaskThread::Entry, this);
}

TaskThread::~TaskThread()
{
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
			m_IsAwake = ts.HasTasks() || m_Quit;

			return m_IsAwake;
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

		m_IsAwake = false;

		lock.unlock();
	}
}

void TaskThread::Wake()
{
	m_IsAwake = true;
	m_ConditionVariable.notify_one();
}

void TaskThread::Sync()
{
	m_Quit = true;
	Wake();
}

bool TaskThread::IsAwake() const
{
	return m_IsAwake;
}

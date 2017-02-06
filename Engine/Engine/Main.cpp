#include <iostream>

#include "TaskScheduler\TaskScheduler.h"
#include "TestingTask.h"

int main()
{
	TaskScheduler& ts = TaskScheduler::GetInstance();
	ts.AddThreads(8);
	ts.SetTasksPerThread(5);
	
	for (UI32 i = 0; i < 100; i++)
	{
		ts.AddTask(new TestingTask((char)i));
	}

	ts.WakeWorkerThreads();
	ts.WaitForWorkerThreadsToFinish();
	ts.SyncWorkerThreads();

	return 0;
}
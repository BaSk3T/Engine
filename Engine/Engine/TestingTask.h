#ifndef TESTINGTASK_H
#define TESTINGTASK_H

#include "TaskScheduler\Task.h"

class TestingTask : public Task
{
public:
	TestingTask(char ch);
	~TestingTask();

	virtual void Complete();

private:
	char m_Ch;
};

#endif // !TESTINGTASK_H

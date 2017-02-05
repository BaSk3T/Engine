#ifndef TASK_H
#define TASK_H

#include <functional>

class Task
{
public:
	Task();
	~Task();

	virtual void Complete() = 0;
};

#endif // !TASK_H

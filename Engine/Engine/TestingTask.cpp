#include "TestingTask.h"

#include <fstream>
#include <string>

TestingTask::TestingTask(char ch)
	: m_Ch(ch)
{
}

TestingTask::~TestingTask()
{
}

void TestingTask::Complete()
{
	std::string name = std::to_string(static_cast<int>(m_Ch));
	name += ".txt";

	std::ofstream outfile(name);

	for (size_t i = 0; i < 100; i++)
	{
		outfile << m_Ch;
	}

	outfile.close();
}
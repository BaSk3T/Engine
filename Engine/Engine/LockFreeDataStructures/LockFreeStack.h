#ifndef LOCKFREESTACK_H
#define LOCKFREESTACK_H

#include <atomic>

#include "../Types.h"

template <typename T>
class LockFreeStack
{
public:
	LockFreeStack();
	~LockFreeStack();

	void Push(T value);
	bool Pop(T& value);

	bool IsEmpty() const;

private:
	struct Node {
		Node() {};
		Node(T data) : m_Next(nullptr), m_Data(data) {};

		Node* m_Next;
		T m_Data;
	};

	struct CtPtr {
		CtPtr() : m_Pointer(nullptr), m_Count(0) {};
		CtPtr(Node* pointer) : m_Pointer(pointer), m_Count(0) {};

		bool operator== (CtPtr const & other) const
		{
			return (m_Pointer == other.m_Pointer) && (m_Count == other.m_Count);
		}

		Node* m_Pointer;
		UI32 m_Count;
	};


	std::atomic<CtPtr> m_Top;
};

#include "LockFreeStack.inl"

#endif // !LOCKFREESTACK_H
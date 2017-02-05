template <typename T>
LockFreeStack<T>::LockFreeStack()
	: m_Top(CtPtr())
{
}

template <typename T>
LockFreeStack<T>::~LockFreeStack()
{
}

template<typename T>
void LockFreeStack<T>::Push(T value)
{
	CtPtr top = m_Top.load();

	CtPtr newCounterPtr = CtPtr(new Node(value));

	do
	{
		newCounterPtr.m_Count = top.m_Count + 1;
		newCounterPtr.m_Pointer->m_Next = top.m_Pointer;
	} while (!m_Top.compare_exchange_strong(top, newCounterPtr));
}

template<typename T>
bool LockFreeStack<T>::Pop(T& value)
{
	CtPtr top = m_Top.load();
	CtPtr newTop;

	do
	{
		if (top.m_Pointer == nullptr) // empty
		{
			return false;
		}

		newTop.m_Count = top.m_Count + 1;
		newTop.m_Pointer = top.m_Pointer->m_Next; // next and assign it as the new top
	} while (!m_Top.compare_exchange_strong(top, newTop));

	value = top.m_Pointer->m_Data;
	delete top.m_Pointer;

	return true;
}

template<typename T>
bool LockFreeStack<T>::IsEmpty() const
{
	return m_Top.load().m_Pointer == nullptr;
}

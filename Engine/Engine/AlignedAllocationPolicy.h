#ifndef ALIGNEDALLOCATIONPOLICY_H
#define ALIGNEDALLOCATIONPOLICY_H

template<size_t Alignment>
class AlignedAllocationPoilicy
{
public:
	AlignedAllocationPoilicy() {};
	virtual ~AlignedAllocationPoilicy() {};

	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, Alignment);
	}

	static void operator delete(void* memory)
	{
		_aligned_free(memory);
	}
};

#endif // !ALIGNEDALLOCATIONPOLICY_H

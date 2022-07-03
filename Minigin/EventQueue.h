#pragma once
#include "RingBuffer.h"

template<class T>
class EventQueue
{
public:
	EventQueue(size_t size)
		:m_pRingBuffer{ std::make_shared<RingBuffer<T>>(size) }
	{}

	void PutInQueue(T event)
	{
		m_pRingBuffer->put(event);
	}
	T CallEvent()
	{
		return m_pRingBuffer->get();
	}
	void Reset()
	{
		m_pRingBuffer->reset();
	}
	bool empty() const
	{
		return m_pRingBuffer->empty();
	}
	bool full() const
	{
		return m_pRingBuffer->full();
	}
	size_t capacity() const
	{
		return m_pRingBuffer->capacity();
	}
	size_t size() const
	{
		return m_pRingBuffer->size();
	}

private:
	std::shared_ptr<RingBuffer<T>> m_pRingBuffer;
};

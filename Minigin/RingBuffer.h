#pragma once
#include <mutex>

template <class T>
class RingBuffer {
public:
	explicit RingBuffer(size_t size) :
		m_pBuffer(std::unique_ptr<T[]>(new T[size])),
		m_maxSize(size)
	{}

	void put(T item)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		m_pBuffer[m_head] = item;

		if (m_full)
		{
			m_tail = (m_tail + 1) % m_maxSize;
		}

		m_head = (m_head + 1) % m_maxSize;

		m_full = m_head == m_tail;
		/*if(m_head == m_tail){
			m_full = true;
		}else{
			m_full = false;
		}*/
	}
	T get()
	{
		std::lock_guard<std::mutex> lock(mutex_);

		if (empty())
		{
			return T();
		}

		//Read data and advance the tail (we now have a free space)
		auto val = m_pBuffer[m_tail];
		m_full = false;
		m_tail = (m_tail + 1) % m_maxSize;

		return val;
	}
	void reset()
	{
		std::lock_guard<std::mutex> lock(mutex_);
		m_head = m_tail;
		m_full = false;
	}
	bool empty() const
	{
		return (!m_full && (m_head == m_tail));
	}
	bool full() const
	{
		return m_full;
	}
	size_t capacity() const
	{
		return m_maxSize;
	}
	size_t size() const
	{
		size_t size = m_maxSize;

		if (!m_full)
		{
			if (m_head >= m_tail)
			{
				size = m_head - m_tail;
			}
			else
			{
				size = m_maxSize + m_head - m_tail;
			}
		}

		return size;
	}

private:
	std::mutex mutex_;
	std::unique_ptr<T[]> m_pBuffer;
	size_t m_head = 0;
	size_t m_tail = 0;
	const size_t m_maxSize;
	bool m_full = false;
};

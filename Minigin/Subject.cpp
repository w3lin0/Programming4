#include "MiniginPCH.h"
#include "Subject.h"

Subject::Subject()
	:m_pHead(nullptr)
{
}

void Subject::addObserver(std::shared_ptr<Observer> observer)
{
	observer->m_pNext = m_pHead;
	m_pHead = observer;
}
void Subject::removeObserver(std::shared_ptr<Observer> observer)
{
	if (m_pHead == observer)
	{
		m_pHead = observer->m_pNext;
		observer->m_pNext = nullptr;
		return;
	}

	std::shared_ptr<Observer> current = m_pHead;
	while (current != nullptr)
	{
		if (current->m_pNext == observer)
		{
			current->m_pNext = observer->m_pNext;
			observer->m_pNext = nullptr;
			return;
		}

		current = current->m_pNext;
	}
}

void Subject::notify(std::shared_ptr<dae::GameObject> entity, Event event)
{
	std::shared_ptr<Observer> observer = m_pHead;
	while (observer != nullptr)
	{
		observer->Notify(entity, event);
		observer = observer->m_pNext;
	}
}

#pragma once
#include "GameObject.h"

enum class Event;
class Observer {
	friend class Subject;

public:
	Observer()
		:m_pNext(nullptr)
	{}

	virtual ~Observer() = default;
	virtual void Notify(std::shared_ptr<dae::GameObject> entity, Event event) = 0;

private:
	std::shared_ptr<Observer> m_pNext;
};
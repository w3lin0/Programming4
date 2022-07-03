#pragma once
#include "Observer.h"
#include "GameObject.h"

class Subject
{
public:
	Subject();

	void addObserver(std::shared_ptr<Observer> observer);
	void removeObserver(std::shared_ptr<Observer> observer);

	void notify(std::shared_ptr<dae::GameObject> entity, Event event);

private:
	std::shared_ptr<Observer> m_pHead;
};


export module Subject;

import Event;
import Observer;
import std.core;

export class Subject
{
public:
	void notify(const Event& event);
	void subscribe(const std::string& type, std::shared_ptr<Observer> observer);
	void unsubscribe(const std::string& type, std::shared_ptr<Observer> observer);
private:
	std::map<std::string, std::weak_ptr<Observer>> _subscribers;
};

void Subject::notify(const Event& event)
{
	_subscribers.at(event.type()).lock()->on_event(event);
}

void Subject::subscribe(const std::string& type, std::shared_ptr<Observer> observer)
{
	_subscribers[type] = observer;
}

void Subject::unsubscribe(const std::string& type, std::shared_ptr<Observer> observer)
{
	_subscribers[type] = std::weak_ptr<Observer>();
}
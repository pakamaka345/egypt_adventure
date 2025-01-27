//
// Created by pakamaka345 on 1/27/25.
//

#include "EventManager.hpp"
#include <sstream>
#include <algorithm>

void EventManager::addEvent(EventType type, const std::string& message)
{
	std::lock_guard lock(mutex);
	if (events.size() >= maxEvents) {
		events.pop_front();
	}
	events.push_back({type, message});

	notifyObservers(type, message);
}

std::deque<Event> EventManager::getAllEvents() const
{
	return events;
}

std::vector<Event> EventManager::getEvents(EventType type) const
{
	std::vector<Event> filteredEvents;
	for (const auto& event : events) {
		if (event.type == type) {
			filteredEvents.push_back(event);
		}
	}

	return filteredEvents;
}

std::string EventManager::formatInteractEvents() const
{
	std::ostringstream oss;
	std::for_each(events.begin(), events.end(), [&oss](const Event& event)
	{
		if (event.type == EventType::Interaction) {
			oss << event.message << " ";
		}
	});

	return oss.str();
}


void EventManager::clearEvents()
{
	std::lock_guard lock(mutex);
	events.clear();
}

void EventManager::subscribe(const std::function<void(EventType, const std::string&)>& observer)
{
	observers.push_back(observer);
}

void EventManager::notifyObservers(EventType type, const std::string& message)
{
	for (const auto& observer : observers) {
		observer(type, message);
	}
}






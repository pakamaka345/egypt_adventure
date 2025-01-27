//
// Created by pakamaka345 on 1/27/25.
//

#pragma once
#include <string>
#include <deque>
#include <functional>
#include <vector>
#include <mutex>

enum class EventType
{
	Interaction,
	Combat,
	System
};

struct Event
{
	EventType type;
	std::string message;
};

class EventManager {
public:
	static EventManager& getInstance()
	{
		static EventManager instance;
		return instance;
	}

	EventManager(EventManager const&) = delete;
	void operator=(EventManager const&) = delete;

	void addEvent(EventType type, const std::string& message);
	std::deque<Event> getAllEvents() const;

	std::vector<Event> getEvents(EventType type) const;
	std::string formatInteractEvents() const;
	std::string formatCombatEvents() const;
	std::string formatSystemEvents() const;

	void clearEvents();

	void subscribe(const std::function<void(EventType, const std::string&)>& observer);

private:
	EventManager(const size_t maxEvents = 15) : maxEvents(maxEvents) {}

	void notifyObservers(EventType type, const std::string& message);

	size_t maxEvents;
	std::deque<Event> events;
	std::vector<std::function<void(EventType, const std::string&)>> observers;
	mutable std::mutex mutex;
};



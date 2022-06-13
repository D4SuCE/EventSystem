#pragma once
#include "event.h"

namespace Core
{
	class KeyPressedEvent : public Event
	{
	private:
		int key;
	public:
		KeyPressedEvent(int key)
			:
			Event("Key pressed Event", Event::EventType::KEY_PRESSED_EVENT),
			key(key) {}
	public:
		std::string format() const override
		{
			std::string formatted = name + ": " + (char)key;
			return formatted;
		}
	};

	class KeyReleasedEvent : public Event
	{
	private:
		int key;
	public:
		KeyReleasedEvent(int key)
			:
			Event("Key released Event", Event::EventType::KEY_RELEASED_EVENT),
			key(key) {}
	public:
		std::string format() const override
		{
			std::string formatted = name + ": " + (char)key;
			return formatted;
		}
	};
}
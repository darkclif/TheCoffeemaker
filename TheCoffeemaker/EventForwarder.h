#pragma once
#include <SFML/Window.hpp>

#include <map>

template <typename I, typename O>
class EventForwarder
{
public:
	void registerForward(sf::Event::EventType _eventType, std::is_function<bool(sf::Event&)> _func);
	void registerForward(sf::Keyboard::Key _key, std::is_function<bool(sf::Event&)> _func);

	void handleForward(sf::Event& _event);

	EventForwarder();
	~EventForwarder();

private:

	std::map < sf::Event::EventType, > eventMapper;
};


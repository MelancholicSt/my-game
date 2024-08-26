#include "EventListener.h"

#include <iostream>
#include <source_location>
EventListener::EventListener()
{
    this->initialize();
}

EventListener::~EventListener()
{
    delete this->event_;
    delete this-> event_handlers_;
    delete this->listener_thread_;
}

void EventListener::initialize()
{
    this->listener_thread_ = nullptr;
    this->event_ = new sf::Event;
    this->event_handlers_ = new std::map<sf::Event::EventType, std::vector<std::function<void()>>>; 
}

bool EventListener::is_event_type_listens(sf::Event::EventType event_type) const
{
    return this -> event_handlers_ -> count(event_type) != 0;
}


void EventListener::bind(sf::Event::EventType event_type, const std::function<void()>& callback)
{
    std::vector<std::function<void()>>* callbacks_ptr;
    if(!this->is_event_type_listens(event_type))
    {
        callbacks_ptr = new std::vector<std::function<void()>> {callback};
        this->event_handlers_->insert({event_type, *callbacks_ptr});
        return;
    }
    callbacks_ptr = &this->event_handlers_->find(event_type)->second;
    callbacks_ptr->push_back(callback);
}

void EventListener::unbind(sf::Event::EventType event_type)
{
    if(!this->is_event_type_listens(event_type))
        return;
    
    this->event_handlers_->erase(event_type);
}



void EventListener::unbind(sf::Event::EventType event_type, const std::function<void()>& callback)
{
    if(!this->is_event_type_listens(event_type)) return;
    
    std::vector<std::function<void()>>* callbacks_ptr = &this->event_handlers_->find(event_type)->second;
    std::function<bool(std::function<void()>)> are_functions_equal = [callback, this](const std::function<void()>& fn)->bool
    {
  
        return this->getAddress(callback) == this->getAddress(fn);
    };

    for(auto it = callbacks_ptr->begin(); it != callbacks_ptr->end(); ++it)
    {
        if(are_functions_equal(*it))
        {
            callbacks_ptr->erase(it);
            return;
        }
    }
    
}


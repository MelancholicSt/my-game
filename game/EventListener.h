#pragma once
#include <functional>
#include <map>
#include <thread>
#include <vector>

#include "SFML/Window/Event.hpp"


class EventListener
{
public:
    EventListener();
    ~EventListener();
    void bind(sf::Event::EventType event_type, const std::function<void()>& callback);
    void unbind(sf::Event::EventType event_type);
    void unbind(sf::Event::EventType event_type, const std::function<void()>& callback);
private:
    std::thread* listener_thread_;
    sf::Event* event_;
    std::map<sf::Event::EventType, std::vector<std::function<void()>>>* event_handlers_;
    
    void initialize();
    void check_events();
    bool is_event_type_listens(sf::Event::EventType) const;
    template<typename T, typename... U>
    size_t getAddress(std::function<T(U...)> f) {
        typedef T(fnType)(U...);
        fnType ** fnPointer = f.template target<fnType*>();
        return (size_t) *fnPointer;
        
    }
    // template<typename T, typename... U>
    // size_t get_address(std::function<T(U...)> f)
    // {
    //     typedef T(fnType)(U...);
    //     
    //     fnType ** fnPointer = f.template target<fnType*>();
    //     return *fnPointer;
    // }
};

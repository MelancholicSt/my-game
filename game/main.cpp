

#include <iostream>

#include "EventListener.h"
void on_win_closed()
{
    std::cout << "a";
}
void on_not_closed()
{
    std::cout << 'b';
}
int main(int argc, char* argv[])
{
    EventListener* listener = new EventListener;
    
    listener->bind(sf::Event::Closed, on_win_closed);
    listener->unbind(sf::Event::Closed, on_win_closed);
    return 0;
}

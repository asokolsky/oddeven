
#pragma once
#include <iostream>
#include <sstream>
#include <functional>
#include <map>
#include <vector>
#include <mutex>

namespace assignment
{

typedef std::function<void()> EventHandler;

/**
 * Note: this is different from what you may expect of EventBus
 * design pattern, e.g. https://timnew.me/blog/2014/12/06/typical-eventbus-design-patterns/
 * Here main APIs are add and invoke by spec.
 */
class EventBus
{

public:
    EventBus()
    {
    }

    ~EventBus()
    {
    }

    /**
     * Add an event handler for a given named event
     */
    void add( const std::string& ename, EventHandler ehandler )
    {
        std::lock_guard<std::mutex> g(_m);

        auto result = _ename2handlers.find( ename );
        if(result != _ename2handlers.end()) 
            result->second.push_back( ehandler );
        else 
            _ename2handlers[ename] = { ehandler };
    }


    /**
     * Given an event name, call its event handlers
     */
    void invoke( const std::string& ename ) // const
    {
        std::lock_guard<std::mutex> g(_m);

        auto result = _ename2handlers.find( ename );
        if(result != _ename2handlers.end())
            for( auto handler: result->second )
                handler();
    }

    std::ostream& implement_output( std::ostream& os ) // const
    {
        std::lock_guard<std::mutex> g(_m);

        os << "<< EventBus {";
        for( auto k: _ename2handlers )
        {
            os << k.first << ":" << k.second.size() << " ";
        }
        return os << "} >>";
    }

    void reset()
    {
        std::lock_guard<std::mutex> g(_m);
        _ename2handlers.clear();
    }

private:
    std::map< std::string, std::vector<EventHandler> > _ename2handlers;
    std::mutex _m;
};

std::ostream& operator<<(std::ostream& os, /*const*/ EventBus &eb)
{
    return eb.implement_output( os );
}

}; // namespace

#pragma once
#include <map>
#include <vector>
#include <mutex>

/**
 *  Counter by endpoint
 */
class EndpointCounter
{
public:
    EndpointCounter() {}
    ~EndpointCounter() {}

    /**
     * Count an endoint execution.
     */
    void count( const char *fname ) 
    {
        std::lock_guard<std::mutex> g(_m);

        auto result = _fname2counter.find( fname );
        if(result == _fname2counter.end()) 
            _fname2counter[ fname ] = 1;
        else
            result->second++;
    }
    /**
     * How many times was fname counted?
     */ 
    int get_count( const char *fname ) // const
    {
        std::lock_guard<std::mutex> g(_m);
        auto result = _fname2counter.find( fname );
        if(result != _fname2counter.end()) 
            return result->second;
        return 0;
    }
    /** clear the counter */
    void reset()
    {
        std::lock_guard<std::mutex> g(_m);
        _fname2counter.clear();
    }

private:
    /** counter by endpoint */
    std::map< std::string, int > _fname2counter;
    /** _fname2counter guard */
    std::mutex _m;
};

#include <utility>
#include <vector>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <math.h> 

using namespace std;

vector <pair<int, int>> ClosestDestinationsRadius(const vector <pair<int, int>> &ds, double r)
{
    vector <pair<int, int>> res;
    for(auto &elt : ds)
    {
        int x = elt.first;
        int y = elt.second;
        double d = sqrt(x*x + y*y);
        if(d <= r)
            res.push_back(elt);
    }
    return res;
}


/**
 * Amazon Interview Q1
 * 
 * Given an array of N possible destinations
 * create delivery plan for the closest X destinations.
 * Truck starts at [0,0]
 */
vector <pair<int, int> > ClosestXdestinations(
    int numDestinations, /** tot number of destinations */
    int** allLocations, /** delivery destination */
    int numDeliveries)
{
    vector <pair<int, int>> allDestinations;
    for(int i = 0; i < numDestinations; ++i)
    {
        pair <int, int> dest(allLocations[i][0], allLocations[i][1]);
        allDestinations.push_back(dest);
    }
    // by now allDestinations has a copy of allLocations
    int iRadius = 1;
    int iDeliveries = 0;
    for(double iRadius = 1; iRadius < 10000; ++iRadius)
    {
        vector <pair<int, int>> ds = ClosestDestinationsRadius(allDestinations, iRadius);
        if(ds.size() >= numDeliveries)
        {
            //return ds;
            vector <pair<int, int>> ds1 = ClosestDestinationsRadius(allDestinations, iRadius - 0.5);
            return (ds1.size() >= numDeliveries) ? ds1 : ds;
        }
    }
    // we failed!
    allDestinations.empty();
    return allDestinations;
}

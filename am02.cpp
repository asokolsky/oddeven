#include <utility>
#include <vector>
#include <set>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <math.h> 

using namespace std;
const int inf = 10000;

int minimumDistance(int numRows, int numColumns, int **area, int x, int y, set<pair<int,int>> path, int d)
{
    if((x < 0) || (y < 0) || (x >= numColumns) || (y >= numRows) || (area[x][y] == 0))
        return inf;
    if(area[x][y] == 9)
        return d;
    pair<int,int>here(x, y);
    if(path.count(here) > 0)
        return inf;
    path.insert(here);
    // for a given x, y we can move up/down/left/right
    int dUp = minimumDistance(numRows, numColumns, area, x, y-1, path, d+1);
    int dDn = minimumDistance(numRows, numColumns, area, x, y+1, path, d+1);        
    int dLeft = minimumDistance(numRows, numColumns, area, x-1, y, path, d+1);
    int dRight = minimumDistance(numRows, numColumns, area, x+1, y, path, d+1);

    int iRes = inf;
    if(iRes > dUp) iRes = dUp;
    if(iRes > dDn) iRes = dDn;
    if(iRes > dLeft) iRes = dLeft;
    if(iRes > dRight) iRes = dRight;
    return iRes;
}

/**
 * Amazon Interview Q2
 * 
 * area is a 2D array on numColumns x numRows
 * In area 1 denotes road, 0 denotes unpassable area, 9 destination
 * Travel from top left and get to the destination in shortest route possible.
 **/
int minimumDistance(int numRows, int numColumns, int **area)
{
    set<pair<int,int>> path;
    return minimumDistance(numRows, numColumns, area, 0, 0, path, 0);
}

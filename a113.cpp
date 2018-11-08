#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float a, b, c;
    cin >> a >> b >> c;
    if(a == 0)
    {
        if(b != 0) 
        {
            float x = (-c) / b;
            cout << x;
        }
        return 0;
    }
    float D = (b*b) - 4*a*c;
    if(D < 0)
        return 0;
    if(D == 0)
    {
        float x = (-b) / (2*a);
        cout << x;
    }
    else
    {
        float x = ((-b) + sqrt(D))/ (2*a);
        cout << x << " ";
        x = ((-b) - sqrt(D))/ (2*a);
        cout << x;
    }      
    return 0;
}

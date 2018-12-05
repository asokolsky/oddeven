#include <map>
#include <iostream>

using namespace std;

int main() 
{ 
    map<int, int> mp; 
    // insert elements in random order 
    mp.insert({ 2, 30 }); 
    mp.insert({ 1, 10 }); 
    mp.insert({ 5, 50 }); 
    mp.insert({ 4, 40 }); 
    for(auto it = mp.begin(); it != mp.end(); ++it) { 
        cout << it->first << "." << it->second << endl; 
    } 
    // when 2 is present 
    auto it = mp.lower_bound(2); 
    cout << "The lower bound of key 2 is " << it->first << "." << it->second << endl;
    if(it == mp.end()) cout << "We are at the end" << endl;

    // when 3 is not present 
    // points to next greater after 3 
    it = mp.lower_bound(3); 
    cout << "The lower bound of key 3 is " << it->first << "." << it->second << endl;
    if(it == mp.end()) cout << "We are at the end" << endl;

    // when 6 exceeds 
    it = mp.lower_bound(6); 
    cout << "The lower bound of key 6 is " << it->first << "." << it->second << endl;
    if(it == mp.end()) cout << "We are at the end" << endl;

    // when 0 exceeds 
    it = mp.lower_bound(0); 
    cout << "The lower bound of key 0 is " << it->first << "." << it->second << endl;
    if(it == mp.end()) cout << "We are at the end" << endl;

    return 0; 
} 

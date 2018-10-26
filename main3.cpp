#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>
#include <condition_variable>

class VarWithGuard
{
public:
  VarWithGuard(int initVal) : 
    _val(initVal)
  {  
  }
  int get() 
  {
    return _val;
  }
  /**
   *  equivalent of  ++var;
   */
  int inc() 
  {
    std::lock_guard<std::mutex> g(_m);
    int iRes = ++_val;
    _cv.notify_all();
    return iRes;
  }

  using ValueCondition = bool(int /* _val */);

  void waitTill(ValueCondition cond)
  {
    std::unique_lock<std::mutex> lck(_m);
    while(!cond(_val))
    {
      //std::cout << ".";
      _cv.wait(lck);    
    }
    // by now vc(_val) is true;
  }

private:
  int _val;
  std::mutex _m;
  std::condition_variable _cv; // wait on this till _val change
};

VarWithGuard x(0);

int main() 
{
  const int iMaxCount = 100;
  std::thread odd([]() {
    for(;;) {
      x.waitTill([](int v) { return (v%2) !=0; }); // isOdd
      std::cout << "1";
      if(x.get() >= iMaxCount)
        break;
      if(x.inc() >= iMaxCount)
        break;
    }});

  std::thread even([]() {
    for(;;) {
      x.waitTill([](int v) { return (v%2) ==0; }); // isEven
      std::cout << "0";    
      if(x.get() >= iMaxCount)
        break;
      if(x.inc() >= iMaxCount)
        break;
    }});
    
  std::cout << "Main is waiting for threads to complete their job...\n";
  // ...
  even.join();
  odd.join();
  std::cout << "\nx=" << x.get() <<"\ndone!\n";
  return 0;
}

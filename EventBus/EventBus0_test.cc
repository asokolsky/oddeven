#include <ctime>
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
#include <random>
#include <gtest/gtest.h>
#include "EventBus0.hh"
#include "EndpointCounter.hh"

using namespace assignment;

/** THE event bus to test */
EventBus eb;

/** counter for executeXXX calls */
EndpointCounter ec;

void executeNew()
{
  ec.count( "NewEmail" );
}
void executeTrash()
{
  ec.count( "TrashEmail" );
}
void executeReply()
{
  ec.count( "ReplyEmail" );
}

TEST(EventBusTest00, BasicSingleThreaded) 
{
  ec.reset();
  EXPECT_EQ( ec.get_count( "NewEmail" ), 0);
  EXPECT_EQ( ec.get_count( "TrashEmail" ), 0);
  EXPECT_EQ( ec.get_count( "ReplyEmail" ), 0);

  eb.reset();
  eb.add("NewEmail", executeNew);
  eb.add("TrashEmail", executeTrash);
  eb.add("NewEmail", executeNew);
  eb.add("ReplyEmail", executeReply);
  
  std::cout << eb << std::endl;

  eb.invoke("NewEmail");
  eb.invoke("TrashEmail");

  EXPECT_EQ( ec.get_count( "NewEmail" ), 2 );
  EXPECT_EQ( ec.get_count( "TrashEmail" ), 1 );
  EXPECT_EQ( ec.get_count( "ReplyEmail" ), 0 );
}

/** events to play with */
const char *enames[] = {
  "NewEmail",
  "TrashEmail",
  "ReplyEmail"
};
/** # of elements in the above array */
const size_t uEvents = sizeof(enames) / sizeof(enames[0]);

/** eventhandlers in the same order as above */
EventHandler ehandlers[] = {
  executeNew,
  executeTrash,
  executeReply,
};

/** counting add calls */
EndpointCounter ac;

std::random_device rd;  // Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
/** distributon of random indexes in enames */
std::uniform_int_distribution<> distrib(0, uEvents-1);

/**
 * Keep adding events to the event bus
 */
void AdderThreadProc( unsigned duration )
{
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  using std::chrono::seconds;
  using std::chrono::system_clock;

  auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  auto finish = now + duration;
  while( duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() < finish )
  {
    size_t uEvent = distrib(gen); // random index in enames
    //std::cout << uEvent << std::endl;
    auto ename = enames[uEvent];
    //std::cout << ename << std::endl;
    eb.add( ename, ehandlers[uEvent]);
    ac.count( ename );
    // sleep if only to force context switch
    std::this_thread::sleep_for(milliseconds(1));
  }
}

TEST(EventBusTest01, BasicMultiThreaded) 
{
  // global reset
  ac.reset();
  ec.reset();
  eb.reset();

  // expect total calm
  for( size_t i = 0; i<uEvents; i++)
  {
    EXPECT_EQ( ec.get_count( enames[i] ), 0);
    EXPECT_EQ( ac.get_count( enames[i] ), 0);
  }
  // start adding from multiple threads
  std::vector< std::thread > adders;
  int iAdders = 4;
  unsigned duration = 1 * 1000; // duration of the test in milliseconds
  for( int i =0; i< iAdders; i++ )
  {
    // these work with ExecuteCounter ac
    std::thread adder( AdderThreadProc, duration );
    adders.push_back( std::move( adder ) );
  }

  // messaround for upto duration ms

  for(std::thread &adder: adders)
    adder.join();

  std::cout << eb << std::endl;
  
  // ensure we collected all the posted events
  for( size_t i = 0; i<uEvents; i++)
    eb.invoke( enames[i] );

  // verify that ac and ec are the same
  for( size_t i = 0; i<uEvents; i++)
  {
    EXPECT_EQ( ec.get_count( enames[i] ), ac.get_count( enames[i] ));
  }


}


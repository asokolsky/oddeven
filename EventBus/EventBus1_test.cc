#include <ctime>
#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
#include <random>
#include <gtest/gtest.h>
#include "EventBus1.hh"
#include "EndpointCounter.hh"

using namespace assignment;

EventBus eb;
EndpointCounter ec;

void executeNew( const std::string& arg )
{
  ec.count( "NewEmail" );
}
void executeTrash( const std::string& arg )
{
  ec.count( "TrashEmail" );
}
void executeReply( const std::string& arg )
{
  ec.count( "ReplyEmail" );
}
void executeAttachment( const std::string& arg )
{
  ec.count( "AddAttachment" );
}

TEST(EventBusTest10, BasicSingleThreaded) 
{
  ec.reset();
  EXPECT_EQ( ec.get_count( "NewEmail" ), 0);
  EXPECT_EQ( ec.get_count( "TrashEmail" ), 0);
  EXPECT_EQ( ec.get_count( "ReplyEmail" ), 0);
  EXPECT_EQ( ec.get_count( "AddAttachment" ), 0);

  eb.reset();
  eb.add("NewEmail", executeNew);
  eb.add("TrashEmail", executeTrash);
  eb.add("NewEmail", executeNew);
  eb.add("ReplyEmail", executeReply);
  eb.add("AddAttachment", executeAttachment);

  std::cout << eb << std::endl;

  eb.invoke("NewEmail", "");
  eb.invoke("TrashEmail", "");
  eb.invoke("AddAttachment", "path/to/attachment");

  EXPECT_EQ( ec.get_count( "NewEmail" ), 2 );
  EXPECT_EQ( ec.get_count( "TrashEmail" ), 1 );
  EXPECT_EQ( ec.get_count( "ReplyEmail" ), 0 );
  EXPECT_EQ( ec.get_count( "AddAttachment" ), 1 );
}

// events to play with
const char *enames[] = {
  "NewEmail",
  "TrashEmail",
  "ReplyEmail",
  "AddAttachment"
};
// eventhandlers in the same order as above
EventHandler ehandlers[] = {
  executeNew,
  executeTrash,
  executeReply,
  executeAttachment
};

// # of elements in the above array
const size_t uEvents = sizeof(enames) / sizeof(enames[0]);

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
    auto ename = enames[uEvent];
    //std::cout << ename << std::endl;
    eb.add( ename, ehandlers[uEvent]);
    ac.count( ename );
    // sleep short random period
  }
}

TEST(EventBusTest11, BasicMultiThreaded) 
{
  eb.reset();
  ac.reset();
  ec.reset();
  for( size_t i = 0; i<uEvents; i++)
  {
    EXPECT_EQ( ec.get_count( enames[i] ), 0);
    EXPECT_EQ( ac.get_count( enames[i] ), 0);
  }

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
    eb.invoke( enames[i], "" );

  // verify that ac and ec are the same
  for( size_t i = 0; i<uEvents; i++)
  {
    EXPECT_EQ( ec.get_count( enames[i] ), ac.get_count( enames[i] ));
  }
}

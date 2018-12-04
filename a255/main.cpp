#include <iostream>
#include <stdexcept>
#include "database.h"
#include "node.h"
#include "condition_parser.h"
#include "test_runner.h"

using namespace std;

string trimLeading(const string& str) 
{
  const std::string whitespace = " \t";
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content
  return str.substr(strBegin);
}
/*std::string trimLeadingAndTrailing(const std::string& str)
{
  const std::string whitespace = " \t";
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content
  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;
  return str.substr(strBegin, strRange);
}*/

string ParseEvent(istream& is) {
  string str;
  getline(is, str);
  return trimLeading(str);
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() 
{
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}

int main() 
{
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }
  return 0;
}


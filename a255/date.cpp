#include <iomanip>
#include "date.h"
#include "test_runner.h"

Date::Date(int y, int m, int d) : _y(y), _m(m), _d(d) 
{
  if(_m <= 0 || _m > 12)
      throw(invalid_argument("Month value is invalid: " + to_string(_m)));
  if(_d <= 0 || _d > 31)
      throw(invalid_argument("Day value is invalid: " + to_string(_d)));
}

bool operator<(const Date& lhs, const Date& rhs)
{
  int ly = lhs.GetYear();
  int ry = rhs.GetYear();
  if(ly != ry)
    return ly < ry;
  int lm = lhs.GetMonth();
  int rm = rhs.GetMonth();
  if(lm != rm)
    return lm < rm;
  return lhs.GetDay() < rhs.GetDay();
}
bool operator>(const Date& lhs, const Date& rhs)
{
  int ly = lhs.GetYear();
  int ry = rhs.GetYear();
  if(ly != ry)
    return ly > ry;
  int lm = lhs.GetMonth();
  int rm = rhs.GetMonth();
  if(lm != rm)
    return lm > rm;
  return lhs.GetDay() > rhs.GetDay();
}
bool operator==(const Date& lhs, const Date& rhs) {
  return (lhs.GetYear() == rhs.GetYear())
    && (lhs.GetMonth() == rhs.GetMonth())
    && (lhs.GetDay() == rhs.GetDay());
}

std::ostream& operator<<(std::ostream& os, const Date &obj)
{
  return os << setfill('0') << setw (4) << obj.GetYear() 
    << "-" << setfill('0') << setw (2) << obj.GetMonth() 
    << "-" << setfill('0') << setw (2) << obj.GetDay();
}
std::istream& operator>>(std::istream& is, Date &obj)
{
  string strDate;
  is >> strDate;
  stringstream in(strDate);
  int y = -100, m = -100, d = -100;
  char ch1,ch2;
  in >> y >> ch1 >> m >> ch2 >> d;
  if((y == -100) || (ch1 != '-') || (m == -100) || (ch2 != '-') || (d == -100) || !isdigit(strDate[strDate.size() - 1]))
    throw(invalid_argument("Wrong date format: " + strDate));
  Date res(y,m,d);
  // read obj from stream
  //if(ch != '-') is.setstate(std::ios::failbit);
  //else
    obj = res;
  return is;
}

Date ParseDate(std::istream& is)
{
  Date res;
  is >> res;
  return res;
}

void TestDate()
{
    {
        istringstream is("2017-01-01");
        Date date;
        is >> date;
        ostringstream os;
        os << date;
        AssertEqual("2017-01-01", os.str(), "serialiaze/desrialize date");
    }
    {
        istringstream is("   2017-01-01");
        Date date;
        is >> date;
        ostringstream os;
        os << date;
        AssertEqual("2017-01-01", os.str(), "serialiaze/desrialize date, with leading spaces");
    }
    {
        Assert(  Date{2017, 1, 1} == Date{2017, 1, 1},  "==");
        Assert(!(Date{2017, 1, 1} == Date{2017, 1, 2}), "!==");
        Assert(!(Date{2017, 1, 1} == Date{2017, 2, 1}), "!==");
        Assert(!(Date{2017, 1, 1} == Date{2018, 1, 1}), "!==");
        Assert(!(Date{2017, 1, 2} == Date{2017, 1, 1}), "!==");
        Assert(!(Date{2017, 2, 1} == Date{2017, 1, 1}), "!==");
        Assert(!(Date{2018, 1, 1} == Date{2017, 1, 1}), "!==");

        Assert(  Date{2017, 1, 1} != Date{2017, 1, 2},  "!=");
        Assert(  Date{2017, 1, 1} != Date{2017, 2, 1},  "!=");
        Assert(  Date{2017, 1, 1} != Date{2018, 1, 1},  "!=");
        Assert(  Date{2017, 1, 2} != Date{2017, 1, 1},  "!=");
        Assert(  Date{2017, 2, 1} != Date{2017, 1, 1},  "!=");
        Assert(  Date{2018, 1, 1} != Date{2017, 1, 1},  "!=");
        Assert(!(Date{2017, 1, 1} != Date{2017, 1, 1}), "!!=");

        Assert(  Date{2017, 1, 1} <= Date{2017, 1, 1},  "<=");
        Assert(  Date{2017, 1, 1} <= Date{2017, 1, 2},  "<=");
        Assert(  Date{2017, 1, 1} <= Date{2017, 2, 1},  "<=");
        Assert(  Date{2017, 1, 1} <= Date{2018, 1, 1},  "<=");
        Assert(!(Date{2017, 1, 2} <= Date{2017, 1, 1}), "!<=");
        Assert(!(Date{2017, 2, 1} <= Date{2017, 1, 1}), "!<=");
        Assert(!(Date{2018, 1, 1} <= Date{2017, 1, 1}), "!<=");

        Assert(  Date{2017, 1, 1} <  Date{2017, 1, 2},  "<");
        Assert(  Date{2017, 1, 1} <  Date{2017, 2, 1},  "<");
        Assert(  Date{2017, 1, 1} <  Date{2018, 1, 1},  "<");
        Assert(!(Date{2017, 1, 1} <  Date{2017, 1, 1}), "!<");
        Assert(!(Date{2017, 1, 2} <  Date{2017, 1, 1}), "!<");
        Assert(!(Date{2017, 2, 1} <  Date{2017, 1, 1}), "!<");
        Assert(!(Date{2018, 1, 1} <  Date{2017, 1, 1}), "!<");

        Assert(  Date{2017, 1, 1} >= Date{2017, 1, 1} , ">=");
        Assert(  Date{2017, 1, 2} >= Date{2017, 1, 1} , ">=");
        Assert(  Date{2017, 2, 1} >= Date{2017, 1, 1} , ">=");
        Assert(  Date{2018, 1, 1} >= Date{2017, 1, 1} , ">=");
        Assert(!(Date{2017, 1, 1} >= Date{2017, 1, 2}), "!>=");
        Assert(!(Date{2017, 1, 1} >= Date{2017, 2, 1}), "!>=");
        Assert(!(Date{2017, 1, 1} >= Date{2018, 1, 1}), "!>=");

        Assert(  Date{2017, 1, 2} >  Date{2017, 1, 1} , ">");
        Assert(  Date{2017, 2, 1} >  Date{2017, 1, 1} , ">");
        Assert(  Date{2018, 1, 1} >  Date{2017, 1, 1} , ">");
        Assert(!(Date{2017, 1, 1} >  Date{2017, 1, 1}), "!>");
        Assert(!(Date{2017, 1, 1} >  Date{2017, 1, 2}), "!>");
        Assert(!(Date{2017, 1, 1} >  Date{2017, 2, 1}), "!>");
        Assert(!(Date{2017, 1, 1} >  Date{2018, 1, 1}), "!>");
    }
}


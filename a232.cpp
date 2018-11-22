#include "phone_number.h"
#include <stdexcept>

//#include <string>

/**
 *  Принимает строку в формате +XXX-YYY-ZZZZZZ
    Часть от '+' до первого '-' - это код страны.
    Часть между первым и вторым символами '-' - код города
    Всё, что идёт после второго символа '-' - местный номер.
    Код страны, код города и местный номер не должны быть пустыми.
    Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

    Примеры:
    * +7-495-111-22-33
    * +7-495-1112233
    * +323-22-460002
    * +1-2-coursera-cpp
    * 1-2-333 - некорректный номер - не начинается на '+'
    * +7-1233 - некорректный номер - есть только код страны и города
*/
PhoneNumber::PhoneNumber(const string &international_number)
{
  if(international_number.size() < 6 || international_number[0] != '+')
    throw invalid_argument("bad PhoneNumber constructor");
  size_t posFirstDash = international_number.find_first_of("-", 1);
  if(posFirstDash == std::string::npos)
    throw invalid_argument("bad PhoneNumber constructor");
  country_code_ = international_number.substr(1, posFirstDash-1);

  size_t posSecondDash = international_number.find_first_of("-", posFirstDash+1);
  if(posSecondDash == std::string::npos)
    throw invalid_argument("bad PhoneNumber constructor");
  city_code_ = international_number.substr(posFirstDash+1, posSecondDash-posFirstDash-1);
  local_number_ = international_number.substr(posSecondDash+1);

  if(country_code_.empty() || city_code_.empty() || local_number_.empty())
    throw invalid_argument("bad PhoneNumber constructor");
}

string PhoneNumber::GetCountryCode() const
{
  return country_code_;
}
string PhoneNumber::GetCityCode() const
{
  return city_code_;
}
string PhoneNumber::GetLocalNumber() const
{
  return local_number_;
}
string PhoneNumber::GetInternationalNumber() const
{
  return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}
/*
int main()
{
  PhoneNumber n1("+7-495-111-22-33");

  PhoneNumber n2("+1-2-coursera-cpp");

  return 0;
}
*/

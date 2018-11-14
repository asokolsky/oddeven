#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <system_error>
#include <map>
#include <stdexcept>

using namespace std;

/**
Вам дана функция string AskTimeServer(), про которую известно следующее:

    в процессе своей работы она обращается по сети к удалённому серверу, запрашивая текущее время;
    если обращение к серверу прошло успешно, функция возвращает текущее время в виде строки;
    если в процессе обращения к серверу возникла сетевая проблема, функция выбрасывает исключение system_error;
    функция может выбрасывать другие исключения, чтобы сообщить о других проблемах.

Используя функцию AskTimeServer, напишите класс TimeServer со следующим интерфейсом:

class TimeServer {
public:
  string GetCurrentTime();
private:
  string LastFetchedTime = "00:00:00";
};

Метод GetCurrentTime должен вести себя так:

    он должен вызвать функцию AskTimeServer, записать её результат в поле LastFetchedTime и вернуть значение этого поля;
    если AskTimeServer выбросила исключение system_error, метод GetCurrentTime должен его поймать 
    и вернуть текущее значение поля LastFetchedTime. Таким образом мы скрываем от пользователя сетевые проблемы, 
    возвращая значение, которое было получено при последнем успешном обращении к серверу;
    если AskTimeServer выбросила другое исключение, метод GetCurrentTime должен пробросить его дальше, 
    потому что в рамках класса TimeServer мы не знаем, как обрабатывать проблемы, не связанные со сбоями сети.

Как выполнять задание

Вам дан файл, содержащий заготовку класса TimeServer. В нём вам надо реализовать метод GetCurrentTime так, как описано выше. 
Файл содержит пустую функцию AskTimeServer. Для тестирования своей реализации вы можете пробовать добавлять разные команды в её тело:

    возврат строки;
    выброс исключения system_error (класс system_error принимает в конструкторе параметр типа error_code, 
    поэтому самый простой способ выбросить это исключение — throw system_error(error_code());, 
    подробнее см. http://www.cplusplus.com/reference/system_error/system_error);
    выброс других исключений.

 * 
 */

/* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
    * нормальный возврат строкового значения
    * выброс исключения system_error
    * выброс другого исключения с сообщением.
*/
string AskTimeServer() 
{
  static int i = 0;
  i++;
  if(i%3 ==1)
    return "00:00:" + to_string(i%60);
  else if(i%3 ==2)
    throw system_error(error_code());
  throw range_error("random error");
}

class TimeServer {
public:
       /* Реализуйте этот метод:
            * если AskTimeServer() вернула значение, запишите его в LastFetchedTime и верните
            * если AskTimeServer() бросила исключение system_error, верните текущее значение
            поля LastFetchedTime
            * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
        */
    string GetCurrentTime() 
    {
      try {
        string res = AskTimeServer();
        LastFetchedTime = res;
      } catch (system_error &err) {
        ;
      }
      return LastFetchedTime;
    }

private:
    string LastFetchedTime = "00:00:00";
};
/*
int main() {
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
      for(int i = 0; i < 10; i++)
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
*/

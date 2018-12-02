#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <cmath>



using namespace std;

/**
В Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур.

Как видно из кода, есть два вида команд:

    ADD — добавить фигуру в набор;
    PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.

Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:

    ADD RECT width height — добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
    ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
    ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).

Не меняя функцию main, реализуйте недостающие функции и классы:

    базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
    классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
    функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle>
    или shared_ptr<Circle>.

Гарантируется, что все команды ADD корректны; 
размеры всех фигур — это натуральные числа не больше 1000. 
В качестве значения π используйте 3,14.

Как будет тестироваться ваш код

Автоматическая проверяющая система заменит в вашей программе функцию main на ту, 
которая приведена в условии задачи, скомпилирует получившийся файл и прогонит на наборе тестов. 
Кроме того, отдельно проверяется, что функция CreateFigure возвращает объект, созданный с помощью make_shared<Rect>, 
если во входном потоке задан прямоугольник, объект, созданный с помощью make_shared<Circle>, 
если во входном потоке задан круг, и т. д.

 */
const double PI = 3.14;

/** базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area; */
class Figure
{
public:
  Figure() {}
  virtual const char *Name() = 0;
  virtual double Perimeter() = 0;
  virtual double Area() = 0;
};

/** классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы; */
class Circle : public Figure
{
  int _r;
public:
  Circle(int r) : _r(r), Figure() {}

  const char *Name() {
    return "CIRCLE";
  }
  double Perimeter() {
    return 2*PI*_r;
  }
  double Area() {
    return PI*_r*_r;
  }
};
class Rect : public Figure
{
  int _w;
  int _h;
public:
  Rect(int w, int h) : _w(w), _h(h), Figure() {}

  const char *Name() {
    return "RECT";
  }
  double Perimeter() {
    return 2*(_w + _h);
  }
  double Area() {
    return _w*_h;
  }
};
class Triangle : public Figure
{
  int _a;
  int _b;
  int _c;
public:
  Triangle(int a, int b, int c) : _a(a), _b(b), _c(c), Figure() {}

  const char *Name() {
    return "TRIANGLE";
  }
  double Perimeter() {
    return _a + _b + _c;
  }
  double Area() {
    double semip = Perimeter() / 2;
    return sqrt(semip * (semip-_a) * (semip-_b) * (semip-_c));
  }
};

/**
 * функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle>
    или shared_ptr<Circle>.
  */
shared_ptr<Figure> CreateFigure(istringstream &is)
{
    string figure;
    is >> figure;
    if(figure == "CIRCLE")
    {
      int r;
      is >> r;
      return make_shared<Circle>(r);
    }
    if(figure == "RECT")
    {
      int w, h;
      is >> w >> h;
      return make_shared<Rect>(w,h);
    }
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a,b,c);
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}

/*
Input:
ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT

Output:
RECT 10.000 6.000
TRIANGLE 12.000 6.000
RECT 60.000 200.000
CIRCLE 31.400 78.500
*/

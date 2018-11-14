#include <iostream>
#include <vector>

using namespace std;

/**
Реализуйте рассказанный на лекции класс Function, позволяющий создавать, вычислять и инвертировать функцию, состоящую из следующих элементарных операций:

    прибавить вещественное число x;
    вычесть вещественное число x.

При этом необходимо объявить константными все методы, которые по сути такими являются.
 * 
 */
class FunctionPart
{
public: 
  FunctionPart(char op, double v) : _op(op), _v(v) {}

  double Apply(double src) const
  {
    if(_op == '+')
      return src + _v;
    else 
      return src - _v;

  }
  void Invert()
  {
    if(_op == '+')
      _op = '-';
    else
      _op = '+';

  }
private:
  char _op;
  double _v;
};

class Function
{
public:
  void AddPart(char op, double v)
  {
    _parts.push_back({op, v});
  }
  double Apply(double v) const
  {
    for(const FunctionPart &part: _parts)
      v = part.Apply(v);
    return v;
  }
  void Invert()
  {
    for(FunctionPart &part: _parts)
      part.Invert();
    reverse(begin(_parts), end(_parts));
  }
private:
  vector <FunctionPart> _parts;
};
/*
struct Image 
{
  double quality;
  double freshness;
  double rating;
};

struct Params 
{
  double a;
  double b;
  double c;
};

Function MakeWeightFunction(const Params& params,
                            const Image& image) 
{
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) 
{
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) 
{
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() 
{
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}
*/
/*
36
20
*/
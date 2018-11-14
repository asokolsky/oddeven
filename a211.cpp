#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

/**
В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. 
   
Вам дана заготовка решения, а также пример ввода и вывода. Когда вы реализуете класс Matrix, вы можете использовать этот пример, 
чтобы убедиться, что ваш код работает правильно.

Важно! Пример не проверяет выполнение всех требований, приведённых в условии.

Автор задачи — Дмитрий Минченко
 */
class Matrix
{
public:
  /** конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов */
  Matrix() {}
  /** 
   * конструктор от двух целочисленных параметров: num_rows и num_cols, — 
   * которые задают количество строк и столбцов матрицы соответственно 
   * */
  Matrix(int rows, int cols)
  {
    Reset(rows, cols);
  }
  /**
   * метод Reset, принимающий два целочисленных параметра, которые задают количество строк и столбцов матрицы соответственно
   * Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, 
   * то должно быть выброшено стандартное исключение out_of_range.
   * Reset must zero out all elements.
   */
  void Reset(int rows, int cols)
  {
    if(rows < 0)
      throw out_of_range("Negative row#!");
    if(cols < 0)
      throw out_of_range("Negative col#!");
    _rows.resize(rows);
    _cols = cols;
    /*
    for(auto &row : _rows)
      row.resize(cols);
    for(int i = 0; i < rows; ++i)
      for(int j = 0; j < cols; ++j)
        _rows[i][j] = 0;
        */
    _rows.assign(rows, vector<int>(cols));
}
  /**
   * константный метод At, который принимает номер строки и номер столбца 
   * (именно в этом порядке; нумерация строк и столбцов начинается с нуля)
   * и возвращает значение в соответствущей ячейке матрицы.
   * Это же исключение out_of_range должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
   */
  int At(int row, int col) const
  {
    if(row < 0 || row >= _rows.size())
      throw out_of_range("Row out of range!");
    if(col < 0 || col >= _rows[0].size())
      throw out_of_range("Col out of range!");
    return _rows[row][col];
  }
  /**
   * неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
   * Это же исключение out_of_range должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
   */
  int& At(int row, int col)
  {
    if(row < 0 || row >= _rows.size())
      throw out_of_range("Row out of range!");
    if(col < 0 || col >= _rows[0].size())
      throw out_of_range("Col out of range!");
    return _rows[row][col];
  }
  /** 
   * константные методы GetNumRows и GetNumColumns, 
   * которые возвращают количество строк и столбцов матрицы соответственно
   */
  int GetNumRows() const
  {
    return _rows.size();
  }
  int GetNumColumns() const
  {
    return _cols;
  }
  /**
   * оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой; 
   * если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.
   */
  Matrix operator+(const Matrix &rhs) const
  {
    int rows = GetNumRows();
    if(rows != rhs.GetNumRows())
      throw invalid_argument("Matrixes row# is different");
    int cols = GetNumColumns();
    if(cols != rhs.GetNumColumns())
      throw invalid_argument("Matrixes col# is different");
    Matrix res(rows,cols);
    for(int i = 0; i < rows; ++i)
      for(int j = 0; j < cols; ++j)
        res.At(i, j) = _rows[i][j] + rhs.At(i, j);
    return res;
  }
private:
  vector<vector<int>> _rows;
  int _cols = 0;
};

/**
 * оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер 
 * и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
 */
inline bool operator==(const Matrix &lhs, const Matrix &rhs) 
{
  int rows = lhs.GetNumRows();
  int cols = lhs.GetNumColumns();
  if((rows != rhs.GetNumRows())  || (cols != rhs.GetNumColumns()))
    return false;
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
      if(lhs.At(i, j) != rhs.At(i, j))
        return false;
  return true;
}
/**
 * оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, 
 * — в первой строке количество строк и столбцов, 
 * во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
 */
std::ostream& operator<<(std::ostream& os, const Matrix &obj)
{
  int rows = obj.GetNumRows();
  int cols = obj.GetNumColumns();
  os << rows << " " << cols << endl;
  for(int i = 0; i < rows; ++i)
  {
    for(int j = 0; j < cols; ++j)
      os << obj.At(i, j) << " ";
    os << endl;
  }
  return os;
}

/**
 *  оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), 
 *  а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
 */
std::istream& operator>>(std::istream& is, Matrix &obj)
{
  int rows, cols;
  is >> rows >> cols;
  obj.Reset(rows, cols);
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
    {
      int cell;
      is >> cell;
      obj.At(i, j) = cell;
    }
  return is;
}

int main() 
{
  try {
    Matrix one, two;
    cin >> one >> two;
    cout << "one: " << one << endl;
    cout << "two: " << two << endl;
    cout << "one+two: " << one + two << endl;
  } catch (out_of_range x) {
    cout << "out_of_range: " << x.what() << endl;
  } catch (invalid_argument x) {
    cout << "invalid_argument: " << x.what() << endl;
  }
  return 0;
}




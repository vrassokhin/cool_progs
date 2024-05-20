#include "vector.h"
#include <limits>

using namespace std;

int main() {
  MyVector<int> intVector1;
  MyVector<int> intVector2;
  MyVector<string> stringVector;

  int intElement;
  while (true) {
    cout << "Введите целое число для первого вектора (-1 чтобы выйти): ";

    if (!(cin >> intElement)) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "ошибка" << endl;
      continue;
    }

    intVector1.push_back(intElement);

    if (intElement == -1) {
      intVector1.pop_back();
      break;
    }
  }

  while (true) {
    cout << "Введите целое число для второго вектора (-1 чтобы выйти): ";

    if (!(cin >> intElement)) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "ошибка" << endl;
      continue;
    }

    intVector2.push_back(intElement);

    if (intElement == -1) {
      intVector2.pop_back();
      break;
    }
  }

  string stringElement;
  while (true) {
    cout << "Введите строку (\"exit\" чтобы выйти): ";

    if (!(cin >> stringElement)) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "ошибка" << endl;
      continue;
    }

    stringVector.push_back(stringElement);

    if (stringElement == "exit") {
      stringVector.pop_back();
      break;
    }
  }

  cout << endl << intVector1 << endl << intVector2 << endl << stringVector << endl;

  MyVector<MyVector<int>> vectorVector;
  vectorVector.push_back(intVector1);
  vectorVector.push_back(intVector2);

  cout << endl << vectorVector << endl;
  
  intVector1.sort();
  intVector2.sort();
  stringVector.sort();
  vectorVector.sort();

  cout << endl << "отсортированные: " << endl;
  cout << endl << "вектор1: " << intVector1 
       << endl << "вектор2: " << intVector2 
       << endl << "вектор из строк: " << stringVector 
       << endl << "вектор из векторов: " << vectorVector << endl;

  vectorVector.pop_back();
  cout << endl << "убрали вектор: " << vectorVector << endl;

  return 0;
}

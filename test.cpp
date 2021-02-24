#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>

// В данной лабораторной работе пока можно не писать каждый раз "std::".
using namespace std;

// ---------------------------------------------------------------------------
// Задание 1. Сумма элементов массива.

double GetSum(const vector<double>& values) {
  double sum{0};
  for (double value : values) {
    sum += value;
  }
  return sum;
}

// ---------------------------------------------------------------------------
// Задание 2. Магическая сумма матрицы.

int NumberOfOnes(uint32_t number) {
  int number_of_ones{0};
  while (number != 0) {
    number = number & (number - 1);
    ++number_of_ones;
  }
  return number_of_ones;
}

uint32_t GetMagicXor(const vector<uint32_t>& array) {
  uint32_t sum{0};
  for (uint32_t i : array) {
    int number_of_ones = NumberOfOnes(i);
    if (number_of_ones <= 4) {
      sum = sum ^ i;
    }
  }
  sum = ~sum;
  return sum;
}

vector<uint32_t> GetMagicXor(const vector<vector<uint32_t>>& values) {
  int number_of_rows = values.size();
  vector<uint32_t> result(number_of_rows);
  for (size_t row = 0; row < values.size(); ++row) {
    result.at(row) = GetMagicXor(values.at(row));
  }
  return result;
}

// ---------------------------------------------------------------------------
// Задание 3. Точка на плоскости

const double kEps = 10e-8;

// Функция возвращает номер Вашего варианта.
int GetVariant() {
  return 5;
}

// Функция определяет, лежит ли точка в указанной области.
bool IsPointInRange(double x, double y) {
  if (x >= -6 && x <= 6 && y >= -6 && y <= 6) {
    return true;
  } else {
    return false;
  }
}

bool IsPointInArea(double x, double y) {
  if (!IsPointInRange(x, y)) {
    return false;
  }
  if ((y + kEps >= 0) && (tan(x / 2) <= y + kEps) && (x + kEps >= y * y - 1.5
      * y - 2.5) && (x < 3)) {
    return true;
  } else if ((x > -3) && (y <= -2 * x - 7 + kEps) && (y <= tan(x / 2) + kEps)) {
    return true;
  } else if ((x > 3) && (x * x + y * y <= 25 + kEps) && (y <= tan(x / 2) +
      kEps)) {
    return true;
  } else {
    return false;
  }
}

// ---------------------------------------------------------------------------
// Задание 4. Сортировки

void SelectionSort(vector<string>& array) {
  if (array.size() < 2) {
    return;
  }
  int index_of_min_element;
  for (int i = 0; i < array.size() - 1; ++i) {
    index_of_min_element = i;
    for (int j = i + 1; j < array.size(); ++j) {
      if (array.at(j) < array.at(index_of_min_element)) {
        index_of_min_element = j;
      }
    }
    swap(array.at(i), array.at(index_of_min_element));
  }
}

void InsertionSort(vector<string>& array) {
  if (array.size() < 2) {
    return;
  }
  for (int i = 1; i < array.size(); ++i) {
    int j = i;
    string copy_of_element = array.at(i);
    while (j > 0 && array.at(j - 1) > copy_of_element) {
      array.at(j) = array.at(j - 1);
      --j;
    }
    array.at(j) = copy_of_element;
  }
}

void BubbleSort(vector<string>& array) {
  if (array.size() < 2) {
    return;
  }
  int number_of_elements = array.size();
  for (int i = 0; i < number_of_elements - 1; ++i) {
    for (int j = number_of_elements - 1; j > i; --j) {
      if (array.at(j - 1) > array.at(j)) {
        swap(array.at(j - 1), array.at(j));
      }
    }
  }
}

void ShakerSort(vector<string>& array) {
  if (array.size() < 2) {
    return;
  }
  int right_element = array.size() - 1;
  int left_element = 0;
  do {
    for (int i = left_element; i < right_element; ++i) {
      if (array.at(i + 1) < array.at(i)) {
        swap(array.at(i+1), array.at(i));
      }
    }
    --right_element;
    for (int i = right_element; i > left_element; --i) {
      if (array.at(i - 1) > array.at(i)) {
        swap(array.at(i - 1), array.at(i));
      }
    }
    ++left_element;
  } while (left_element < right_element);
}
// ---------------------------------------------------------------------------
// Задание 5. Бинарный поиск

int Recursion(const vector<int>& array, int number, int first_element, int
last_element) {
  int middle = (first_element + last_element) / 2;
  if (last_element < first_element) {
    return -1;
  }
  if (array.at(middle) < number) {
    return Recursion(array, number, middle + 1, last_element);
  } else if (array.at(middle) > number) {
    return Recursion(array, number, first_element, middle - 1);
  } else {
    return middle;
  }
}

int FindRecursively(const vector<int>& array, int number) {
  int first_element{0};
  int last_element = array.size() - 1;
  int result = Recursion(array, number, first_element, last_element);
  return result;
}

int FindIteratively(const vector<int>& array, int number) {
  int first_element = 0;
  int last_element = array.size() - 1;
  int middle;
  while (first_element <= last_element) {
    middle = (first_element + last_element) / 2;
    if (array.at(middle) < number) {
      first_element = middle + 1;
    } else if (array.at(middle) > number) {
      last_element = middle - 1;
    } else {
      return middle;
    }
  }
  return -1;
}

#ifndef IGNORE_SOLUTION_MAIN
int main() {
  // ---------------------------------------------------------------------
  // Тут Вы можете написать код для тестирования Вашего решения.
  // При проверке в системе всё содержимое в данном блоке будет игнорироваться.

  // Ниже даны некоторые очевидные тесты для демонстрации принципа работы.
  // Разумеется, они не покрывают все случаи, но позволяют понять формат,
  // в котором будут использоваться написанные Вами функции.

  {
    // Задание 1.
    // std::vector<double> values = {1, 1.5 - 42.42};
    // double values_sum = GetSum(values);
    // assert(values_sum == -39.92);
  }
  {
    // Задание 2.
    // vector<vector<uint32_t>> matrix{{3, 5}, {7, 5}};
    // vector<uint32_t> values(2);
    // values = GetMagicXor(matrix);
    // for (unsigned int value : values) {
    //   cout << value << " ";
    // }
    // std::vector<uint32_t> input_1d = {0x1111, 0x0111, 0x0011, 0x0001};
    // uint32_t output_1d = GetMagicXor(input_1d);
    // assert(output_1d == 0xFFFFEFEF);

    // auto result = GetMagicXor(
    //     {
    //         {0x1111, 0x0111, 0x0011, 0x0001,},
    //         {0x0000FFFF, 0x11111111, 0x01010101, 0x0F000F00,},
    //     });
    //
    // assert(result.size() == 2);
    // assert(result[0] == 0xFFFFEFEF);
    // assert(result[1] == 0xFEFEFEFE);
  }
  {
    // Задание 3.
    // assert(GetVariant() == -1);
    // double x{2.52};
    // double y{3};
    // if (IsPointInArea(x, y)) {
    //   cout << "Yes" << endl;
    // } else {
    //   cout << "No" << endl;
    // }
    // double x{4.3};
    // double y{-0.8};
    // while (x < 5) {
    //   if (IsPointInArea(x, y)) {
    //     cout << "+" << " ";
    //   } else {
    //     cout << "-" << " " << x << " ";
    //   }
    //   x += 0.001;
    // }
    // cout << endl;
    // cout << x << endl;

    // assert(!IsPointInArea(1.23, 4.56));
    // assert(IsPointInArea(-1.23, -4.56));
  }
  {
    // Задание 4.
    // vector<string> values = {
    //     "abacabadabacaba",
    //     "abacaba",
    //     "aaaaaaa",
    // };
    // SelectionSort(values);
    // InsertionSort(values);
    // BubbleSort(values);
    // ShakerSort(values);
    // for (auto element: values) {
    //   std::cout << element << " ";
    // }
    // assert(values == vector<string>(
    //     {"aaaaaaa", "abacaba", "abacabadabacaba"}));
    // vector<string> values;
    // ShakerSort(values);
    // for (auto element: values) {
    //   std::cout << element << " ";
    // }


  }

  {
    // Задание 5.
    vector<int> values = {1, 2, 3, 4, 5};
    // values.resize(1000);
    // int number;
    // std::cout << "Enter number" << std::endl;
    // std::cin >> number;
    // int result = FindRecursively(values, number);
    // cout << result;
    //
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10'000'000; ++i) {
      // assert(FindRecursively(values, 1) == 0);
      // assert(FindRecursively(values, 2) == 1);
      // assert(FindRecursively(values, 3) == 2);
      // assert(FindRecursively(values, 4) == 3);
      assert(FindRecursively(values, 5) == 4);
      // assert(FindRecursively(values, 42) == -1);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "Recursive search test finished in "
         << std::chrono::duration<double>(finish - start).count()
         << " seconds.\n";
    //
    // auto start = std::chrono::high_resolution_clock::now();
    // for (int i = 0; i < 10'000'000; ++i) {
    //   // assert(FindIteratively(values, 1) == 0);
    //   // assert(FindIteratively(values, 2) == 1);
    //   // assert(FindIteratively(values, 3) == 2);
    //   // assert(FindIteratively(values, 4) == 3);
    //   // assert(FindIteratively(values, 5) == 4);
    //   assert(FindIteratively(values, 42) == -1);
    // }
    //   auto finish = std::chrono::high_resolution_clock::now();
    //   cout << "Iterative search test finished in "
    //        << std::chrono::duration<double>(finish - start).count()
    //        << " seconds.\n";
  }
  {
    // srand(time(0));
    // vector<string> values(10000);
    // for (int i = 0; i < 10000; ++i) {
    //   values[i]=char(int('a') + rand() % 26);
    // }
    // std::sort(values.begin(), values.end(), [](string first, string second) {
    //   return first > second;
    // });
    //
    // vector<string> copy1 = values;
    //
    // auto start = std::chrono::high_resolution_clock::now();
    // ShakerSort(values);
    // auto finish = std::chrono::high_resolution_clock::now();
    //
    // cout << ". Time: "
    //      << std::chrono::duration<double>(finish - start).count() << '\n';
    // int index_of_min_element;
    // int number_of_comparisons{0};
    // int number_of_exchanges{0};
    // for (int i = 0; i < copy1.size() - 1; ++i) {
    //   index_of_min_element = i;
    //   for (int j = i + 1; j < copy1.size(); ++j) {
    //     ++number_of_comparisons;
    //     if (copy1.at(j) < copy1.at(index_of_min_element)) {
    //       index_of_min_element = j;
    //     }
    //   }
    //   swap(copy1.at(i), copy1.at(index_of_min_element));
    //   ++number_of_exchanges;
    // }

    // int number_of_comparisons{0};
    // int number_of_exchanges{0};
    // for (int i = 1; i < copy1.size(); ++i) {
    //   int j = i;
    //   string copy_of_element = copy1.at(i);
    //   ++number_of_comparisons;
    //   while (j > 0 && copy1.at(j - 1) > copy_of_element) {
    //     ++number_of_comparisons;
    //     copy1.at(j) = copy1.at(j - 1);
    //     ++number_of_exchanges;
    //     --j;
    //   }
    //   copy1.at(j) = copy_of_element;
    // }

    // int number_of_elements = copy1.size();
    // int number_of_comparisons{0};
    // int number_of_exchanges{0};
    // for (int i = 0; i < number_of_elements - 1; ++i) {
    //   for (int j = number_of_elements - 1; j > i; --j) {
    //     ++number_of_comparisons;
    //     if (copy1.at(j - 1) > copy1.at(j)) {
    //       ++number_of_exchanges;
    //       swap(copy1.at(j - 1), copy1.at(j));
    //     }
    //   }
    // }

    // int right_element = copy1.size() - 1;
    // int left_element = 0;
    // int number_of_comparisons{0};
    // int number_of_exchanges{0};
    // do {
    //   for (int i = left_element; i < right_element; ++i) {
    //     ++number_of_comparisons;
    //     if (copy1.at(i + 1) < copy1.at(i)) {
    //       ++number_of_exchanges;
    //       swap(copy1.at(i+1), copy1.at(i));
    //     }
    //   }
    //   --right_element;
    //   for (int i = right_element; i > left_element; --i) {
    //     ++number_of_comparisons;
    //     if (copy1.at(i - 1) > copy1.at(i)) {
    //       ++number_of_exchanges;
    //       swap(copy1.at(i - 1), copy1.at(i));
    //     }
    //   }
    //   ++left_element;
    // } while (left_element < right_element);
    // cout << "Number of comparisons " << number_of_comparisons << " , number "
    //                                                              "of "
    //                                                              "exchanges "
    //      <<
    //      number_of_exchanges << endl;

  }
  {
    // srand(time(0));
    // vector<int> values(1000);
    // for (int i = 0; i < 1000; ++i) {
    //   values[i]=rand() % 100;
    // }
    // sort(values.begin(), values.end());
    // int number = 56;
    // auto start = std::chrono::high_resolution_clock::now();
    // FindRecursively(values, number);
    // auto finish = std::chrono::high_resolution_clock::now();
    // cout << "Recursive search test finished in "
    //      << std::chrono::duration<double>(finish - start).count()
    //      << " seconds.\n";
    //
    // // auto start = std::chrono::high_resolution_clock::now();
    // //   int result = FindIteratively(values, number);
    // //   auto finish = std::chrono::high_resolution_clock::now();
    // //   cout << "Iterative search test finished in "
    // //        << std::chrono::duration<double>(finish - start).count()
    // //        << " seconds.\n";

  }

  // ---------------------------------------------------------------------
}
#endif  // IGNORE_SOLUTION_MAIN


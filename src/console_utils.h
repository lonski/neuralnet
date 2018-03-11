#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <iostream>
#include <vector>

void clear_cin() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
T getNumber(const std::string& msg) {
  std::cout << msg << "\n>";
  T val;
  while (!(std::cin >> val)) {
    clear_cin();
    std::cout << "Invalid input. Try again.\n>";
  }
  return val;
}

template <typename T>
std::vector<T> getVector(const std::string& msg) {
  std::string line;

  std::cout << msg << " (enter numbers separated with spaces)\n>";
  std::getline(std::cin, line);

  T number;
  std::vector<T> numbers;
  std::istringstream stream(line);
  while (stream >> number)
    numbers.push_back(number);

  return numbers;
}

bool getBool(const std::string& msg) {
  std::cout << msg << " [t/n]\n>";
  std::string s;
  std::cin >> s;
  return s == "t";
}

#endif

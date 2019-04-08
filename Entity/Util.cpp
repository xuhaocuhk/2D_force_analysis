//
// Created by 徐豪 on 2017/4/13.
//
#include <iostream>
#include <sstream>
#include <string>

template <class T>
  std::string ConvertToString(T value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}


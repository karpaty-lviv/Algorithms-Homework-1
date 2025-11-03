// Sorting using standart sorting function

#include "Task3_S5_1.h"
#include <algorithm>  // for std::sort
#include <functional>

void SorterS5_Standard::sort(std::vector<Student> &students)
{
    std::sort(students.begin(), students.end(),
              [](const Student &a, const Student &b)
              {
                  return a.m_group < b.m_group;
              });
}
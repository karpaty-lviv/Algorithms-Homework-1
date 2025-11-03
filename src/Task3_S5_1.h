// Sorting using standart sorting function

#pragma once

#include "Student.h"
#include <vector>

class SorterS5_Standard
{
public:
    /**
     * @brief sort vector by using std::sort.
     */
    static void sort(std::vector<Student> &students);
};
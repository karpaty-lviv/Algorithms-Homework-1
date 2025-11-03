#pragma once

#include "Student.h"
#include <vector>

class SorterS5_Radix
{
public:
    /**
     * @brief sort students by m_group using Radix Sort (LSD).
     */
    static void sort(std::vector<Student> &students);

private:
    /**
     * @brief helper function counting sort.
     */
    static void countingSort(std::vector<Student> &students, int digit_index);
};

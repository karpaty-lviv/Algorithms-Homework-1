#include "Task3_S5_2.h"
#include <vector>

void SorterS5_Radix::countingSort(std::vector<Student> &students, int digit_index)
{
    int n = students.size();
    if (n == 0)
        return;

    const int RANGE = 256;

    std::vector<Student> output(n);
    std::vector<int> count(RANGE, 0);

    for (int i = 0; i < n; i++)
    {
        int char_val = (int)students[i].m_group[digit_index];
        count[char_val]++;
    }
    for (int i = 1; i < RANGE; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int char_val = (int)students[i].m_group[digit_index];
        int output_index = count[char_val] - 1;
        output[output_index] = students[i];
        count[char_val]--;
    }

    students = std::move(output);
}

void SorterS5_Radix::sort(std::vector<Student> &students)
{
    // each group has 6 symbols
    const int NUM_DIGITS = 6;
    for (int d = NUM_DIGITS - 1; d >= 0; d--)
    {
        countingSort(students, d);
    }
}

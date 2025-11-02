#pragma once

#include <string>
#include <vector>
#include "Student.h"

class CSVParser
{
public:
    static std::vector<Student> load(const std::string &filename);

    static void save(const std::string &filename, const std::vector<Student> &students);
};

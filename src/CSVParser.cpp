#include "CSVParser.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

std::vector<Student> CSVParser::load(const std::string &filename)
{
    std::vector<Student> students_vector;
    std::ifstream f(filename);

    if (!f.is_open()){
        std::cerr << "Cannot open the file";
        return students_vector;
    }

    std::string header_line;
    if (!std::getline(f, header_line))
    {
        std::cerr << "File is empty: " << filename << std::endl;
        return students_vector;
    }

    std::string line;
    while (std::getline(f, line)){
        std::stringstream ss(line);
        Student student;
        std::string word;
        size_t counter = 0; // we have 9 data points in the line
        while (std::getline(ss, word, ',')){
            switch (counter){
                case 0: // m_name
                    student.m_name = word;
                    break;
                case 1: // m_surname
                    student.m_surname = word;
                    break;
                case 2: // m_email
                    student.m_email = word;
                    break;
                case 3:
                    student.m_birth_year = std::stoull(word);
                    break;
                case 4:
                    student.m_birth_month = std::stoull(word);
                    break;
                case 5:
                    student.m_birth_day = std::stoull(word);
                    break;
                case 6:
                    student.m_group = word;
                    break;
                case 7:
                    student.m_rating = std::stof(word);
                    break;
                case 8:
                    student.m_phone_number = word;
                    break;
            }
            counter++;
        }
        students_vector.push_back(student);
    }
    f.close();
    return students_vector;
}

void CSVParser::save(const std::string &filename, const std::vector<Student> &students)
{
    // ...
    // твоя логіка запису
    // ...
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

#include "Student.h"
#include "CSVParser.h"

int main()
{
    // --- 1. Виклик парсера ---

    // Використаємо маленький файл для тесту.
    // Потім можеш замінити це на "students.csv" або "students_100000.csv"
    const std::string filename = "../data/students_100.csv";

    std::cout << "loading from " << filename << "..." << std::endl;

    // Викликаємо наш статичний метод load
    std::vector<Student> students_vector = CSVParser::load(filename);

    // Перевірка, чи завантажилось хоч щось
    if (students_vector.empty())
    {
        std::cerr << "error" << std::endl;
        return 1; // Вихід з помилкою
    }

    std::cout << "loading complete, number of students:  " << students_vector.size() << std::endl;

    // --- 2. Вивід перших 10 студентів ---

    std::cout << "\nfirst 10 students" << std::endl;

    // Визначаємо, скільки студентів виводити
    // (або 10, або менше, якщо у файлі менше 10 рядків)
    size_t count_to_print = std::min((size_t)10, students_vector.size());

    for (size_t i = 0; i < count_to_print; ++i)
    {
        // Отримуємо студента за індексом.
        // Використовуємо const&, щоб уникнути копіювання.
        const Student &s = students_vector[i];

        // Виводимо ключову інформацію
        std::cout << "[" << (i + 1) << "] "
                  << s.m_name << " " << s.m_surname
                  << " (Group: " << s.m_group << ")"
                  << ", Email: " << s.m_email
                  << ", Rating: " << s.m_rating << std::endl;
    }

    return 0; // Успішне завершення програми
}
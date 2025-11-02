#pragma once // Захист від подвійного включення

// --- Імпорти ---
#include "StudentDatabase.h" // Базовий клас (інтерфейс)
#include "Student.h"         // Для std::vector<Student>
#include <vector>            // Для m_students
#include <string>            // Для std::string
#include <unordered_map>     // Для m_email_to_index

// --- Структура класу ---
class Task2_V2_1 : public StudentDatabase
{
public:
    // --- Обов'язкові функції (з StudentDatabase) ---
    // Ми "перевизначаємо" (override) всі чисті віртуальні функції

    // Деструктор за замовчуванням
    virtual ~Task2_V2_1() = default;

    // Завантаження даних у наші приватні структури
    void load(const std::vector<Student> &students) override;

    // Операція 1 (V2): Знайти за днем народження
    std::vector<Student> findByBirthday(int month, int day) override;

    // Операція 2 (V2): Змінити групу за email
    bool updateGroup(const std::string &email, const std::string &newGroup) override;

    // Операція 3 (V2): Знайти групу з max. студентів в один день
    std::string findGroupWithMaxSharedBirthdays() override;

    // Допоміжні функції
    size_t getMemoryUsage() const override;
    const std::vector<Student> &getAllStudents() const override;

private:
    // --- Приватні дані (наша реалізація) ---

    // 1. Основне сховище. Всі студенти лежать тут.
    std::vector<Student> m_students;

    // 2. Індекс для миттєвого доступу за email (для Операції 2)
    // Key: email (std::string)
    // Value: індекс студента у векторі m_students (size_t)
    std::unordered_map<std::string, size_t> m_email_to_index;
};
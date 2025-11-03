#pragma once

#include "StudentDatabase.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>

class Task2_V2_2 : public StudentDatabase
{
public:
    virtual ~Task2_V2_2() = default;

    void load(const std::vector<Student> &students) override;
    std::vector<Student> findByBirthday(int month, int day) override;
    bool updateGroup(const std::string &email, const std::string &newGroup) override;
    std::string findGroupWithMaxSharedBirthdays() override;

    size_t getMemoryUsage() const override;
    const std::vector<Student> &getAllStudents() const override;

private:
    std::vector<Student> m_students;
    std::unordered_map<std::string, size_t> m_email_to_index;
    std::map<std::pair<int, int>, std::vector<size_t>> m_birthday_to_index;
};
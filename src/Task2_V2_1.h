#pragma once
#include "StudentDatabase.h" 
#include "Student.h"         
#include <vector>            
#include <string>           
#include <unordered_map>     


class Task2_V2_1 : public StudentDatabase
{
public:
    virtual ~Task2_V2_1() = default;
    void load(const std::vector<Student> &students) override;

    std::vector<Student> findByBirthday(int month, int day) override;

    bool updateGroup(const std::string &email, const std::string &newGroup) override;

    std::string findGroupWithMaxSharedBirthdays() override;

    size_t getMemoryUsage() const override;
    const std::vector<Student> &getAllStudents() const override;

private:
    std::vector<Student> m_students;

    std::unordered_map<std::string, size_t> m_email_to_index;
};
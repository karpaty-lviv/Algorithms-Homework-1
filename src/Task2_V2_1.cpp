#include "Task2_V2_1.h" 
#include <map>
#include <utility>
#include <limits> 


void Task2_V2_1::load(const std::vector<Student> &students)
{
    m_students.clear();
    m_email_to_index.clear();

    m_students = students;

    for (size_t i = 0; i < m_students.size(); ++i)
    {
        const std::string &email = m_students[i].m_email;
        m_email_to_index[email] = i;
    }
}

// operation 1 (slow, O(N))
std::vector<Student> Task2_V2_1::findByBirthday(int month, int day)
{
    std::vector<Student> results;
    for (const auto &student : m_students)
    {
        if (student.m_birth_month == month && student.m_birth_day == day)
        {
            results.push_back(student);
        }
    }
    return results;
}

// operation 1 (fast, O(1))
bool Task2_V2_1::updateGroup(const std::string &email, const std::string &newGroup)
{
    auto it = m_email_to_index.find(email);
    if (it == m_email_to_index.end())
    {
        return false;
    }
    size_t index = it->second;
    m_students[index].m_group = newGroup;
    return true;
}

// operation 3 (slow, O(N))
std::string Task2_V2_1::findGroupWithMaxSharedBirthdays()
{
    std::unordered_map<std::string, std::map<std::pair<int, int>, int>> stats;
    for (const auto &student : m_students)
    {
        stats[student.m_group][{student.m_birth_month, student.m_birth_day}]++;
    }

    std::string best_group = "";
    int max_count = 0;

    for (const auto &group_pair : stats)
    {
        for (const auto &date_pair : group_pair.second)
        {
            int current_count = date_pair.second;
            if (current_count > max_count)
            {
                max_count = current_count;
                best_group = group_pair.first;
            }
        }
    }
    return best_group;
}

const std::vector<Student> &Task2_V2_1::getAllStudents() const
{
    return m_students;
}

size_t Task2_V2_1::getMemoryUsage() const
{
    // Approximate memory usage
    size_t memory = sizeof(m_students) + (m_students.capacity() * sizeof(Student));
    memory += sizeof(m_email_to_index);
    return memory;
}
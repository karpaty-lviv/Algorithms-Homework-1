#include "Task2_V2_2.h"
#include <limits>

void Task2_V2_2::load(const std::vector<Student> &students)
{
    m_students.clear();
    m_email_to_index.clear();
    m_birthday_to_index.clear();

    m_students = students;

    for (size_t i = 0; i < m_students.size(); ++i)
    {
        m_email_to_index[m_students[i].m_email] = i;

        std::pair<int, int> birthday = {
            m_students[i].m_birth_month,
            m_students[i].m_birth_day};
        m_birthday_to_index[birthday].push_back(i);
    }
}

// operation 1 (fast, O(logN + k))
std::vector<Student> Task2_V2_2::findByBirthday(int month, int day)
{
    std::vector<Student> results;
    std::pair<int, int> target_birthday = {month, day};

    // find key in map O(logN))
    auto it = m_birthday_to_index.find(target_birthday);
    if (it == m_birthday_to_index.end())
    {
        return results;
    }

    const std::vector<size_t> &indices = it->second;

    // O(k)
    for (size_t index : indices)
    {
        results.push_back(m_students[index]);
    }

    return results;
}
// operation 2 (fast, O(1), without changes)
bool Task2_V2_2::updateGroup(const std::string &email, const std::string &newGroup)
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

// operation 3 (slow, O(N), without changes)
std::string Task2_V2_2::findGroupWithMaxSharedBirthdays()
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

const std::vector<Student> &Task2_V2_2::getAllStudents() const
{
    return m_students;
}

size_t Task2_V2_2::getMemoryUsage() const
{
    size_t memory = sizeof(m_students) + (m_students.capacity() * sizeof(Student));
    memory += sizeof(m_email_to_index);

    memory += sizeof(m_birthday_to_index);

    return memory;
}
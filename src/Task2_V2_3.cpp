#include "Task2_V2_3.h" 
#include <limits>       

void Task2_V2_3::load(const std::vector<Student> &students)
{
    m_students.clear();
    m_email_to_index.clear();
    m_group_stats.clear();

    m_students = students;

    for (size_t i = 0; i < m_students.size(); ++i)
    {
        // index for operation 2
        m_email_to_index[m_students[i].m_email] = i;

        // statisctics for operation 3
        const auto &s = m_students[i];
        std::pair<int, int> birthday = {s.m_birth_month, s.m_birth_day};
        const std::string &group = s.m_group;

        m_group_stats[group][birthday]++;
    }
}

// operation 1 (slow, O(N))
std::vector<Student> Task2_V2_3::findByBirthday(int month, int day)
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

// operation 2 (slower, O(logN))
bool Task2_V2_3::updateGroup(const std::string &email, const std::string &newGroup)
{
    auto it = m_email_to_index.find(email);
    if (it == m_email_to_index.end())
    {
        return false;
    }
    size_t index = it->second;
    const std::string &old_group = m_students[index].m_group;
    std::pair<int, int> birthday = {
        m_students[index].m_birth_month,
        m_students[index].m_birth_day};

    m_group_stats[old_group][birthday]--;

    m_group_stats[newGroup][birthday]++;

    m_students[index].m_group = newGroup;
    return true;
}

// operation 3 (fast)
std::string Task2_V2_3::findGroupWithMaxSharedBirthdays()
{
    std::string best_group = "";
    int max_count = 0;

    for (const auto &group_pair : m_group_stats)
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


const std::vector<Student> &Task2_V2_3::getAllStudents() const
{
    return m_students;
}

size_t Task2_V2_3::getMemoryUsage() const
{
    size_t memory = sizeof(m_students) + (m_students.capacity() * sizeof(Student));
    memory += sizeof(m_email_to_index);
    memory += sizeof(m_group_stats);
    return memory;
}
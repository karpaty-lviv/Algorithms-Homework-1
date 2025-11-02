#include "Student.h"
#include <vector>
#include <string>

class StudentDatabase
{
public:
    virtual ~StudentDatabase() = default;

    // load the data
    virtual void load(const std::vector<Student> &students) = 0;

    // V2.1
    virtual std::vector<Student> findByBirthday(int month, int day) = 0;

    // V2.2
    virtual bool updateGroup(const std::string &email, const std::string &newGroup) = 0;

    // V2.3
    virtual std::string findGroupWithMaxSharedBirthdays() = 0;

    // find how much memory was used
    virtual size_t getMemoryUsage() const = 0;

    // Taks 3, sorting
    virtual const std::vector<Student> &getAllStudents() const = 0;
};

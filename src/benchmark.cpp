#include "Benchmark.h"
#include <chrono> 
#include <random>
#include <vector>
#include <string>
#include <iostream>

BenchmarkResult Benchmark::run(StudentDatabase &db,
                               int seconds,
                               double ratioA,
                               double ratioB)
{
    const auto &all_students = db.getAllStudents();

    // generating random number
    std::mt19937 rng(std::random_device{}());

    // decide ehich option to choose (A, B or C)
    std::uniform_real_distribution<double> op_distribution(0.0, 1.0);

    // choose random student
    std::uniform_int_distribution<size_t> student_distribution(0, all_students.size() - 1);

    // setting a timer
    long long op_count = 0;

    long long op_count_A = 0;
    long long op_count_B = 0;
    long long op_count_C = 0;

    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = start_time + std::chrono::seconds(seconds);


    while (std::chrono::high_resolution_clock::now() < end_time)
    {
        double op_choice = op_distribution(rng);

        if (op_choice < ratioA)
        {
            size_t rand_index = student_distribution(rng);
            int month = all_students[rand_index].m_birth_month;
            int day = all_students[rand_index].m_birth_day;
            (void)db.findByBirthday(month, day);

            op_count_A++;
        }
        else if (op_choice < (ratioA + ratioB))
        {
            size_t rand_index = student_distribution(rng);
            const std::string &email = all_students[rand_index].m_email;

            size_t rand_index_2 = student_distribution(rng);
            const std::string &new_group = all_students[rand_index_2].m_group;

            (void)db.updateGroup(email, new_group);

            op_count_B++;
        }
        else
        {
            (void)db.findGroupWithMaxSharedBirthdays();
            op_count_C++;
        }
        op_count++;
    }

    size_t memory = db.getMemoryUsage();

    long long total_ops = op_count_A + op_count_B + op_count_C;
    return {total_ops, op_count_A, op_count_B, op_count_C, memory};
}
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <chrono>
#include <fstream>

#include "Student.h"
#include "StudentDatabase.h"
#include "CSVParser.h"
#include "Benchmark.h"
#include "Task2_V2_1.h"
#include "Task2_V2_2.h"
#include "Task2_V2_3.h"
#include "Task3_S5_1.h"
#include "Task3_S5_2.h"

int main()
{
    std::ofstream results_file("./data/results.csv");
    results_file << "Size,Variant,TotalOperations,OpsA_FindByBirthday,OpsB_UpdateGroup,OpsC_FindGroup,Memory\n";

    std::vector<std::string> filenames = {
        "./data/students_100.csv",
        "./data/students_1000.csv",
        "./data/students_10000.csv",
        "./data/students.csv" // 100 000
    };


    std::vector<size_t> data_sizes = {100, 1000, 10000, 100000};
    std::vector<std::string> variant_names = {"Variant_1_Base", "Variant_2_Op1_Opt", "Variant_3_Op3_Opt"};

    const double total_ratio = 10.0 + 100.0 + 10.0;
    const double ratioA = 10.0 / total_ratio;
    const double ratioB = 100.0 / total_ratio;

    for (size_t i = 0; i < filenames.size(); ++i)
    {
        const auto &filename = filenames[i];
        const auto data_size = data_sizes[i];

        std::cout << "========================================================\n";
        std::cout << "Testing file: " << filename << "\n";
        std::cout << "========================================================\n";

        std::vector<Student> data = CSVParser::load(filename);

        std::cout << "Loaded " << data.size() << " students.\n"
                  << std::endl;

        std::vector<std::unique_ptr<StudentDatabase>> databases;
        databases.push_back(std::make_unique<Task2_V2_1>());
        databases.push_back(std::make_unique<Task2_V2_2>());
        databases.push_back(std::make_unique<Task2_V2_3>());

        for (size_t db_index = 0; db_index < databases.size(); ++db_index)
        {
            auto &db = databases[db_index];
            const auto &variant_name = variant_names[db_index];

            std::cout << "--- Testing variant " << (db_index + 1) << " (" << variant_name << ") ---" << std::endl;

            db->load(data);

            std::cout << "Benchmark for 10 seconds" << std::endl;
            BenchmarkResult result = Benchmark::run(*db, 10, ratioA, ratioB);

            std::cout << "Result" << std::endl;
            int w = 35;
            std::cout << std::left << std::setw(w) << "  (A) findByBirthday:" << result.op_count_A << std::endl;
            std::cout << std::left << std::setw(w) << "  (B) updateGroup:" << result.op_count_B << std::endl;
            std::cout << std::left << std::setw(w) << "  (C) findGroupWithMaxSharedBirthdays:" << result.op_count_C << std::endl;
            std::cout << "  ------------------------------------------------------" << std::endl;
            std::cout << std::left << std::setw(w) << "  Operations:" << result.op_count_total << std::endl;
            std::cout << std::left << std::setw(w) << "  Memory usage:" << result.memory_used << std::endl;
            std::cout << std::endl;

            results_file << data_size << ","
                         << variant_name << ","
                         << result.op_count_total << ","
                         << result.op_count_A << ","
                         << result.op_count_B << ","
                         << result.op_count_C << ","
                         << result.memory_used << "\n";
        }
    }

    results_file.close();
    std::cout << "\nFile 'results.csv' saved.\n"
              << std::endl;

    std::cout << "========================================================\n";
    std::cout << "Task III: S5 (sorting by m_group)" << std::endl;
    std::cout << "========================================================\n";

    std::vector<Student> data_to_sort = CSVParser::load("./data/students.csv");

    if (data_to_sort.empty())
    {
        std::cerr << "Cannot download students.csv" << std::endl;
    }
    else
    {
        std::vector<Student> copy1 = data_to_sort;
        std::vector<Student> copy2 = data_to_sort;

        std::cout << "Sorting " << data_to_sort.size() << " students...\n"
                  << std::endl;

        auto start1 = std::chrono::high_resolution_clock::now();

        SorterS5_Standard::sort(copy1);

        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time1 = end1 - start1;

        std::cout << std::left << std::setw(30) << "  Time (std::sort):"
                  << time1.count() << " ms" << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();

        SorterS5_Radix::sort(copy2);

        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time2 = end2 - start2;

        std::cout << std::left << std::setw(30) << "  Time (Radix Sort):"
                  << time2.count() << " ms" << std::endl;

        std::cout << "\nSaving sorted file in 'sorted_by_group.csv'..." << std::endl;
        CSVParser::save("./data/sorted_by_group.csv", copy1);
    }

    std::cout << "========================================================\n";
    std::cout << "Benchmark completed" << std::endl;
    std::cout << "========================================================\n";

    return 0;
}
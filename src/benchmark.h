#pragma once

#include <cstddef>
#include "StudentDatabase.h"
#include <cstddef>
#include "StudentDatabase.h"

struct BenchmarkResult
{
    long long op_count_total; 
    long long op_count_A;     // findByBirthday
    long long op_count_B;     // updateGroup
    long long op_count_C;     // findGroupWithMax...

    size_t memory_used; 
};

class Benchmark
{
public:
    /**
     * @brief Testing productivity for any database
     * @param db database
     * @param seconds test time
     * @param ratioA ratio of Operation 1
     * @param ratioB ratio of Operation 2
     * @return struct BenchmarkResult
     */
    static BenchmarkResult run(StudentDatabase &db,
                               int seconds,
                               double ratioA,
                               double ratioB);
};
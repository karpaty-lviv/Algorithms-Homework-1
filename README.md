# Algorithms-Homework-1
HW 1 for algorithm course<br>
Variant for second task: V2<br>
Variant for third task: S5<br>
Proportion A:B:C = 10:100:10

### Usage
Copy repository on your machine.
Go to the root folder (where README.md is located). Then type the following command to run the program:
```bash
g++ -o main.exe src/main.cpp src/CSVParser.cpp src/Benchmark.cpp src/Task2_V2_1.cpp src/Task2_V2_2.cpp src/Task2_V2_3.cpp src/Task3_S5_1.cpp src/Task3_S5_2.cpp -std=c++17 -O2
```

The results of this test will be loaded to <code>results.csv</code> file in <code>data</code> folder. In order to generate graphs based on this data run <code>plot_graphs.py</code> program.

### Short description

For Task 2, I developed three distinct implementations for the following operations: finding all students by birthday (<code>findByBirthday</code>), updating a student's group by email (<code>updateGroup</code>), and finding the group with the highest number of students sharing the same birthday. These implementations utilized different data structures—specifically <code>std::vector</code>, <code>std::unordered_map</code>, and <code>std::map</code> — to analyze performance trade-offs.

The benchmarking results were exported to a separate <code>.csv</code> file. A Python script was then used to read this data and generate comparative graphs for various performance statistics using matplotlib.

Additionally, Task 3 (sorting all students by group) was implemented using Radix Sort. However, benchmark tests showed that it was **significantly slower than** the standard C++ **built-in** sorting method (`std::sort`).

### Performance Overview

For Task 2, I developed three distinct implementations using different data structures to analyze their efficiency. Each implementation supports the following operations: finding all students by birthday (`findByBirthday`), updating a student's group by email (`updateGroup`), and finding the group with the highest number of students sharing the same birthday (`findGroupWithMaxSharedBirthdays`). Below is a breakdown of each implementation separately.

#### First Implementation (`Task2_V2_1`)

* **`findByBirthday`**
    For this function, I simply iterate through all students and add those with the corresponding birthdays to the result vector. This straightforward method results in **O(N)** complexity, which is relatively slow and was proven inefficient by the benchmark tests.

* **`updateGroup`**
    In the `load` function, I populated `m_email_to_index`, which is an `unordered_map` (hash table). This provides instant access to any student record via their email. Consequently, updating a group by email is extremely fast and runs in **O(1)** time, as confirmed by the benchmarks.

* **`findGroupWithMaxSharedBirthdays`**
    This function creates a temporary map where keys are group names and values are maps of birthdays linked to the student count. It iterates through every student to build this map from scratch each time. Therefore, it works in **O(N)**. While functional, this approach is slow for repeated calls.

#### Second Implementation (`Task2_V2_2`)

* **`findByBirthday`**
    Here, I utilized an additional data structure (a map) that links each birthday to a list of student indices. The time required to find students by a specific date is reduced to **O(log N)** (or O(1) depending on the map type), which is significantly faster compared to the linear search in the first implementation.

* **`updateGroup`**
    Unchanged (same as V1).

* **`findGroupWithMaxSharedBirthdays`**
    Unchanged (same as V1).

#### Third Implementation (`Task2_V2_3`)

* **`findByBirthday`**
    Same as in the first implementation.

* **`updateGroup`**
    In this implementation, I maintain a "live" statistics structure, `m_group_stats`, which tracks student counts for each birthday within each group. When updating a student's group, I must also update this statistics structure to keep `findGroupWithMaxSharedBirthdays` accurate. Because this involves lookups in a nested map, the complexity increases to **O(log N)**.

* **`findGroupWithMaxSharedBirthdays`**
    Since `m_group_stats` is pre-calculated and maintained during updates, this function no longer needs to iterate through all students. It simply scans the existing statistics to find the maximum. Its complexity depends only on the number of groups and unique birthdays (O(Groups × UniqueBirthdays)), making it practically instantaneous compared to the O(N) approach, though this comes at the cost of a slightly slower `updateGroup`.

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

Additionally, Task 3 (sorting all students by group) was implemented using Radix Sort.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


bool createSampleFiles(const std::string &original_filename,
                       const std::vector<std::string> &sample_filenames,
                       const std::vector<int> &sample_sizes)
{
    std::ifstream input_file(original_filename);
    if (!input_file.is_open())
    {
        std::cerr << "Error" << original_filename << std::endl;
        return false;
    }

    std::vector<std::ofstream> output_files;
    int max_sample_size = 0;

    for (size_t i = 0; i < sample_filenames.size(); ++i)
    {
        output_files.emplace_back(sample_filenames[i]);
        if (!output_files.back().is_open())
        {
            std::cerr << "Error" << sample_filenames[i] << std::endl;
            return false;
        }
        if (sample_sizes[i] > max_sample_size)
        {
            max_sample_size = sample_sizes[i];
        }
    }

    std::string line;
    int line_count = 0;

    while (std::getline(input_file, line))
    {
        for (size_t i = 0; i < output_files.size(); ++i)
        {
            if (line_count <= sample_sizes[i])
            {
                output_files[i] << line << '\n';
            }
        }

        line_count++;

        if (line_count >= max_sample_size)
        {
            break;
        }
    }

    input_file.close();
    for (auto &file : output_files)
    {
        file.close();
    }

    std::cout << "\nAll files were loaded" << std::endl;
    return true;
}

int main()
{
    const std::string original_file = "students.csv";
    std::vector<std::string> filenames = {
        "students_100.csv",
        "students_1000.csv",
        "students_10000.csv"};
    std::vector<int> sizes = {100, 1000, 10001};
    createSampleFiles(original_file, filenames, sizes);
    return 0;
}
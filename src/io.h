#pragma once

#include <vector>
#include <array>
#include <sstream>
#include <fstream>


namespace io{
    class readANEOSfile {
    public:
        static std::vector<std::vector<std::array<double, 6>>> readfile(
                std::vector<double> &var1_vector,
                std::vector<double> &var2_vector,
                std::vector<double> &var3_vector,
                const std::string &file_path,
                const int property_index
                ) {

            std::vector<std::vector<std::array<double, 6>>> eos_data;

            const unsigned int n_expected_fields = 5;
            unsigned int n_expected_lines = 0;
            unsigned int n_expected_columns = 0;
            unsigned int n_lines = 0;
            unsigned int column_index = 0;

            std::string();
            std::ifstream input;
            input.open(file_path, std::ios::in);

            if (input.is_open()) {
                std::string line;
                while (std::getline(input, line)) {
                    // read the table size, which has to be of the format # n_rows n_cols
                    if (n_lines == 0 && n_expected_lines == 0 && n_expected_columns == 0) {
                        std::string tmp;
                        std::istringstream stream(line);

                        stream >> tmp;
                        stream >> n_expected_lines;
                        stream >> n_expected_columns;

                        ++n_lines;
                        column_index = 0;
                        eos_data.emplace_back();
                    }

                    // skip other comments
                    if (line[0] == '#')
                        continue;

                    // if we have reached the expected number of columns add a new row
                    if (column_index == n_expected_columns) {
                        ++n_lines;
                        column_index = 0;
                        eos_data.emplace_back();
                    }

                    const unsigned int line_index = n_lines - 1;
                    eos_data[line_index].push_back(std::array<double, 6>());

                    // make stream for reading
                    std::istringstream stream(line);
                    unsigned int field_index = 0;
                    double tmp;

                    while (stream >> tmp) {
                        eos_data[line_index][column_index][field_index] = tmp;

                        if (column_index == 0 && field_index == 0)
                            var1_vector.push_back(tmp);
                        if (line_index == 0 && field_index == 1)
                            var2_vector.push_back(tmp);
                        if (line_index == 0 && field_index == property_index)
                            var3_vector.push_back(tmp);

                        ++field_index;
                    }
                    ++column_index;
                }
            }
            input.close();
            return eos_data;
        }
    };
}

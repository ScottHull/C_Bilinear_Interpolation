#pragma once

#include <vector>
#include <array>
#include <sstream>
#include <fstream>

class readANEOSfile {
public:
    static std::vector<std::vector<std::array<double, 6>>> readfile(
            std::vector<double> &var1_vector, // density
    std::vector<double> &var2_vector, // energy
    std::vector<double> &var3_vector, // entropy
    std::vector<double> &var4_vector, // temperature
    std::vector<double> &var5_vector, // pressure
    std::vector<double> &var6_vector, // soundspeed
    std::vector<double> &var1_vector_full, // density
    std::vector<double> &var2_vector_full, // energy
    std::vector<double> &var3_vector_full, // entropy
    std::vector<double> &var4_vector_full, // temperature
    std::vector<double> &var5_vector_full, // pressure
    std::vector<double> &var6_vector_full, // soundspeed
    const std::string &file_path,
    const int val1_property_index, // density index
    const int val2_property_index, // energy index
    const int val3_property_index, // entropy index
    const int val4_property_index, // temperature index
    const int val5_property_index, // pressure index
    const int val6_property_index // soundspeed index
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

                    if (column_index == 0 && field_index == val1_property_index)
                        var1_vector.push_back(tmp);
                    if (line_index == 0 && field_index == val2_property_index)
                        var2_vector.push_back(tmp);
                    if (line_index == 0 && field_index == val3_property_index)
                        var3_vector.push_back(tmp);
                    if (line_index == 0 && field_index == val4_property_index)
                        var4_vector.push_back(tmp);
                    if (line_index == 0 && field_index == val5_property_index)
                        var5_vector.push_back(tmp);
                    if (line_index == 0 && field_index == val6_property_index)
                        var6_vector.push_back(tmp);

                    if (field_index == val1_property_index)
                        var1_vector_full.push_back(tmp);
                    if (field_index == val2_property_index)
                        var2_vector_full.push_back(tmp);
                    if (field_index == val3_property_index)
                        var3_vector_full.push_back(tmp);
                    if (field_index == val4_property_index)
                        var4_vector_full.push_back(tmp);
                    if (field_index == val5_property_index)
                        var5_vector_full.push_back(tmp);
                    if (field_index == val6_property_index)
                        var6_vector_full.push_back(tmp);

                    ++field_index;
                }
                ++column_index;
            }
        }
        input.close();
        return eos_data;
    }
};



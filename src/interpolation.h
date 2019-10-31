#pragma once

#include <sstream>
#include <vector>
#include <iostream>
#include "array"

//the bilinear interpolation class that can be accessed outside of this file
class BilinearInterpolation {

//do not allow these functions and variables to be externally accessible
private:
//    create a static function that returns a pair of index values of the nearest neighbor values
    static std::pair<unsigned int, unsigned int> get_neighbors(
            double val1, //val1 is the value which will get a nearest neighbor from var1_vect
            double val2, //val1 is the value which will get a nearest neighbor from var2_vect
            const std::vector<double> &var1_vect, //the vector from with var1 will be interpolated
            const std::vector<double> &var2_vect //the vector from with var2 will be interpolated
    ) {
        auto line = std::lower_bound(var1_vect.begin(), var1_vect.end(),
                                     val1); //returns an iterator that points to the first value in var1_vect that is not < val1
        const unsigned int line_index = std::distance(var1_vect.begin(),
                                                      line); //returns an int which is the number of elements between the first element of var1_vect and line
        auto column = std::lower_bound(var2_vect.begin(), var2_vect.end(),
                                       val2); //returns an iterator that points to the first value in var2_vect that is not < val2
        const unsigned int column_index = std::distance(var2_vect.begin(),
                                                        column); //returns an int which is the number of elements between the first element of var2_vect and column

        const unsigned int max_line_index = var1_vect.size() - 1; //get the largest index value possible of var1_vect
        const unsigned int max_column_index = var2_vect.size() - 1; //get the largest index value possible of var2_vect

//        make a tuple of the nearest neighbor indices: std::min returns either the value in argument 1 (the index calculated above) or the value of argment 2, which is the max index (i.e. the boundary)
        return std::make_pair(std::min(line_index, max_line_index), std::min(column_index, max_column_index));
    }

//allow these functions and variables to be externally accessible
public:
    static double interpolate(
            double val1,
            double val2,
            const std::vector<double> &var1_vect,
            const std::vector<double> &var2_vect,
            const std::vector<double> &var3_vect,
            const unsigned int property_index,
            const std::vector<std::vector<std::array<double, 6>>> &eos_data
            ) {
        std::pair<unsigned int, unsigned int> neighbors = get_neighbors(val1, val2, var1_vect, var2_vect);
//        std::cout << std::to_string(neighbors.first) << std::endl;
//        std::cout << std::to_string(neighbors.second) << std::endl;

        // If we are not at the boundaries of the data table
        if ((neighbors.first < var1_vect.size() - 1) &&
            (neighbors.second < var2_vect.size() - 1)) {
            // compute the interpolation weights of this val1 and val2
            const auto xi = (val1 - var1_vect[neighbors.first - 1]) /
                            (var1_vect[neighbors.first] - var1_vect[neighbors.first - 1]);

            const auto eta = (val2 - var2_vect[neighbors.second-1]) /
                             (var2_vect[neighbors.second] - var2_vect[neighbors.second-1]);

            // use these coordinates for a bilinear interpolation
            const double interpolated_value = (1 - xi) * (1 - eta) * eos_data[neighbors.first - 1][neighbors.second - 1][property_index] +
                                              xi * (1 - eta) * eos_data[neighbors.first][neighbors.second - 1][property_index] +
                                              (1 - xi) * eta * eos_data[neighbors.first - 1][neighbors.second][property_index] +
                                              xi * eta * eos_data[neighbors.first][neighbors.second][property_index];
            std::cout << std::to_string(interpolated_value) << std::endl;
            return interpolated_value;
        } else {
            // Return the boundary value
            const double interpolated_value = eos_data[neighbors.first][neighbors.second][property_index];
            return interpolated_value;
        }
    };
};
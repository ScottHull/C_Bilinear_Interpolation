#include <iostream>

#include "src/interpolation.h"
#include "src/io.h"


int main() {

    std::vector<double> var1_vector;
    std::vector<double> var2_vector;
    std::vector<double> var3_vector;
    const int property_index = 5;
    const std::string file_path = "../input/granite.rho_u.txt";

    std::vector<std::vector<std::array<double, 6>>> eos_data = io::readANEOSfile::readfile(var1_vector, var2_vector, var3_vector, file_path, property_index);
    double interpolated_value = BilinearInterpolation::interpolate( 1.91611522E+03, 9.84467337E+04, var1_vector, var2_vector, var3_vector, property_index, eos_data);
    std::cout << std::to_string(interpolated_value) << std::endl;
    
//    for (double & i : var1_vector)
//        std::cout << i << ' ';

//    std::vector<double> var1{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    std::vector<double> var2{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    std::vector<double> var3{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//
//    BilinearInterpolation::interpolate(50, 10, var1, var2, var3);

    return 0;
}
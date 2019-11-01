#include <iostream>

#include "src/interpolation.h"
#include "src/io.h"


int main() {

    //define parameters for the interpolation function
    std::vector<double> var1_vector; //this currently stores density from "granite.rho_u.txt"
    std::vector<double> var2_vector; //this currently stores internal energy from "granite.rho_u.txt"
    std::vector<double> var3_vector; //this currently stores entropy from "granite.rho_u.txt"
    const int val1_property_index = 0; //this is the column index value of density in the "granite.rho_u.txt" file
    const int val2_property_index = 1; //this is the column index value of internal energy in the "granite.rho_u.txt" file
    const int val3_property_index = 5; //this is the column index value of entropy in the "granite.rho_u.txt" file
    const std::string file_path = "../input/granite.rho_u.txt"; //the relative path to the "granite.rho_u.txt" file

    //read in the interpolation file
    std::vector<std::vector<std::array<double, 6>>> eos_data = io::readANEOSfile::readfile(var1_vector, var2_vector,
            var3_vector, file_path, val1_property_index, val2_property_index, val3_property_index);
    //perform the interpolation
    double interpolated_value = BilinearInterpolation::interpolate( 1.91611522E+03, 9.84467337E+04, var1_vector, var2_vector, var3_vector, val3_property_index, eos_data);

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
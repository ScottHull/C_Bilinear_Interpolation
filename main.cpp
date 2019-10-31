#include <iostream>

#include "src/interpolation.h"
#include "src/io.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<double> var1_vect;
    std::vector<double> var2_vect;
    std::vector<double> var3_vect;
    const int property_index = 5;

    std::vector<std::vector<std::array<double, 6>>> eos_data = io::readANEOSfile::readfile(var1_vect, var2_vect, var3_vect, property_index);
    BilinearInterpolation::interpolate( 1.91611522E+03, 9.84467337E+04, var1_vect, var2_vect, var3_vect, property_index, eos_data);
    
//    for (double & i : var1_vect)
//        std::cout << i << ' ';

//    std::vector<double> var1{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    std::vector<double> var2{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    std::vector<double> var3{0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//
//    BilinearInterpolation::interpolate(50, 10, var1, var2, var3);

    return 0;
}
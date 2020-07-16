#include <iostream>

#include "src/interpolation.h"
#include "src/io.h"


int main() {

    unsigned int grid_size = 120;

    std::vector<double> densities;
    std::vector<double> energies;
    std::vector<double> entropies;
    std::vector<double> temperatures;
    std::vector<double> pressures;
    std::vector<double> soundspeeds;

    std::vector<double> full_densities;
    std::vector<double> full_energies;
    std::vector<double> full_entropies;
    std::vector<double> full_temperatures;
    std::vector<double> full_pressures;
    std::vector<double> full_soundspeeds;

//    const std::string filename = "../input/duniteS2.rho_u.txt";
    const std::string filename = "../input/iron___.rho_u.txt";

    //read in the interpolation file
    std::vector < std::vector < std::array < double, 6 >> > eos_data = readANEOSfile::readfile(densities, energies,
                                                                                               entropies, temperatures,
                                                                                               pressures, soundspeeds,
                                                                                               full_densities,
                                                                                               full_energies,
                                                                                               full_entropies,
                                                                                               full_temperatures,
                                                                                               full_pressures,
                                                                                               full_soundspeeds,
                                                                                               filename, 0, 1, 5, 2, 3,
                                                                                               4);
    //perform the interpolation
    double dens = 12578.1;
    double eng = 3.70774e+06;
    double interpolated_value = RestrictedBilinearInterpolation::interpolate(dens, eng, full_densities, full_energies,
                                                                             full_entropies, 5, eos_data, grid_size);

    std::cout << std::to_string(interpolated_value) << std::endl;

    return 0;
}
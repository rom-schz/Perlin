#include <iostream>
#include <cstdint>
#include <vector>
#include <fstream>

#include "perlinNoiseGenerator.hpp"

int main(int argc, char** argv) {

    std::vector<uint64_t> sizes; sizes.push_back(3);
    Perlin::PerlinNoiseGenerator generator = Perlin::PerlinNoiseGenerator(sizes, 5, .6, .6);

    std::ofstream data;
    data.open("perlin_data.dat");

    for(uint64_t i=0; i < 10000; i++) {
        std::vector<float> coos;
        coos.push_back(float(i)/5000);

        data << float(i)/5000 << " " << generator.getNoise(coos) << std::endl;
    }

    data.close();

    return EXIT_SUCCESS;
}
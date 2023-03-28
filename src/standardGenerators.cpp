#include "standardGenerators.hpp"

namespace Perlin {


/**
 * ==============================================================================================
 * |                                      1D GENERATOR                                          |
 * ==============================================================================================
 */

generator1D::generator1D() {
    generator1D(8, 0, 0 ,0);
}

generator1D::generator1D(uint64_t size, uint64_t nb_octaves, float persistence, float lacunarity, bool abs_val, int continuity, float scale, float offset) {
    std::vector<uint64_t> sizes; sizes.push_back(size);
    this->generator = PerlinNoiseGenerator(sizes, nb_octaves, persistence, lacunarity, abs_val, continuity, scale, offset);
}

float generator1D::getNoise(float x) {
    std::vector<float> coos; coos.push_back(x);
    return generator.getNoise(coos);
}


/**
 * ==============================================================================================
 * |                                      2D GENERATOR                                          |
 * ==============================================================================================
 */


generator2D::generator2D() {
    generator2D(8, 8, 0, 0 ,0);
}

generator2D::generator2D(uint64_t size_x, uint64_t size_y, uint64_t nb_octaves, float persistence, float lacunarity, bool abs_val, int continuity, float scale, float offset) {
    std::vector<uint64_t> sizes; sizes.push_back(size_x); sizes.push_back(size_y);
    this->generator = PerlinNoiseGenerator(sizes, nb_octaves, persistence, lacunarity, abs_val, continuity, scale, offset);
}

float generator2D::getNoise(float x, float y) {
    std::vector<float> coos; coos.push_back(x); coos.push_back(y);
    return generator.getNoise(coos);
}

}
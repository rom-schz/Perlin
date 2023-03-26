#include "perlin.hpp"
#include "perlinNoiseGenerator.hpp"

namespace Perlin {

PerlinNoiseGenerator::PerlinNoiseGenerator(std::vector<uint64_t> sizes,uint64_t nb_octaves, float persistence, float lacunarity, float scale, float offset) {
    this->perlin = Perlin(sizes);
    this->nb_octaves = nb_octaves;
    this->persistence = persistence;
    this->lacunarity = lacunarity;
    this->scale = scale;
    this->offset = offset;
}

float PerlinNoiseGenerator::getNoise(std::vector<float> coos) {
    float noise=0;
    float amplitude = 1;

    for(uint64_t i=0; i < nb_octaves; i++) {

        // Add noise of one octave
        noise += amplitude * perlin.noise(coos);

        // Update amplitude and frequency parameters for next octave
        amplitude *= persistence;
        for(uint64_t i=0; i < coos.size(); i++) {
            coos[i] = coos[i] / lacunarity;
        }
    }

    return noise * scale + offset;
}

}
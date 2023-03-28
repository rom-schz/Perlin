#include "perlinNoiseGenerator.hpp"

namespace Perlin {

class generator1D : PerlinNoiseGenerator {

    public:
        generator1D();
        generator1D(uint64_t size, uint64_t nb_octaves, float persistence,
                    float lacunarity, bool abs_val=false, int continuity=2, float scale=1, float offset=0);
        float getNoise(float x);

    private:
        PerlinNoiseGenerator generator;

};

class generator2D : PerlinNoiseGenerator {

    public:
        generator2D();
        generator2D(uint64_t size_x, uint64_t size_y, uint64_t nb_octaves, float persistence,
                    float lacunarity, bool abs_val=false, int continuity=2, float scale=1, float offset=0);
        float getNoise(float x, float y);

    private:
        PerlinNoiseGenerator generator;

};

}
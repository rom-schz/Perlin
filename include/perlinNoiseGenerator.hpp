#include "perlin.hpp"

namespace Perlin {

class PerlinNoiseGenerator {

    public:
        PerlinNoiseGenerator();
        PerlinNoiseGenerator(std::vector<uint64_t> sizes,uint64_t nb_octaves, float persistence, float lacunarity, bool abs_val=false, int continuity=2, float scale=1, float offset=0);
        float getNoise(std::vector<float> coos);

    private:
        Perlin perlin;
        uint64_t nb_octaves; // Number of octaves to add
        float persistence, lacunarity; // Parameters to apply recursivelw to each octave
        float scale, offset; // End parameters to apply on the end noise
        bool abs_val;
        int continuity;
};

}
#include "pch.h"
#include "framework.h"

#pragma once

#include <vector>

namespace Perlin
{

    class Perlin {

    private:
        uint64_t dim;
        std::vector<uint64_t> sizes; // [1, n, n * m, n * m * p, ...]
        std::vector<uint64_t> prod_sizes; // [1, n, n * m, n * m * p, ...]
        std::vector<std::vector<float>> nodes;
        std::vector<uint64_t> nodes_order; // The order of the nodes to consider for pairwise interpolation

        // Return the norm of a given vector.
        float norm(std::vector<float>& v);

        //Return the unit vector with same direction than the one given.
        std::vector<float> randomVect();

        // Return a random vector with coordinates between -RAND_MAX and RAND_MAX.
        std::vector<float> unitVect(std::vector<float>&& v);

        void initOrder();
        void initGrid();
        void increase_counters(std::vector<uint64_t>& counters);
        int64_t periodicityTest(std::vector<uint64_t>& counters);

    public:
        // Initialize the grid with given sizes (e.g.: [n, m, p] describes the grid of a noise of dimension 3).
        Perlin(std::vector<uint64_t>& sizes);

        void print();

        float noise(std::vector<float> coordinates);
    };

}
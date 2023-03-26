#pragma once

#include <vector>
#include <cstdint>

namespace Perlin
{

    class Perlin {

    private:
        uint64_t dim;
        std::vector<uint64_t> sizes; // [n, m, p, ...]
        std::vector<uint64_t> prod_sizes; // [1, n, n * m, n * m * p, ...]
        std::vector<std::vector<float>> nodes; // The values stored in the gridd
        std::vector<uint64_t> nodes_order; // The order of the nodes to consider for pairwise interpolation

        // Return the norm of a given vector.
        float norm(std::vector<float>& v);

        //Return the unit vector with same direction than the one given.
        std::vector<float> randomVect();

        // Return a random vector with coordinates between -RAND_MAX and RAND_MAX.
        std::vector<float> unitVect(std::vector<float>&& v);

        // Initialize order of the nodes used in pairwise interpolation
        void initOrder();

        // Initialize the grid with random values, respecting periodicity
        void initGrid();

        std::vector<std::vector<float>> hCubePositionVect(std::vector<float>& coos);

        void increase_counters(std::vector<uint64_t>& counters);

        /**
        * @param counters the counter values for each dimension of the grid
        * @return the dimension to chose to apply periodicity to the given element. Return � if no periodicity should be applied.
        */
        int64_t periodicityTest(std::vector<uint64_t>& counters);

        /*
        * Returns the node associated to the given float number coordinates, i.e.
        * the cell in which the point of given coordinates is located.
        */
        uint64_t getNode(std::vector<float>& coordinates);

        float interpolate(float val1, float val2, float dist);

    public:
        // Initialize the grid with given sizes (e.g.: [n, m, p] describes the grid of a noise of dimension 3).
        Perlin(std::vector<uint64_t>& sizes);

        std::vector<float> const getNode(std::vector<uint64_t>& coo);

        void print();

        void setGrid(std::vector<std::vector<float>> grid);

        float noise(std::vector<float>& coordinates);
    };

}
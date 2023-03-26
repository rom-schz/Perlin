#pragma once

#include <vector>
#include <cstdint>

namespace Perlin
{

    class Perlin {


    public:

        /**
         * Initialize the grid and other private parameters of the noise.
         * 
         * @param sizes the size of the grid, with each dimension corresponding to a value in the vector
         *  (e.g.: [n, m, p] describes the grid of a noise of dimension 3)
         *  The size also includes the last layers of the grid used for periodicity and therefore gives the exact size
         *  with which the grid will be stored in memory.
        */
        Perlin(std::vector<uint64_t>& sizes);

        /**
         * Helper method, useful for debugging.
         * 
         * Prints a basic representation of the grid on the standard output.
        */
        void print();

        /**
         * @param coordinates the coordinates of the point where the noise has to be computed.
         * @return the computed noise as a floating value.
        */
        float noise(std::vector<float>& coordinates);

        /**
         * Returns the vector stored as the node of given coordinates.
         * 
         * @param coo the coordinates of the node to return.
         * @return the vector located at the given coordinates.
        */
        std::vector<float> const getNodeValue(std::vector<uint64_t>& coo);

    private:
        uint64_t dim;
        std::vector<uint64_t> sizes; // [n, m, p, ...]
        std::vector<uint64_t> prod_sizes; // [1, n, n * m, n * m * p, ...]
        std::vector<std::vector<float>> nodes; // The values stored in the gridd
        std::vector<uint64_t> nodes_order; // The order of the nodes to consider for pairwise interpolation


/**
 * ==============================================================================================
 * |                                        UTILITIES                                           |
 * ==============================================================================================
*/

        /**
         * Utility method.
         * 
         * @param v the vector which we want to compute the norm.
         * @return The norm of the given vector.
        */
        float norm(std::vector<float>& v);

        /**
         * @return a random vector with coordinates between -RAND_MAX and RAND_MAX.
        */
        std::vector<float> randomVect();

        /**
         * @param v a vector giving direction
         * @return a unit vector with same direction than v.
        */ 
        std::vector<float> unitVect(std::vector<float>&& v);


/**
 * ==============================================================================================
 * |                                     INITIALISATION                                         |
 * ==============================================================================================
*/

        /**
         * Initialize an array with the offset coordinates of each neighbor nodes of an hypercube.
         * These offset coordinates are then used to compute the relative coordinates of the point in
         * the hypercube to each of the nodes.
        */
        void initOrder();

        /**
         * Initialize the nodes grid with random value vectors, respecting periodicity.
         * The grid contains an additional layer for each dimension to allow periodicity
         * not to be handled by computations later.
        */
        void initGrid();

/**
 * ==============================================================================================
 * |                                    GRID COMPUTATION                                        |
 * ==============================================================================================
*/

        /**
         * Used in grid generation.
         * Updates the values of the counters according to periodicity.
        */
        void increase_counters(std::vector<uint64_t>& counters);

        /**
         * Used in grid generation to check whether an element
         * should be added according to periodicity conditions or not.
         * 
         * @param counters the counter values for each dimension of the grid
         * @return the dimension to chose to apply periodicity to the given element. 0 means no periodicity.
        */
        int64_t periodicityTest(std::vector<uint64_t>& counters);

/**
 * ==============================================================================================
 * |                                    NOISE COMPUTATION                                       |
 * ==============================================================================================
*/

        /**
         * Used in noise computing.
         * 
         * @param coos the coordinates of a floating point in the grid.
         * @returns a vector containing the position vectors relative to all the nodes in the hypercube
         *      containing the point of coordinates coos.
        */
        std::vector<std::vector<float>> hCubePositionVect(std::vector<float>& coos);

        /**
         * Compute the grid element in which the given element is contained.
         * Applies modulo if need be.
         * 
         * @param coordinates the coordinates of the floating point in the grid. This point isn't necesarily located in the grid and the method will apply the proper modulo if required.
         * @return the index of the grid element in which the floating point is contained.
        */
        uint64_t getNodeIndex(std::vector<float>& coordinates);

        /**
         * Standard smooth interpolation function between two values separated by a 1-length interval. 
         * Ensures a C2 continuity.
         * 
         * @param val1 left interpolated value
         * @param val2 right interpolated value
         * @param dist distance to the left value, 1-dist gives the distance to the right value.
        */
        float interpolate(float val1, float val2, float dist);
    };
}


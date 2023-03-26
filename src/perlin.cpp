#include <random>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cstdint>
#include <functional>

#include "perlin.hpp"

namespace Perlin
{

    /**
     * ==============================================================================================
     * |                                         PUBLIC                                             |
     * ==============================================================================================
     */

    Perlin::Perlin()
    {
        this->dim = 0;
        this->sizes = std::vector<uint64_t>();
    }

    // Initialize the grid with given sizes (e.g.: [n, m, p] describes the grid of a noise of dimension 3).
    Perlin::Perlin(std::vector<uint64_t> &sizes)
    {
        this->dim = sizes.size();
        this->sizes = sizes;

        initGrid();
        initOrder();
    }

    std::vector<float> const Perlin::getNodeValue(std::vector<uint64_t> &coo)
    {
        uint64_t oneDimCoo = 0;
        for (int i = 0; i < sizes.size(); i++)
        {
            oneDimCoo += coo[i] * prod_sizes[i];
        }

        return nodes[oneDimCoo];
    }

    void Perlin::print()
    {
        for (uint64_t i : prod_sizes)
            std::cout << i << " ";
        std::cout << std::endl;

        for (std::vector<float> v : nodes)
        {
            std::cout << "(";
            for (float f : v)
            {
                std::cout << f << ", ";
            }
            std::cout << ") ";
        }

        for (uint64_t i : nodes_order)
        {
            std::cout << i << " - ";
        }
        std::cout << std::endl;
    }

    float Perlin::noise(std::vector<float> &coordinates, int continuity)
    {

        /* Prepare coordinates to compute noise */
        if (coordinates.size() != this->sizes.size())
        {
            std::cerr << "transformCoordinates error : coordinates do not have the proper dimension. Dimensions should be "
                      << this->sizes.size() << ", but are " << coordinates.size() << std::endl;
            exit(EXIT_FAILURE);
        }

        // std::cout << "Getting node... " << std::endl;
        //  Get the grid element in which the point is
        uint64_t node = getNodeIndex(coordinates);
        // std::cout << "done !" << std::endl;

        // std::cout << "Computing unit coordinates... ";
        //  Compute the unit coordinates of the point in the cell
        std::vector<float> unitCoo;
        for (float f : coordinates)
            unitCoo.push_back(f - int(f));
        // std::cout << "done !" << std::endl;

        // std::cout << "Computing relative positions... ";
        /* Compute dot products between positions and gradients vectors */
        std::vector<std::vector<float>> positions = hCubePositionVect(unitCoo);
        std::vector<float> values;
        // std::cout << "done !" << std::endl;

        int debug = 0;
        if (debug)
        {
            for (std::vector<float> pos : positions)
            {
                std::cout << "Position" << std::endl;
                for (float f : pos)
                    std::cout << f << " ";
                std::cout << std::endl;
            }
        }

        // std::cout << "Computing dot products... ";
        //  For all the different position and gradient vectors
        for (uint64_t i = 0; i < (1 << dim); i++)
        {
            std::vector<float> position = positions[i];
            std::vector<float> grad = nodes[node + nodes_order[i]];

            float sum = 0;
            // Add the contribution of all components to the scalar product
            for (uint64_t j = 0; j < dim; j++)
            {
                sum += position[j] * grad[j];
            }

            values.push_back(sum);
        }
        // std::cout << "done !" << std::endl;

        // std::cout << "Computing interpolation... ";
        //  Interpolate all the elements of this array pairwise
        for (uint64_t i = 0; i < dim; i++)
        {
            float dist = unitCoo[i];

            std::vector<float> new_values;
            for (uint64_t j = 0; j < (1 << (dim - 1 - i)); j++)
            {
                float new_value = 0;
                switch(continuity) {
                    case 0:
                        new_value = interpolate_rough(values[2 * j], values[2 * j + 1], dist);
                        break;
                    case 1:
                        new_value = interpolate_smooth(values[2 * j], values[2 * j + 1], dist);
                        break;
                    default:
                        new_value = interpolate_ultra_smooth(values[2 * j], values[2 * j + 1], dist);
                        break;
                }
                new_values.push_back(new_value);
            }
            values = new_values;
        }
        // std::cout << "done !" << std::endl;

        // Return interpolated value
        return values[0];
    }

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
    float Perlin::norm(std::vector<float> &v)
    {
        float dot = 0;

        for (int i = 0; i < v.size(); i++)
        {
            dot += v[i] * v[i];
        }

        return sqrt(dot);
    }

    /**
     * @return a random vector with coordinates between -RAND_MAX and RAND_MAX.
     */
    std::vector<float> Perlin::randomVect()
    {
        std::vector<float> v = std::vector<float>();
        for (uint64_t i = 0; i < dim; i++)
        {
            v.push_back(rand() - RAND_MAX / 2);
        }

        return v;
    }

    /**
     * @param v a vector giving direction
     * @return a unit vector with same direction than v.
     */
    std::vector<float> Perlin::unitVect(std::vector<float> &&v)
    {

        std::vector<float> v2 = std::vector<float>();
        float d = norm(v);
        for (int i = 0; i < v.size(); i++)
        {
            v2.push_back(v[i] / d);
        }

        return v2;
    }

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
    void Perlin::initOrder()
    {

        this->nodes_order = std::vector<uint64_t>();

        for (uint64_t i = 0; i < (uint64_t)1 << dim; i++)
            nodes_order.push_back(0);

        for (uint64_t i = 0; i < dim; i++)
        {
            int status = 1;
            uint64_t step = (uint64_t)1 << i;

            for (uint64_t j = 0; j < (uint64_t)1 << dim; j++)
            {
                if (j % step == 0)
                    status = 1 - status;
                if (status)
                    nodes_order[j] += prod_sizes[i];
            }
        }
    }

    /**
     * Initialize the nodes grid with random value vectors, respecting periodicity.
     * The grid contains an additional layer for each dimension to allow periodicity
     * not to be handled by computations later.
     */
    void Perlin::initGrid()
    {
        int debug = 0;

        // Initializing counters, one for each dimension.
        std::vector<uint64_t> counters = std::vector<uint64_t>();
        for (uint64_t i = 0; i < dim; i++)
        {
            counters.push_back(0);
        }

        // Initializing the vector of dimensions sizes (ex: dimension 3 [1, n, n*m, n*m*p]).
        uint64_t prod = 1;
        for (uint64_t i = 0; i < dim; i++)
        {
            prod_sizes.push_back(prod);
            prod *= sizes[i];
        }
        prod_sizes.push_back(prod);

        // Adding nodes to the grid
        for (uint64_t i = 0; i < prod_sizes[dim]; i++)
        {

            if (debug)
                std::cout << "Loop : " << i << std::endl;

            // Checks if the next elements should be added according to periodicity.
            int64_t j = periodicityTest(counters);

            // If no periodicity is required, simply add a random element
            if (j < 0)
            {
                if (debug)
                    std::cout << "\tAdding random element" << std::endl;
                nodes.push_back(Perlin::unitVect(Perlin::randomVect()));
                increase_counters(counters);
            }

            // Else, add the proper amount of elements according to the dimension related to the period.
            else
            {
                if (debug)
                    std::cout << "\tAdding periodic element : " << j << std::endl;
                for (uint64_t k = 0; k < prod_sizes[j]; k++)
                {
                    if (debug)
                        std::cout << "\t\tfor : " << k << std::endl;
                    nodes.push_back(nodes[i + k - prod_sizes[j + 1] + prod_sizes[j]]);
                    increase_counters(counters);
                }

                i += prod_sizes[j] - 1;
            }
        }
    }

    /**
     * ==============================================================================================
     * |                                    GRID COMPUTATION                                        |
     * ==============================================================================================
     */

    /**
     * Used in grid generation.
     * Updates the values of the counters according to periodicity.
     */
    void Perlin::increase_counters(std::vector<uint64_t> &counters)
    {

        uint64_t j = 0;
        while (j < dim)
        {
            counters[j] += 1;
            if (counters[j] == sizes[j])
            {
                counters[j] = 0;
                j++;
            } // Continue to increment higher dimensions counters.
            else
            {
                break;
            }
        }
    }

    /**
     * Used in grid generation to check whether an element
     * should be added according to periodicity conditions or not.
     *
     * @param counters the counter values for each dimension of the grid
     * @return the dimension to chose to apply periodicity to the given element. 0 means no periodicity.
     */
    int64_t Perlin::periodicityTest(std::vector<uint64_t> &counters)
    {
        uint64_t j = 0;

        while (j < dim)
        {
            if (counters[j] == sizes[j] - 1)
                return j;
            else
                j++;
        }

        return -1;
    }

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
    std::vector<std::vector<float>> Perlin::hCubePositionVect(std::vector<float> &coos)
    {
        std::vector<std::vector<float>> relativeCoordinates;

        for (uint64_t i = 0; i < (1 << dim); i++)
        {

            // Compute the coordinates of the point to which the relative position should be computed.
            // The result has to be in binary.
            uint64_t num = i;
            // std::cout << "Number to convert: " << num << " | ";
            uint64_t c = 0;
            uint64_t r = 0;
            std::vector<uint64_t> binArray;
            for (int i = 0; i < dim; i++)
                binArray.push_back(0);
            while (c < dim)
            {
                r = num % 2;
                binArray[c++] = r;
                num /= 2;
            }

            // std::cout << "Converted value: ";
            // for (int k = 0; k < dim; k++) std::cout << binArray[k];
            // std::cout << std::endl;

            // std::cout << "Computing relative position... ";
            //  Compute position vector relative to each point
            std::vector<float> relativeCoordinatesPoint;
            for (uint64_t j = 0; j < dim; j++)
            {
                relativeCoordinatesPoint.push_back(coos[j] - binArray[j]);
            }
            // std::cout << std::endl << "done !" << std::endl;

            // std::cout << "Ici" << std::endl;

            relativeCoordinates.push_back(relativeCoordinatesPoint);
            // std::cout << "Really done?" << std::endl;
        }

        // std::cout << "All done!" << std::endl;

        // Return all the position vector relative to each point of the hypercube of dimension dim
        return relativeCoordinates;
    }

    /**
     * Standard smooth interpolation function between two values separated by a 1-length interval.
     * Ensures a C2 continuity.
     *
     * @param val1 left interpolated value
     * @param val2 right interpolated value
     * @param dist distance to the left value, 1-dist gives the distance to the right value.
     */
    float Perlin::interpolate_ultra_smooth(float val0, float val1, float w)
    {
        return (val1 - val0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + val0;
    }

    /**
     * Standard smooth interpolation function between two values separated by a 1-length interval. 
     * Ensures a C1 continuity.
     * 
     * @param val0 left interpolated value
     * @param val1 right interpolated value
     * @param w distance to the left value, 1-w gives the distance to the right value.
    */
    float Perlin::interpolate_smooth(float val0, float val1, float w) {
        return val0 + (3 - 2 * w) * w * (val1 - val0);
    }

    /**
     * Linear interpolation function between two values separated by a 1-length interval.
     *
     * @param val1 left interpolated value
     * @param val2 right interpolated value
     * @param dist distance to the left value, 1-dist gives the distance to the right value.
     */
    float Perlin::interpolate_rough(float val0, float val1, float w) {
        return val0 + w * (val1 - val0);
    }

    /**
     * Compute the grid element in which the given element is contained.
     * Applies modulo if need be.
     *
     * @param coordinates the coordinates of the floating point in the grid. This point isn't necesarily located in the grid and the method will apply the proper modulo if required.
     * @return the index of the grid element in which the floating point is contained.
     */
    uint64_t Perlin::getNodeIndex(std::vector<float> &coordinates)
    {
        uint64_t node = 0;

        for (int i = 0; i < coordinates.size(); i++)
            node += (int(coordinates[i]) % (sizes[i] - 1)) * prod_sizes[i];

        return node;
    }
}

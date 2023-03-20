#include "framework.h"
#include "pch.h"

#include <random>
#include <cmath>
#include <numeric>
#include <iostream>

#include "perlin.h"

namespace Perlin
{
    // Return the norm of a given vector. 
    float Perlin::norm(std::vector<float>& v) {
        float dot = 0;

        for (int i = 0; i < v.size(); i++) { dot += v[i] * v[i]; }

        return sqrt(dot);
    }

    //Return the unit vector with same direction than the one given.
    std::vector<float> Perlin::unitVect(std::vector<float>&& v) {

        std::vector<float> v2 = std::vector<float>();
        float d = norm(v);
        for (int i = 0; i < v.size(); i++) { v2.push_back(v[i] / d); }

        return v2;
    }

    // Return a random vector with coordinates between -RAND_MAX and RAND_MAX.
    std::vector<float> Perlin::randomVect() {
        std::vector<float> v = std::vector<float>();
        for (uint64_t i = 0; i < dim; i++) { v.push_back(rand() - RAND_MAX / 2); }

        return v;
    }

    // Initialize the grid with given sizes (e.g.: [n, m, p] describes the grid of a noise of dimension 3).
    Perlin::Perlin(std::vector<uint64_t>& sizes) {
        this->dim = sizes.size();
        this->sizes = sizes;

        initGrid();
        initOrder();
    }

    void Perlin::initOrder() {

        this->nodes_order = std::vector<uint64_t>();

        for (uint64_t i = 0; i < (uint64_t)1 << dim; i++) nodes_order.push_back(0);

        for (uint64_t i = 0; i < dim; i++) {
            int status = 1;
            uint64_t step = (uint64_t) 1 << i;

            for (uint64_t j = 0; j < (uint64_t)1 << dim; j++) {
                if (j % step == 0) status = 1 - status;
                if (status) nodes_order[j] += prod_sizes[i];
            }
        }
    }

    void Perlin::initGrid() {
        int debug = 0;

        // Initializing counters, one for each dimension.
        std::vector<uint64_t> counters = std::vector<uint64_t>();
        for (uint64_t i = 0; i < dim; i++) { counters.push_back(0); }

        // Initializing the vector of dimensions sizes (ex: dimension 3 [1, n, n*m, n*m*p]).
        uint64_t prod = 1;
        for (uint64_t i = 0; i < dim; i++) { prod_sizes.push_back(prod); prod *= sizes[i]; }
        prod_sizes.push_back(prod);

        if (debug) std::cout << "Pas encore dans la boucle!" << std::endl;

        // Adding all vectors
        for (uint64_t i = 0; i < prod_sizes[dim]; i++) {

            if (debug) std::cout << "Loop : " << i << std::endl;

            // Checks if the next elements should be added according to periodicity.
            int64_t j = periodicityTest(counters);

            // If no periodicity is required, simply add a random element
            if (j < 0) {
                if (debug) std::cout << "\tAdding random element" << std::endl;
                nodes.push_back(Perlin::unitVect(Perlin::randomVect()));
                increase_counters(counters);
            }

            // Else, add the proper amount of elements according to the dimension related to the period.
            else {
                if (debug) std::cout << "\tAdding periodic element : " << j << std::endl;
                for (uint64_t k = 0; k < prod_sizes[j]; k++) {
                    if (debug) std::cout << "\t\tfor : " << k << std::endl;
                    nodes.push_back(nodes[i + k - prod_sizes[j + 1] + prod_sizes[j]]);
                    increase_counters(counters);
                }

                i += prod_sizes[j] - 1;
            }
        }
    }

    void Perlin::increase_counters(std::vector<uint64_t>& counters) {
        
        uint64_t j = 0;
        while (j < dim) {
            counters[j] += 1;
            if (counters[j] == sizes[j]) { counters[j] = 0; j++; } // Continue to increment higher dimensions counters.
            else { break; }
        }
    }

    int64_t Perlin::periodicityTest(std::vector<uint64_t>& counters) {
        uint64_t j = 0;

        while (j < dim) {
            if (counters[j] == sizes[j] - 1) return j;
            else j++;
        }

        return -1;
    }

    void Perlin::print() {
        for (uint64_t i : prod_sizes) std::cout << i << " ";
        std::cout << std::endl;

        for (std::vector<float> v : nodes) {
            std::cout << "(";
            for (float f : v) {
                std::cout << f << ", ";
            }
            std::cout << ") ";
        }

        for (uint64_t i : nodes_order) { std::cout << i << " - "; }
        std::cout << std::endl;

    }

}

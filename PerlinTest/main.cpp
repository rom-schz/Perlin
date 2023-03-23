#include <iostream>
#include <vector>

#include "perlin.h"

int main(int argc, char* argv[]) {

	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);
	sizes.push_back(3);
	sizes.push_back(3);

	std::cout << "Computing grid... ";
	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::cout << "Success!\n";

	p.print();

	return EXIT_SUCCESS;
}
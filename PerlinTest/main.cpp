#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "perlin.h"

int main(int argc, char* argv[]) {

	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(8);
	sizes.push_back(8);

	std::cout << "Computing grid... ";
	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::cout << "Success!\n";

	if (0) {

		std::vector<std::vector<float>> grid;
		std::vector<float> vect;
		vect.push_back(1); vect.push_back(0);

		grid.push_back(vect); grid.push_back(vect); grid.push_back(vect); grid.push_back(vect);

		p.setGrid(grid);

		p.print();

		std::vector<float> coos;
		coos.push_back(.5);
		coos.push_back(.5);
		std::cout << "Noise: " << p.noise(coos) << std::endl;

	}
	else {
		std::ofstream data;
		data.open("perlin_data.dat");

		for (uint64_t i = 0; i <= 400; i++) {
			if (1) {
				for (uint64_t j = 0; j <= 400; j++) {
					std::vector<float> coos;
					coos.push_back(float(j) / 100);
					coos.push_back(float(i) / 100);

					data << float(j) / 100 << " " << float(i) / 100 << " " << p.noise(coos) << std::endl;
				}
			}
			else {
				std::vector<float> coos;
				coos.push_back(float(i) / 100);
				data << float(i) / 100 << " " << p.noise(coos) << std::endl;
			}
		}

		data.close();
	}

	//p.print();

	return EXIT_SUCCESS;
}
#include <vector>
#include <cstdint>

#include "gtest/gtest.h"
#include "perlin.hpp"


TEST(GridGenerationTest, GridGeneration) {

	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);
	sizes.push_back(3);
	sizes.push_back(3);

	Perlin::Perlin p = Perlin::Perlin(sizes);
}

TEST(PeriodicityTest, Periodicity1D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<uint64_t> coo1, coo2;

	coo1.push_back(0);
	coo2.push_back(2);

	ASSERT_EQ(p.getNode(coo1), p.getNode(coo2));
}

TEST(PeriodicityTest, Periodicity2D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);
	sizes.push_back(3);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<uint64_t> coo1, coo2, coo3, coo4;

	coo1.push_back(0); coo1.push_back(0);
	coo2.push_back(2); coo2.push_back(0);
	coo3.push_back(0); coo3.push_back(2);
	coo4.push_back(2); coo4.push_back(2);

	ASSERT_EQ(p.getNode(coo1), p.getNode(coo2));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo3));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo4));
}

TEST(PeriodicityTest, Periodicity3D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);
	sizes.push_back(3);
	sizes.push_back(3);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<uint64_t> coo1, coo2, coo3, coo4, coo5, coo6, coo7, coo8;

	coo1.push_back(0); coo1.push_back(0); coo1.push_back(0);
	coo2.push_back(2); coo2.push_back(0); coo2.push_back(0);
	coo3.push_back(0); coo3.push_back(2); coo3.push_back(0);
	coo4.push_back(2); coo4.push_back(2); coo4.push_back(0);

	coo5.push_back(0); coo5.push_back(0); coo5.push_back(2);
	coo6.push_back(2); coo6.push_back(0); coo6.push_back(2);
	coo7.push_back(0); coo7.push_back(2); coo7.push_back(2);
	coo8.push_back(2); coo8.push_back(2); coo8.push_back(2);


	ASSERT_EQ(p.getNode(coo1), p.getNode(coo2));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo3));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo4));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo5));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo6));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo7));
	ASSERT_EQ(p.getNode(coo1), p.getNode(coo8));
}

TEST(NoiseGenerationTest, NoiseGeneration1D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(2);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<float> coos;

	coos.push_back(.5);
	p.noise(coos);

	coos.pop_back();
	coos.push_back(1.01);
	float noise0 = p.noise(coos);

	coos.pop_back();
	coos.push_back(.99);
	float noise1 = p.noise(coos);

	ASSERT_NEAR(noise0, noise1, .1);

	coos.pop_back();
	coos.push_back(36);
	p.noise(coos);

}

TEST(NoiseGenerationTest, NoiseGeneration2D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(2);
	sizes.push_back(3);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<float> coos;

	coos.push_back(.5); coos.push_back(.5);
	p.noise(coos);

	coos.pop_back(); coos.pop_back();
	coos.push_back(1.001); coos.push_back(.999);
	float noise0 = p.noise(coos);

	coos.pop_back(); coos.pop_back();
	coos.push_back(.999); coos.push_back(1.001);
	float noise1 = p.noise(coos);

	ASSERT_NEAR(noise0, noise1, .1);

	coos.pop_back(); coos.pop_back();
	coos.push_back(38); coos.push_back(41);
	p.noise(coos);
}

TEST(NoiseGenerationTest, NoiseGeneration3D) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(2);
	sizes.push_back(3);
	sizes.push_back(4);

	Perlin::Perlin p = Perlin::Perlin(sizes);

	std::vector<float> coos;

	coos.push_back(.5); coos.push_back(.5); coos.push_back(.5);
	p.noise(coos);

	coos.pop_back(); coos.pop_back(); coos.pop_back();
	coos.push_back(1.001); coos.push_back(.999); coos.push_back(.999);
	float noise0 = p.noise(coos);

	coos.pop_back(); coos.pop_back();  coos.pop_back();
	coos.push_back(.999); coos.push_back(1.001); coos.push_back(1.001);
	float noise1 = p.noise(coos);

	ASSERT_NEAR(noise0, noise1, .1);

	coos.pop_back(); coos.pop_back();  coos.pop_back();
	coos.push_back(38); coos.push_back(41); coos.push_back(53);
	p.noise(coos);
}

TEST(NoiseGenerationTest, SurfaceGeneration) {
	std::vector<uint64_t> sizes = std::vector<uint64_t>();
	sizes.push_back(3);
	sizes.push_back(3);

	std::cout << "Computing grid... ";
	Perlin::Perlin p = Perlin::Perlin(sizes);

	for (uint64_t i = 0; i <= 400; i++) {
		for (uint64_t j = 0; j <= 400; j++) {
			std::vector<float> coos;
			coos.push_back(float(j) / 100);
			coos.push_back(float(i) / 100);

			p.noise(coos);
		}
	}
}

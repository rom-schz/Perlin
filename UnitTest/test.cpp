#include "pch.h"
#include "perlin.h"


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

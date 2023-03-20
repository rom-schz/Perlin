#include "pch.h"
#include "CppUnitTest.h"

#include "perlin.h"

#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1D
{
	TEST_CLASS(UnitTest1D)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::vector<uint64_t> sizes = std::vector<uint64_t>();
			sizes.push_back(3);
			sizes.push_back(3);
			sizes.push_back(3);

			std::cout << "Computing grid... ";
			Perlin::Perlin p = Perlin::Perlin(sizes);

			std::cout << "Success!\n";

	};
}

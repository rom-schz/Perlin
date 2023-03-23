#include <vector>

#include "pch.h"

#include "perlin.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::vector<uint64_t> sizes = std::vector<uint64_t>();
			sizes.push_back(3);
			sizes.push_back(3);
			sizes.push_back(3);

			Perlin::Perlin p = Perlin::Perlin(sizes);
		};
	};
};
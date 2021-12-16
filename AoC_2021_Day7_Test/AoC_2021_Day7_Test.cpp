#include "CppUnitTest.h"

#include "../AoC_2021_Day7/AoC_2021_Day7.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day7::test
{
	const puzzle_input test_input =
	{
		.crabs = {16,1,2,0,4,2,7,1,2,14}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int64_t expected_test_ouput_1 = 37;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 168;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

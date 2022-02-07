#include "CppUnitTest.h"

#include "../AoC_2021_Day9/AoC_2021_Day9.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day9::test
{
	const puzzle_input test_input =
	{
		.heights = {
			{ 2, 1, 9, 9, 9, 4, 3, 2, 1, 0 },
			{ 3, 9, 8, 7, 8, 9, 4, 9, 2, 1 },
			{ 9, 8, 5, 6, 7, 8, 9, 8, 9, 2 },
			{ 8, 7, 6, 7, 8, 9, 6, 7, 8, 9 },
			{ 9, 8, 9, 9, 9, 6, 5, 6, 7, 8 },
		}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int64_t expected_test_ouput_1 = 15;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 1134;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

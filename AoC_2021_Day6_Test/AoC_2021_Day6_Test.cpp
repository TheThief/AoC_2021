#include "CppUnitTest.h"

#include "../AoC_2021_Day6/AoC_2021_Day6.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day6::test
{
	const puzzle_input test_input =
	{
		.fish = {3,4,3,1,2}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int64_t expected_test_ouput_1 = 26;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input, 18));

			const int64_t expected_test_ouput_2 = 5934;
			Assert::AreEqual(expected_test_ouput_2, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 26984457539;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

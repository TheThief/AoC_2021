#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../AoC_2021_Day2/AoC_2021_Day2.h"

namespace aoc2021::day2::test
{
	const move test_input[] =
	{
		forward{ 5 },
		down   { 5 },
		forward{ 8 },
		up     { 3 },
		down   { 8 },
		forward{ 2 },
	};

	TEST_CLASS(AoC2021Day1Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int expected_test_ouput_1 = 150;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 900;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

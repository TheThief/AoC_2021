#include "CppUnitTest.h"

#include "../AoC_2021_Day3/AoC_2021_Day3.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day3::test
{
	const std::bitset<5> test_input[] =
	{
		0b00100,
		0b11110,
		0b10110,
		0b10111,
		0b10101,
		0b01111,
		0b00111,
		0b11100,
		0b10000,
		0b11001,
		0b00010,
		0b01010,
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int expected_test_ouput_1 = 198;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 230;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

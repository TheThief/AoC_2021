#include "CppUnitTest.h"

#include "../AoC_2021_Day4/AoC_2021_Day4.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day4::test
{
	const puzzle_input test_input =
	{
		.numbers = {7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1},
		.boards = {
			board {
				.numbers = {{
					{22, 13, 17, 11,  0},
					{ 8,  2, 23,  4, 24},
					{21,  9, 14, 16,  7},
					{ 6, 10,  3, 18,  5},
					{ 1, 12, 20, 15, 19}
				}}
			},

			board {
				.numbers = {{
					{ 3, 15,  0,  2, 22},
					{ 9, 18, 13, 17,  5},
					{19,  8,  7, 25, 23},
					{20, 11, 10, 24,  4},
					{14, 21, 16, 12,  6}
				}}
			},

			board {
				.numbers = {{
					{14, 21, 17, 24,  4},
					{10, 16, 15,  9, 19},
					{18,  8, 23, 26, 20},
					{22, 11, 13,  6,  5},
					{ 2,  0, 12,  3,  7}
				}}
			},
		}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int expected_test_ouput_1 = 188 * 24;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 148 * 13;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

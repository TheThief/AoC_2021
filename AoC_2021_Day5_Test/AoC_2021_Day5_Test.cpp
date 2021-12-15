#include "CppUnitTest.h"

#include "../AoC_2021_Day5/AoC_2021_Day5.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day5::test
{
	const puzzle_input test_input =
	{
		.lines = {
			line{.points={{{0,9}, {5,9}}}},
			line{.points={{{8,0}, {0,8}}}},
			line{.points={{{9,4}, {3,4}}}},
			line{.points={{{2,2}, {2,1}}}},
			line{.points={{{7,0}, {7,4}}}},
			line{.points={{{6,4}, {2,0}}}},
			line{.points={{{0,9}, {2,9}}}},
			line{.points={{{3,4}, {1,4}}}},
			line{.points={{{0,0}, {8,8}}}},
			line{.points={{{5,5}, {8,2}}}},
		}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int expected_test_ouput_1 = 5;
			Assert::AreEqual(expected_test_ouput_1, part1<10>(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 12;
			Assert::AreEqual(expected_test_ouput_2, part2<10>(test_input));
		}
	};
}

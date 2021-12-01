#include "CppUnitTest.h"

#include "../AoC_2021_Day1/AoC_2021_Day1.h"
const int test_input[] =
{
	199,
	200,
	208,
	210,
	200,
	207,
	240,
	269,
	260,
	263,
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AoC2021Day1Test
{
	TEST_CLASS(AoC2021Day1Test)
	{
	public:
		
		TEST_METHOD(Part1)
		{
			const int expected_test_ouput_1 = 7;
			Assert::AreEqual(expected_test_ouput_1, part1(ranges::views::all(test_input)));
		}

		TEST_METHOD(Part2)
		{
			const int expected_test_ouput_2 = 5;
			Assert::AreEqual(expected_test_ouput_2, part2(ranges::views::all(test_input)));
		}
	};
}

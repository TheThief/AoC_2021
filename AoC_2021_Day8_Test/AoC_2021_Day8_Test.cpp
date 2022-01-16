#include "CppUnitTest.h"

#include "../AoC_2021_Day8/AoC_2021_Day8.h"
#include <bitset>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoc2021::day8::test
{
	const puzzle_input test_input =
	{
		.displays = {
			{
				.digits = {"be"_set, "cfbegad"_set, "cbdgef"_set, "fgaecd"_set, "cgeb"_set, "fdcge"_set, "agebfd"_set, "fecdb"_set, "fabcd"_set, "edb"_set},
				.values = {"fdgacbe"_set, "cefdb"_set, "cefbgd"_set, "gcbe"_set}
			},
			{
				.digits = {"edbfga"_set, "begcd"_set, "cbg"_set, "gc"_set, "gcadebf"_set, "fbgde"_set, "acbgfd"_set, "abcde"_set, "gfcbed"_set, "gfec"_set},
				.values = {"fcgedb"_set, "cgb"_set, "dgebacf"_set, "gc"_set}
			},
			{
				.digits = {"fgaebd"_set, "cg"_set, "bdaec"_set, "gdafb"_set, "agbcfd"_set, "gdcbef"_set, "bgcad"_set, "gfac"_set, "gcb"_set, "cdgabef"_set},
				.values = {"cg"_set, "cg"_set, "fdcagb"_set, "cbg"_set}
			},
			{
				.digits = {"fbegcd"_set, "cbd"_set, "adcefb"_set, "dageb"_set, "afcb"_set, "bc"_set, "aefdc"_set, "ecdab"_set, "fgdeca"_set, "fcdbega"_set},
				.values = {"efabcd"_set, "cedba"_set, "gadfec"_set, "cb"_set}
			},
			{
				.digits = {"aecbfdg"_set, "fbg"_set, "gf"_set, "bafeg"_set, "dbefa"_set, "fcge"_set, "gcbea"_set, "fcaegb"_set, "dgceab"_set, "fcbdga"_set},
				.values = {"gecf"_set, "egdcabf"_set, "bgf"_set, "bfgea"_set}
			},
			{
				.digits = {"fgeab"_set, "ca"_set, "afcebg"_set, "bdacfeg"_set, "cfaedg"_set, "gcfdb"_set, "baec"_set, "bfadeg"_set, "bafgc"_set, "acf"_set},
				.values = {"gebdcfa"_set, "ecba"_set, "ca"_set, "fadegcb"_set}
			},
			{
				.digits = {"dbcfg"_set, "fgd"_set, "bdegcaf"_set, "fgec"_set, "aegbdf"_set, "ecdfab"_set, "fbedc"_set, "dacgb"_set, "gdcebf"_set, "gf"_set},
				.values = {"cefg"_set, "dcbef"_set, "fcge"_set, "gbcadfe"_set}
			},
			{
				.digits = {"bdfegc"_set, "cbegaf"_set, "gecbf"_set, "dfcage"_set, "bdacg"_set, "ed"_set, "bedf"_set, "ced"_set, "adcbefg"_set, "gebcd"_set},
				.values = {"ed"_set, "bcgafe"_set, "cdgba"_set, "cbgef"_set}
			},
			{
				.digits = {"egadfb"_set, "cdbfeg"_set, "cegd"_set, "fecab"_set, "cgb"_set, "gbdefca"_set, "cg"_set, "fgcdab"_set, "egfdb"_set, "bfceg"_set},
				.values = {"gbdfcae"_set, "bgc"_set, "cg"_set, "cgb"_set}
			},
			{
				.digits = {"gcafb"_set, "gcf"_set, "dcaebfg"_set, "ecagb"_set, "gf"_set, "abcdeg"_set, "gaef"_set, "cafbge"_set, "fdbac"_set, "fegbdc"_set},
				.values = {"fgae"_set, "cfgab"_set, "fg"_set, "bagce"_set}
			}
		}
	};

	TEST_CLASS(Test)
	{
	public:

		TEST_METHOD(Part1)
		{
			const int64_t expected_test_ouput_1 = 26;
			Assert::AreEqual(expected_test_ouput_1, part1(test_input));
		}

		TEST_METHOD(Part2)
		{
			const int64_t expected_test_ouput_2 = 61229;
			Assert::AreEqual(expected_test_ouput_2, part2(test_input));
		}
	};
}

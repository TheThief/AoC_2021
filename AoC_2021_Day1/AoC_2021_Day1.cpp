#include <fstream>
#include <iostream>
#include <utility>

#include "AoC_2021_Day1.h"

int main()
{
	std::ifstream i("input.txt");
	const auto input = ranges::istream_view<int>(i) | ranges::to<std::vector>;

	std::cout << part1(input) << std::endl;

	std::cout << part2(input) << std::endl;
}

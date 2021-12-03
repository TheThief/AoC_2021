#include <fstream>
#include <iostream>
#include <utility>
#include <chrono>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "AoC_2021_Day3.h"
#include <bitset>

using namespace aoc2021::day3;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	std::ifstream i("input.txt");
	const auto input = ranges::istream_view<std::bitset<12>>(i) | ranges::to<std::vector>;

	{
		const auto start = std::chrono::high_resolution_clock::now();
		const auto part1_result = part1(input);
		const auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "Part 1: " << part1_result << " in " << std::chrono::duration<float, std::micro>(stop - start).count() << "μs" << std::endl;
	}

	{
		const auto start = std::chrono::high_resolution_clock::now();
		const auto part2_result = part2(input);
		const auto stop = std::chrono::high_resolution_clock::now();
		std::cout << "Part 2: " << part2_result << " in " << std::chrono::duration<float, std::micro>(stop - start).count() << "μs" << std::endl;
	}
}

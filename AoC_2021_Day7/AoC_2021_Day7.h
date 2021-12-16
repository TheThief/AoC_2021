#pragma once

#include <range/v3/all.hpp>
#include "../Common/comma_separated.h"

namespace aoc2021::day7
{
	struct puzzle_input
	{
		std::vector<int> crabs;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.crabs = ranges::istream_view<comma_separated<int>>(is) | ranges::to<std::vector<int>>;

		return is;
	}

	auto dist_from(int from)
	{
		return [from](int pos)
		{
			return std::abs(pos - from);
		};
	}

	int64_t part1(const puzzle_input& input)
	{
		const auto crabs = input.crabs | ranges::to<std::vector> | ranges::actions::sort;
		const auto count = (int)ranges::size(crabs);
		const auto midpoint = crabs[count /2];

		return ranges::accumulate(
			crabs,
			0,
			std::plus(),
			dist_from(midpoint));
	}

	int floor_div(int a, int b)
	{
		return a / b;
	}

	int ceil_div(int a, int b)
	{
		return (a + b - 1) / b;
	}

	auto dist_from_2(int from)
	{
		return [from](int pos)
		{
			auto dist = std::abs(pos - from);
			return (dist + 1) * dist / 2;
		};
	}

	int64_t part2(const puzzle_input& input)
	{
		const auto& crabs = input.crabs;
		const auto total = ranges::accumulate(crabs, 0);
		const auto count = (int)ranges::size(crabs);
		const auto average_low  = floor_div(total, count);
		const auto average_high =  ceil_div(total, count);

		return std::min(
			ranges::accumulate(
				crabs,
				0,
				std::plus(),
				dist_from_2(average_low)),
			ranges::accumulate(
				crabs,
				0,
				std::plus(),
				dist_from_2(average_high))
			);
	}
}

#pragma once

#include <optional>
#include <range/v3/all.hpp>
#include "../Common/comma_separated.h"

namespace aoc2021::day6
{
	struct puzzle_input
	{
		std::vector<int8_t> fish;
	};

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.fish = ranges::istream_view<comma_separated<int>>(is) | ranges::to<std::vector<int8_t>>;

		return is;
	}

	int64_t part1(const puzzle_input& input, int days=80)
	{
		auto fish_counts =
			ranges::views::iota(0, 9) |
			ranges::views::transform(
				[&](int i)
				{
					return ranges::count(input.fish, i);
				}) |
			ranges::to<std::vector<int64_t>>;

		for (int i = 0; i < days; ++i)
		{
			ranges::rotate(fish_counts, fish_counts.begin()+1);
			fish_counts[6] += fish_counts[8];
		}

		return ranges::accumulate(fish_counts, INT64_C(0));
	}

	int64_t part2(const puzzle_input& input)
	{
		return part1(input, 256);
	}
}

#pragma once

#include <range/v3/all.hpp>

int part1(ranges::forward_range auto& input)
{
	const auto sliding2 = input | ranges::views::sliding(2);
	const auto increasing = sliding2 |
		ranges::views::transform(
			[](auto pair)
			{
				if (pair[1] > pair[0])
					return 1;
				return 0;
			});

	return ranges::accumulate(increasing, 0);
}

int part2(ranges::forward_range auto& input)
{
	const auto sliding4 = input | ranges::views::sliding(4);
	const auto increasing = sliding4 |
		ranges::views::transform(
			[](auto pair)
			{
				if (pair[3] > pair[0])
					return 1;
				return 0;
			});

	return ranges::accumulate(increasing, 0);
}

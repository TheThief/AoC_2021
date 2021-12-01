#pragma once

#include <range/v3/all.hpp>

int part1(ranges::forward_range auto input)
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

int part2(ranges::forward_range auto input)
{
	const auto sliding3 = input | ranges::views::sliding(3);
	const auto sums = sliding3 |
		ranges::views::transform(
			[](auto triple)
			{
				return ranges::accumulate(triple, 0);
			});

	return part1(sums);
}

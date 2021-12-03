#pragma once

#include <range/v3/all.hpp>

namespace aoc2021::day3
{
	int part1(ranges::forward_range auto& input)
	{
		constexpr size_t size = ranges::range_value_t<decltype(input)>{}.size();
		using counts_t = std::array<int, size>;

		const size_t input_len = ranges::size(input);

		const auto counts = ranges::accumulate(input, counts_t{ 0 },
			[](auto counts, const auto& in)
			{
				auto bits = in.to_ulong();
				auto i = std::countr_zero(bits);
				while (i < size)
				{
					++counts[i];
					bits ^= 1ul << i;
					i = std::countr_zero(bits);
				}
				return counts;
			});

		const auto gamma = ranges::accumulate(
			counts | ranges::views::enumerate |
			ranges::views::transform(
				[input_len](std::pair<size_t, int> index_and_count)
				{
					auto [index, count] = index_and_count;
					return (count * 2 >= input_len ? 1ul << index : 0);
				}),
			0ul);

		const auto epsilon = gamma ^ ((1ul << size) - 1);

		return gamma * epsilon;
	}

	unsigned long part2_rating(const ranges::forward_range auto& input, const bool find)
	{
		constexpr size_t size = ranges::range_value_t<decltype(input)>{}.size();

		auto remaining = ranges::to<std::vector>(input);
		size_t remaining_len = ranges::size(remaining);
		for (size_t bit = size - 1; remaining_len > 1; --bit)
		{
			const size_t count = ranges::count_if(remaining,
				[&](const auto& in)
				{
					return in[bit] == 1;
				});

			const bool majority1s = (count * 2 >= remaining_len);
			remaining = remaining |
				ranges::views::filter(
					[&](const auto& in)
					{
						return in[bit] == (find ? majority1s : !majority1s);
					}) |
				ranges::to<std::vector>;
			remaining_len = ranges::size(remaining);
		}
		return remaining[0].to_ulong();
	}

	int part2(ranges::forward_range auto& input)
	{
		const auto O2_rating = part2_rating(input, true);
		const auto CO2_rating = part2_rating(input, false);

		return O2_rating * CO2_rating;
	}
}

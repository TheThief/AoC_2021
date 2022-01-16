#pragma once

#include <range/v3/all.hpp>
#include "../Common/stream_required.h"

#include <set>
#include <map>
#include <array>

namespace aoc2021::day8
{
	std::set<char> operator ""_set(const char* c, size_t s)
	{
		return { c, c+s };
	}

	std::size_t operator""_uz(std::size_t s)
	{
		return s;
	}

	struct display
	{
		std::array<std::set<char>, 10> digits;
		std::array<std::set<char>, 4> values;
	};

	struct puzzle_input
	{
		std::vector<display> displays;
	};

	std::istream& operator>>(std::istream& is, display& input)
	{
		for (int i = 0; i < 10; ++i)
		{
			std::string s;
			is >> s;
			input.digits[i] = s | ranges::to<std::set>;
		}

		is >> required{ '|' };

		for (int i = 0; i < 4; ++i)
		{
			std::string s;
			is >> s;
			input.values[i] = s | ranges::to<std::set>;
		}

		return is;
	}

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.displays = ranges::istream_view<display>(is) | ranges::to<std::vector>;

		return is;
	}

	int64_t part1(const puzzle_input& input)
	{
		return ranges::count_if(
			input.displays |
			ranges::views::for_each(&display::values),
			[](const auto& value) ->bool
			{
				// 1, 4, 7, 8
				return ranges::contains(std::array{2_uz, 4_uz, 3_uz, 7_uz}, value.size());
			});
	}

	auto decode(const std::array<std::set<char>, 10>& digits)
	{
		std::map<int, std::set<char>> valmap_r;

		// 1, 4, 7, 8
		//  ..    ..   --   -- 
		// .  |  |  | .  | |  |
		//  ..    --   ..   -- 
		// .  |  .  | .  | |  |
		//  ..    ..   ..   -- 
		for (auto& code : digits)
		{
			if (code.size() == 2)
			{
				valmap_r.insert({ 1, code });
			}
			else if (code.size() == 4)
			{
				valmap_r.insert({ 4, code });
			}
			else if (code.size() == 3)
			{
				valmap_r.insert({ 7, code });
			}
			else if (code.size() == 7)
			{
				valmap_r.insert({ 8, code });
			}
		}

		std::set<char> four_not_one;
		ranges::set_difference(valmap_r[4], valmap_r[1], std::inserter(four_not_one, four_not_one.begin()));

		// 2, 3, 5, 6, 9, 0
		//  --    --   --   --   --   -- 
		// .  |  .  | |  . |  . |  | |  |
		//  --    --   --   --   --   .. 
		// |  .  .  | .  | |  | .  | |  |
		//  --    --   --   --   --   -- 
		for (auto& code : digits)
		{
			if (code.size() == 5) // 2, 3, 5
			{
				if (ranges::includes(code, valmap_r[1])) // 3
				{
					valmap_r.insert({ 3, code });
				}
				else if (ranges::includes(code, four_not_one)) // 5
				{
					valmap_r.insert({ 5, code });
				}
				else
				{
					valmap_r.insert({ 2, code });
				}
			}
			else if (code.size() == 6) // 6, 9, 0
			{
				if (ranges::includes(code, valmap_r[1])) // 0, 9
				{
					if (ranges::includes(code, four_not_one)) // 9
					{
						valmap_r.insert({ 9, code });
					}
					else
					{
						valmap_r.insert({ 0, code });
					}
				}
				else
				{
					valmap_r.insert({ 6, code });
				}
			}
		}

		std::map<std::set<char>, int> valmap =
			ranges::views::zip(ranges::views::values(valmap_r), ranges::views::keys(valmap_r)) | ranges::to<std::map>;

		return valmap;
	}

	int64_t part2(const puzzle_input& input)
	{
		return ranges::accumulate(
			input.displays,
			INT64_C(0),
			std::plus(),
			[](const display& d)
			{
				auto valmap = decode(d.digits);
				return ranges::accumulate(
					d.values |
					ranges::views::reverse |
					ranges::views::enumerate,
					INT64_C(0),
					std::plus(),
					[&](std::pair<size_t, std::set<char>> index_and_code)
					{
						auto [index, code] = index_and_code;
						return int64_t(std::pow(10, index) * valmap[code]);
					});
			});
	}
}

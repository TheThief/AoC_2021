#pragma once

#include <range/v3/all.hpp>

#include <vector>
#include <charconv>

namespace aoc2021::day9
{
	struct puzzle_input
	{
		std::vector<std::vector<int8_t>> heights;
	};

	struct digit
	{
		int i;

		friend std::istream& operator>>(std::istream& is, digit& d)
		{
			char c = is.peek();
			auto result = std::from_chars(&c, &c + 1, d.i);
			if (result.ptr == &c + 1)
				is.ignore();
			else
				is.setstate(std::ios::failbit);

			return is;
		}

		operator int()
		{
			return i;
		}
	};

	template<typename T>
	struct line : std::vector<T>
	{
		friend std::istream& operator>>(std::istream& is, line& l)
		{
			std::string numbers_line;
			std::getline(is, numbers_line);
			std::istringstream ss(numbers_line);
			l = line(ranges::istream_view<T>(ss) | ranges::to<std::vector>);

			return is;
		}
	};

	using ssize_t = std::make_signed_t<std::size_t>;
	auto indices_2d(ranges::forward_range auto& input)
	{
		return ranges::views::cartesian_product(ranges::views::iota((ssize_t)0, (ssize_t)ranges::size(input)), ranges::views::iota((ssize_t)0, (ssize_t)ranges::size(input[0])));
	}

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.heights = ranges::istream_view<line<digit>>(is) | ranges::to<std::vector<std::vector<int8_t>>>;

		return is;
	}

	int64_t part1(const puzzle_input& input)
	{
		const auto size_y = ranges::size(input.heights);
		const auto size_x = ranges::size(input.heights[0]);

		auto low_points = indices_2d(input.heights) |
			ranges::views::filter(
				[&](auto index2d)
				{
					auto [y, x] = index2d;
					auto height = input.heights[y][x];
					return
						(x == 0 || height < input.heights[y][x - 1]) &&
						(x == size_x - 1 || height < input.heights[y][x + 1]) &&
						(y == 0 || height < input.heights[y - 1][x]) &&
						(y == size_y - 1 || height < input.heights[y + 1][x]);
				});

		auto low_values = low_points |
			ranges::views::transform(
				[&](auto index2d)
				{
					auto [y, x] = index2d;
					return 1 + input.heights[y][x];
				});
		return ranges::accumulate(low_values, INT64_C(0));
	}

	struct linespan
	{
		ssize_t x1, x2;
	};

	int fill(puzzle_input& input, ssize_t y, int ydir, linespan parent)
	{
		const auto size_y = (ssize_t)ranges::size(input.heights);
		const auto size_x = (ssize_t)ranges::size(input.heights[0]);
		int count = 0;

		ssize_t x1 = parent.x1;
		ssize_t x2 = x1;
		if (input.heights[y][x1] != 9)
		{
			for (; x1 >= 0 && input.heights[y][x1] < 9; --x1)
			{
				input.heights[y][x1] = 10;
				++count;
			}
			++x1;
			++x2;

			if (x1 < parent.x1 - 1)
			{
				count += fill(input, y - ydir, -ydir, { x1, parent.x1 - 1 });
			}
			goto scan;
		}

		while (true)
		{
			x1 = x2;
			for (; x1 < parent.x2 && input.heights[y][x1] >= 9; ++x1)
			{
			}
			x2 = x1;

			if (x2 >= parent.x2)
				break;

		scan:
			for (; x2 < size_x && input.heights[y][x2] < 9; ++x2)
			{
				input.heights[y][x2] = 10;
				++count;
			}

			if (ydir < 0 && y > 0)
			{
				count += fill(input, y + ydir, ydir, { x1, x2 });
			}
			if (ydir > 0 && y < size_y - 1)
			{
				count += fill(input, y + ydir, ydir, { x1, x2 });
			}

			if (x2 >= parent.x2)
				break;
		}

		if (x2 > parent.x2 + 1)
		{
			count += fill(input, y - ydir, -ydir, { parent.x2 + 1, x2 });
		}

		return count;
	}

	int fill_basin(puzzle_input& input, std::tuple<ssize_t, ssize_t> index2d)
	{
		const auto size_y = (ssize_t)ranges::size(input.heights);
		const auto size_x = (ssize_t)ranges::size(input.heights[0]);

		auto [y, x] = index2d;

		int count = 0;

		ssize_t x1 = x;
		for (; x1 >= 0 && input.heights[y][x1] < 9; --x1)
		{
			input.heights[y][x1] = 10;
			++count;
		}
		++x1;
		ssize_t x2 = x + 1;
		for (; x2 < size_x && input.heights[y][x2] < 9; ++x2)
		{
			input.heights[y][x2] = 10;
			++count;
		}

		linespan s = { x1, x2 };
		if (y > 0)
			count += fill(input, y - 1, -1, s);
		if (y < size_y - 1)
			count += fill(input, y + 1, +1, s);

		return count;
	}

	int64_t part2(const puzzle_input& input)
	{
		const auto size_y = ranges::size(input.heights);
		const auto size_x = ranges::size(input.heights[0]);

		auto low_points = indices_2d(input.heights) |
			ranges::views::filter(
				[&](auto index2d)
				{
					auto [y, x] = index2d;
					auto height = input.heights[y][x];
					return
						(x == 0 || height < input.heights[y][x - 1]) &&
						(x == size_x - 1 || height < input.heights[y][x + 1]) &&
						(y == 0 || height < input.heights[y - 1][x]) &&
						(y == size_y - 1 || height < input.heights[y + 1][x]);
				});

		puzzle_input temp = input;
		auto sizes = low_points |
			ranges::views::transform(
				[&](auto index2d)
				{
					return fill_basin(temp, index2d);
				}) | ranges::to<std::vector>;
		std::vector<int> greatest(3);
		ranges::partial_sort_copy(sizes, greatest, std::greater());
		return ranges::accumulate(greatest, 1, std::multiplies());
	}
}

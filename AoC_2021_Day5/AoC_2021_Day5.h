#pragma once

#include <optional>
#include <range/v3/all.hpp>
#include "../Common/stream_required.h"

namespace aoc2021::day5
{
	struct point
	{
		uint16_t x;
		uint16_t y;
	};

	struct line
	{
		std::array<point,2> points;
	};

	struct puzzle_input
	{
		std::vector<line> lines;
	};

	std::istream& operator>>(std::istream& is, point& p)
	{
		is >> p.x >> required{ "," } >> p.y;

		return is;
	}

	std::istream& operator>>(std::istream& is, line& l)
	{
		is >> l.points[0] >> required{ "->" } >> l.points[1];

		return is;
	}

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		input.lines = ranges::istream_view<line>(is) | ranges::to<std::vector>;

		return is;
	}

	template<size_t size>
	struct image
	{
		std::array<std::array<uint8_t, size>, size> pixels = {};

		void raster_line(const line& l)
		{
			const int x0 = l.points[0].x;
			const int y0 = l.points[0].y;
			const int x1 = l.points[1].x;
			const int y1 = l.points[1].y;

			const int dx = x1 - x0;
			const int dy = y1 - y0;
			const int sx = (dx < 0) ? -1 : (dx > 0);
			const int sy = (dy < 0) ? -1 : (dy > 0);

			const int steps = std::max(abs(dx), abs(dy));

			int x = x0;
			int y = y0;

			for (int i = 0; i <= steps; ++i)
			{
				++pixels[y][x];

				x += sx;
				y += sy;
			}
		}
	};

	template<size_t size>
	int part1(const puzzle_input& input)
	{
		auto hv_lines = input.lines |
			ranges::views::filter(
				[](const line& l)
				{
					return
						l.points[0].x == l.points[1].x ||
						l.points[0].y == l.points[1].y;
				});

		image<size> i;
		for (const line& line : hv_lines)
		{
			i.raster_line(line);
		}

		return ranges::accumulate(i.pixels, 0, std::plus(),
			[](const auto& row)
			{
				return ranges::accumulate(row, 0, std::plus(),
					[](const auto& pixel)
					{
						return pixel >= 2;
					});
			});
	}

	template<size_t size>
	int part2(const puzzle_input& input)
	{
		image<size> i;
		for (const line& line : input.lines)
		{
			i.raster_line(line);
		}

		return ranges::accumulate(i.pixels, 0, std::plus(),
			[](const auto& row)
			{
				return ranges::accumulate(row, 0, std::plus(),
					[](const auto& pixel)
					{
						return pixel >= 2;
					});
			});
	}
}

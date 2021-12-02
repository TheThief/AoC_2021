#pragma once

#include <variant>
#include <range/v3/all.hpp>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

namespace aoc2021::day2
{
	struct dist
	{
		int d;
	};
	struct forward : dist {};
	struct down : dist {};
	struct up : dist {};
	using move = std::variant<forward, down, up>;

	std::istream& operator>>(std::istream& is, move& m)
	{
		std::string s;
		int d;
		is >> s >> d;
		if (s == "forward")
		{
			m = forward{ d };
		}
		else if (s == "down")
		{
			m = down{ d };
		}
		else if (s == "up")
		{
			m = up{ d };
		}
		else
		{
			is.setstate(std::ios::failbit);
		}

		return is;
	}

	struct pos
	{
		int hpos = 0;
		int depth = 0;

		pos operator+(const move& rhs) const
		{
			return std::visit(
				overloaded(
					[this](const forward& m) { return pos{ hpos + m.d, depth }; },
					[this](const down& m)    { return pos{ hpos, depth + m.d }; },
					[this](const up& m)      { return pos{ hpos, depth - m.d }; }
			), rhs);
		}
	};

	struct pos2 : pos
	{
		int aim = 0;

		pos2 operator+(const move& rhs) const
		{
			return std::visit(
				overloaded(
					[this](const forward& m) { return pos2{ hpos + m.d, depth + m.d * aim, aim       }; },
					[this](const down& m)    { return pos2{ hpos,       depth,             aim + m.d }; },
					[this](const up& m)      { return pos2{ hpos,       depth,             aim - m.d }; }
			), rhs);
		}
	};

	int part1(ranges::forward_range auto& input)
	{
		const auto final_pos = ranges::accumulate(input, pos{});
		return final_pos.hpos * final_pos.depth;
	}

	int part2(ranges::forward_range auto& input)
	{
		const auto final_pos = ranges::accumulate(input, pos2{});
		return final_pos.hpos * final_pos.depth;
	}
}

#pragma once

#include <optional>
#include <range/v3/all.hpp>
#include "../Common/comma_separated.h"

namespace aoc2021::day4
{
	struct board
	{
		std::array<std::array<int, 5>, 5> numbers;
	};

	struct puzzle_input
	{
		std::vector<int> numbers;
		std::vector<board> boards;
	};

	std::istream& operator>>(std::istream& is, board& input)
	{
		//std::copy_n(std::istream_iterator<int>(is), 5*5, &input.numbers[0][0]); // consumes the correct number, but crashes at eof
		//ranges::copy_n(std::istream_iterator<int>(is), 5*5, &input.numbers[0][0]); // consumes one extra, *and* crashes at eof
		//std/ranges::copy(ranges::istream_view<int>(is) | ranges::views::take(5*5), &input.numbers[0][0]); // consumes one extra

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				is >> input.numbers[i][j];
			}
		}

		return is;
	}

	std::istream& operator>>(std::istream& is, puzzle_input& input)
	{
		std::string numbers_line;
		std::getline(is, numbers_line);
		std::istringstream ss(numbers_line);
		input.numbers = ranges::istream_view<comma_separated<int>>(ss) | ranges::to<std::vector<int>>;
		input.boards = ranges::istream_view<board>(is) | ranges::to<std::vector>;

		return is;
	}

	struct marked_board : board
	{
		std::array<std::array<bool, 5>, 5> marks = {};
	};

	std::optional<std::tuple<size_t, size_t>> index_of_number_in_board(const board& board, int number)
	{
		const auto all_indices = ranges::views::cartesian_product(ranges::views::indices(ranges::size(board.numbers)), ranges::views::indices(ranges::size(board.numbers[0])));
		auto matching_indexes =
			all_indices
			| ranges::views::filter(
				[&, number](auto index2d)
				{
					auto [y, x] = index2d;
					return board.numbers[y][x] == number;
				});
		if (ranges::empty(matching_indexes))
		{
			return std::nullopt;
		}
		else
		{
			return ranges::front(matching_indexes);
		}
	}

	bool is_winner(const marked_board& board, std::tuple<size_t, size_t> mark)
	{
		const auto [y, x] = mark;
		return
			ranges::all_of(board.marks[y], std::identity()) ||
			ranges::all_of(board.marks, [x](auto& row) { return row[x]; });
	}

	bool mark_board_is_winner(marked_board& board, int number_called)
	{
		const auto index2d = index_of_number_in_board(board, number_called);
		if (index2d)
		{
			const auto [y, x] = *index2d;
			board.marks[y][x] = true;

			return is_winner(board, *index2d);
		}
	}

	int score_board(const marked_board& board, int number_called)
	{
		const auto all_indices = ranges::views::cartesian_product(ranges::views::indices(ranges::size(board.numbers)), ranges::views::indices(ranges::size(board.numbers[0])));

		return number_called *
			ranges::accumulate(
				all_indices |
				ranges::views::filter(
					[&](auto index2d)
					{
						const auto [y, x] = index2d;
						return !board.marks[y][x];
					}) |
				ranges::views::transform(
					[&](auto index2d)
					{
						const auto [y, x] = index2d;
						return board.numbers[y][x];
					}),
				0);
	}

	int part1(const puzzle_input& input)
	{
		std::vector<marked_board> boards = input.boards | ranges::views::transform([](const board& board) { return marked_board(board); }) | ranges::to<std::vector>;

		for (int number_called : input.numbers)
		{
			for (marked_board& board : boards)
			{
				if (mark_board_is_winner(board, number_called))
				{
					return score_board(board, number_called);
				}
			}
		}
		__assume(0);
		return 0;
	}

	int part2(const puzzle_input& input)
	{
		std::vector<marked_board> boards = input.boards | ranges::views::transform([](const board& board) { return marked_board(board); }) | ranges::to<std::vector>;

		for (int number_called : input.numbers)
		{
			if (boards.size() == 1)
			{
				auto& board = ranges::front(boards);
				if (mark_board_is_winner(board, number_called))
				{
					return score_board(board, number_called);
				}
			}
			else
			{
				std::erase_if(
					boards,
					[number_called](marked_board& board)
					{
						return mark_board_is_winner(board, number_called);
					});
			}
		}
		__assume(0);
	}
}

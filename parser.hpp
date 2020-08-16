#pragma once

#include "types.hpp"
#include <string_view>
#include <optional>
#include <tuple>

constexpr bool char_is_letter(char const c);
constexpr bool char_is_digit(char const c);
constexpr bool char_is_delimiter(char const c);
constexpr bool char_is_symbol_initial(char const c);
constexpr bool char_is_symbol_subsequent(char const c);

void munch(std::string_view &sv);

constexpr std::optional<std::tuple<Integer, std::string_view>> parse_integer(
		std::string_view sv);
std::optional<std::tuple<Symbol, std::string_view>> parse_symbol(
		std::string_view sv);

#include "parser.hpp"
#include <cstdint>

constexpr bool char_is_letter(char const c) {
	// letter: /[a-zA-Z]/

	switch(c) {
		case 'a' ... 'z':
		case 'A' ... 'Z':
			return true;
	}
	return false;
}

constexpr bool char_is_digit(char const c) {
	// digit: /[0-9]/
	return c >= '0' && c <= '9';
}

constexpr bool char_is_delimiter(char const c) {
	switch(c) {
		case ' ':
		case '\n':
		case '\t':
		case '\'':
		case '(':
		case ')':
			return true;
	}
	return false;
}

constexpr bool char_is_symbol_initial(char const c) {
	// symbol_initial: /[a-zA-Z!$%&*/:<=>?^_~]/

	if(char_is_letter(c)) {
		return true;
	}

	switch(c) {
		case '!':
		case '$':
		case '%':
		case '&':
		case '*':
		case '/':
		case ':':
		case '<':
		case '=':
		case '>':
		case '?':
		case '^':
		case '_':
		case '~':
			return true;
	}
	return false;
}

constexpr bool char_is_symbol_subsequent(char const c) {
	// symbol_subsequent: symbol_initial | digit | /[+.@-]/

	if(char_is_symbol_initial(c) || char_is_digit(c)) {
		return true;
	}

	switch(c) {
		case '+':
		case '.':
		case '@':
		case '-':
			return true;
	}
	return false;
}

void munch(std::string_view &sv) {
	sv.remove_prefix(sv.find_first_not_of(" \t\n"));
}

constexpr std::optional<std::tuple<Integer, std::string_view>> parse_integer(
		std::string_view sv) {
	// integer : /-?[0-9]+/

	std::uint_fast8_t state = 0;

	int num = 0;
	bool negative = false;

	while(true) {
		switch(state) {
			case 0:
				if(sv[0] == '-') {
					sv.remove_prefix(1);
					negative = true;
				}
				state = 1;
				break;
			case 1:
				if(char_is_digit(sv[0])) {
					num = sv[0] - '0';
					sv.remove_prefix(1);
					state = 2;
				} else {
					state = 3;
				}
				break;
			case 2:
				if(char_is_digit(sv[0])) {
					num = num * 10 + (sv[0] - '0');
					sv.remove_prefix(1);
				} else if(char_is_delimiter(sv[0])) {
					state = 4;
				} else {
					state = 3;
				}
				break;
			case 3:
				return std::nullopt;
			case 4:
				if(negative) {
					num *= -1;
				}
				return {{{num}, sv}};
		}

		if(sv.empty()) {
			state = state == 2 ? 4 : 3;
		}
	}
}

std::optional<std::tuple<Symbol, std::string_view>> parse_symbol(
		std::string_view sv) {
	// symbol: symbol_initial symbol_subsequent*
	// TODO Add peculiar identifiers (+ | - | ...)

	uint_fast8_t state = 0;

	auto start = cbegin(sv);

	while(true) {
		switch(state) {
			case 0:
				if(char_is_symbol_initial(sv[0])) {
					sv.remove_prefix(1);
					state = 1;
				} else {
					state = 2;
				}
				break;
			case 1:
				if(char_is_symbol_subsequent(sv[0])) {
					sv.remove_prefix(1);
				} else if(char_is_delimiter(sv[0])) {
					state = 3;
				} else {
					state = 2;
				}
				break;
			case 2:
				return std::nullopt;
			case 3:
				return {{{std::string(start, begin(sv))}, sv}};
		}

		if(sv.empty()) {
			state = state == 1 ? 3 : 2;
		}
	}
}

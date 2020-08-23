#include "parser.hpp"
#include <algorithm>

std::optional<std::tuple<Symbol, TokenIter>> parse_symbol(
		TokenIter begin, TokenIter end) {
	// symbol: (symbol_initial symbol_subsequent*) | peculiar_identifier
	// peculiar_identifier: + | - | ...

	if(begin == end || begin->type != TokenType::Ident || begin->str.empty()) {
		return std::nullopt;
	}

	if(begin->str == "+" || begin->str == "-" || begin->str == "..."
			|| (char_is_symbol_initial(begin->str[0])
					&& std::all_of(std::begin(begin->str) + 1,
							std::end(begin->str), char_is_symbol_subsequent))) {
		return {{{begin->str}, begin + 1}};
	} else {
		return std::nullopt;
	}
}

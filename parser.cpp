#include "parser.hpp"
#include "functions.hpp"
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

std::optional<std::tuple<Cons, TokenIter>> parse_cons(
		TokenIter begin, TokenIter end) {
	// TODO Dotted lists
	if(auto const a = parse_lparen(begin, end); a) {
		begin = *a;
	} else {
		return std::nullopt;
	}

	Cons ret = make_nil();
	Cons *tail = &ret;

	while(true) {
		if(auto const a = parse_expression(begin, end); a) {
			begin = std::get<TokenIter>(*a);
			tail->first = std::get<std::shared_ptr<Object const>>(*a);
			tail->second = std::make_shared<Object const>(make_nil());
			tail = const_cast<Cons *>(std::get_if<Cons>(tail->second.get()));
			// TODO Use recursion instead of mutation, since these values aren't
			// supposed to even be mutable
		} else if(auto const a = parse_rparen(begin, end); a) {
			begin = *a;
			return {{ret, begin}};
		} else {
			return std::nullopt;
		}
	}
}

std::optional<std::tuple<std::shared_ptr<Object const>, TokenIter>>
parse_expression(TokenIter begin, TokenIter end) {
	if(auto const a = parse_cons(begin, end); a) {
		return {{std::make_shared<Object const>(std::get<Cons>(*a)),
				std::get<TokenIter>(*a)}};
	} else if(auto const a = parse_integer(begin, end); a) {
		return {{std::make_shared<Object const>(std::get<Integer>(*a)),
				std::get<TokenIter>(*a)}};
	} else if(auto const a = parse_symbol(begin, end); a) {
		return {{std::make_shared<Object const>(std::get<Symbol>(*a)),
				std::get<TokenIter>(*a)}};
	} else {
		return std::nullopt;
	}
}

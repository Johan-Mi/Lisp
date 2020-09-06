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

std::optional<std::tuple<Quote, TokenIter>> parse_quoted_expression(
		TokenIter begin, TokenIter end) {
	if(auto const a = parse_quote(begin, end)) {
		if(auto const b = parse_expression(*a, end)) {
			return {{Quote{std::get<std::shared_ptr<Object const>>(*b)},
					std::get<TokenIter>(*b)}};
		}
	}

	return std::nullopt;
}

std::optional<std::tuple<Cons, TokenIter>> parse_cons(
		TokenIter begin, TokenIter end) {
	if(auto const a = parse_lparen(begin, end)) {
		return parse_cons_helper(*a, end);
	} else {
		return std::nullopt;
	}
}

std::optional<std::tuple<Cons, TokenIter>> parse_cons_helper(
		TokenIter begin, TokenIter end) {
	if(auto const a = parse_rparen(begin, end)) {
		return {{make_nil(), *a}};
	} else if(auto const a = parse_expression(begin, end)) {
		if(auto const b = parse_dot(std::get<TokenIter>(*a), end)) {
			if(auto const c = parse_expression(*b, end)) {
				if(auto const d = parse_rparen(std::get<TokenIter>(*c), end)) {
					return {{Cons{std::get<std::shared_ptr<Object const>>(*a),
									 std::get<std::shared_ptr<Object const>>(
											 *c)},
							*d}};
				}
			}
		} else if(auto const b
				= parse_cons_helper(std::get<TokenIter>(*a), end)) {
			return {{Cons{std::get<std::shared_ptr<Object const>>(*a),
							 std::make_shared<Object const>(
									 std::get<Cons>(*b))},
					std::get<TokenIter>(*b)}};
		}
	}

	return std::nullopt;
}

std::optional<std::tuple<std::shared_ptr<Object const>, TokenIter>>
parse_expression(TokenIter begin, TokenIter end) {
	if(auto const a = parse_cons(begin, end)) {
		return {{std::make_shared<Object const>(std::get<Cons>(*a)),
				std::get<TokenIter>(*a)}};
	} else if(auto const a = parse_quoted_expression(begin, end)) {
		return {{std::make_shared<Object const>(std::get<Quote>(*a)),
				std::get<TokenIter>(*a)}};
	} else if(auto const a = parse_integer(begin, end)) {
		return {{std::make_shared<Object const>(std::get<Integer>(*a)),
				std::get<TokenIter>(*a)}};
	} else if(auto const a = parse_symbol(begin, end)) {
		return {{std::make_shared<Object const>(std::get<Symbol>(*a)),
				std::get<TokenIter>(*a)}};
	} else {
		return std::nullopt;
	}
}

std::optional<std::tuple<std::vector<std::shared_ptr<Object const>>, TokenIter>>
parse_expressions(TokenIter begin, TokenIter end) {
	std::vector<std::shared_ptr<Object const>> ret;

	while(true) {
		if(auto const a = parse_expression(begin, end)) {
			ret.push_back(std::get<std::shared_ptr<Object const>>(*a));
			begin = std::get<TokenIter>(*a);
		} else {
			if(ret.empty()) {
				return std::nullopt;
			} else {
				return {{ret, begin}};
			}
		}
	}
}

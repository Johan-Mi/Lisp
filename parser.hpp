#pragma once

#include "types.hpp"
#include "lexer.hpp"
#include <string_view>
#include <optional>
#include <tuple>
#include <vector>

using TokenIter = std::vector<Token>::const_iterator;

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

constexpr std::optional<std::tuple<Integer, TokenIter>> parse_integer(
		TokenIter begin, TokenIter end) {
	// integer : /-?[0-9]+/

	if(begin == end || begin->type != TokenType::Ident || begin->str.empty()) {
		return std::nullopt;
	}

	std::string_view sv = begin->str;

	int num = 0;
	bool negative;

	if((negative = sv[0] == '-')) {
		if(sv.size() >= 2) {
			sv.remove_prefix(1);
		} else {
			return std::nullopt;
		}
	}

	for(char const c : sv) {
		if(char_is_digit(c)) {
			num = num * 10 + (c - '0');
		} else {
			return std::nullopt;
		}
	}

	return {{{negative ? -num : num}, begin + 1}};
}

std::optional<std::tuple<Symbol, TokenIter>> parse_symbol(
		TokenIter begin, TokenIter end);

constexpr std::optional<TokenIter> parse_lparen(
		TokenIter begin, TokenIter end) {
	if(begin != end && begin->type == TokenType::LParen) {
		return {begin + 1};
	} else {
		return std::nullopt;
	}
}

constexpr std::optional<TokenIter> parse_rparen(
		TokenIter begin, TokenIter end) {
	if(begin != end && begin->type == TokenType::RParen) {
		return {begin + 1};
	} else {
		return std::nullopt;
	}
}

constexpr std::optional<TokenIter> parse_quote(TokenIter begin, TokenIter end) {
	if(begin != end && begin->type == TokenType::Quote) {
		return {begin + 1};
	} else {
		return std::nullopt;
	}
}

constexpr std::optional<TokenIter> parse_dot(TokenIter begin, TokenIter end) {
	if(begin != end && begin->type == TokenType::Ident && begin->str == ".") {
		return {begin + 1};
	} else {
		return std::nullopt;
	}
}

std::optional<std::tuple<Quote, TokenIter>> parse_quoted_expression(
		TokenIter begin, TokenIter end);

std::optional<std::tuple<Cons, TokenIter>> parse_cons(
		TokenIter begin, TokenIter end);

std::optional<std::tuple<Cons, TokenIter>> parse_cons_helper(
		TokenIter begin, TokenIter end);

std::optional<std::tuple<std::shared_ptr<Object const>, TokenIter>>
parse_expression(TokenIter begin, TokenIter end);

std::optional<std::tuple<std::vector<std::shared_ptr<Object const>>, TokenIter>>
parse_expressions(TokenIter begin, TokenIter end);

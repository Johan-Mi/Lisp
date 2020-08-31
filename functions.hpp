#pragma once

#include <string>

#include "types.hpp"

Cons make_nil();

bool is_nil(Cons const &obj);

std::shared_ptr<Object const> car(std::shared_ptr<Object const> const obj);
std::shared_ptr<Object const> car(Cons const &obj);
std::shared_ptr<Object const> cdr(std::shared_ptr<Object const> const obj);
std::shared_ptr<Object const> cdr(Cons const &obj);
std::shared_ptr<Object const> add(std::shared_ptr<Object const> const lhs,
		std::shared_ptr<Object const> const rhs);
std::shared_ptr<Object const> add(Integer const &lhs, Integer const &rhs);

Cons cons(std::shared_ptr<Object const> const first,
		std::shared_ptr<Object const> const second);

size_t list_length(Cons const &list, size_t const accum = 0);

Cons make_list();

Cons make_list(auto const &first, auto const &... rest) {
	return cons(first, std::make_shared<Object const>(make_list(rest...)));
}

Cons make_unterminated_list(
		auto const &first, auto const &second, auto const &... rest) {
	return cons(first,
			std::make_shared<Object const>(
					make_unterminated_list(second, rest...)));
}

Cons make_unterminated_list(auto const &first, auto const &second) {
	return cons(first, second);
}

Cons join_two_lists(std::shared_ptr<Object const> const first,
		std::shared_ptr<Object const> const second, Cons const &last);
Cons join_two_lists(Cons const &first, Cons const &second, Cons const &last);

std::shared_ptr<Object const> apply(std::shared_ptr<Object const> const func,
		Cons const &args, Cons const &env);
std::shared_ptr<Object const> apply(
		BuiltinFunction const &func, Cons const &args, Cons const &env);
std::shared_ptr<Object const> apply(
		Function const &func, Cons const &args, Cons const &env);

std::shared_ptr<Object const> eval(
		std::shared_ptr<Object const> const expr, Cons const &env);
std::shared_ptr<Object const> eval(Cons const &list, Cons const &env);
std::shared_ptr<Object const> eval(Quote const &quote, Cons const &env);
std::shared_ptr<Object const> eval(Symbol const &symbol, Cons const &env);
std::shared_ptr<Object const> eval(Integer const &integer, Cons const &env);

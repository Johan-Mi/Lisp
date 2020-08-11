#pragma once

#include <string>

#include "types.hpp"

std::string to_string(std::shared_ptr<Object> obj);
std::string to_string(Nil const &obj);
std::string to_string(Cons const &obj);
std::string to_string(Integer const &obj);
std::string to_string(Bit const &obj);
std::string to_string(Symbol const &obj);
std::string to_string(Error const &obj);
std::string to_string(Function const &obj);
std::string to_string(BuiltinFunction const &obj);

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	return accum + " . " + to_string(obj) + ')';
}

std::string to_string_cons(
		std::string const &accum, std::shared_ptr<Object> obj);
template<>
std::string to_string_cons(std::string const &accum, Nil const &obj);
template<>
std::string to_string_cons(std::string const &accum, Cons const &obj);

std::shared_ptr<Object> car(std::shared_ptr<Object> obj);
std::shared_ptr<Object> car(Cons const &obj);
std::shared_ptr<Object> car(Nil const &obj);
std::shared_ptr<Object> cdr(std::shared_ptr<Object> obj);
std::shared_ptr<Object> cdr(Cons const &obj);
std::shared_ptr<Object> cdr(Nil const &obj);

Cons cons(std::shared_ptr<Object> first, std::shared_ptr<Object> second);

size_t list_length(size_t const accum, Cons const &list);

Cons make_list(auto const &first, auto const &... rest) {
	return cons(first, std::make_shared<Object>(make_list(rest...)));
}

Cons make_list(auto const &first) {
	return cons(first, std::make_shared<Object>(Nil{}));
}

Cons make_unterminated_list(
		auto const &first, auto const &second, auto const &... rest) {
	return cons(first,
			std::make_shared<Object>(make_unterminated_list(second, rest...)));
}

Cons make_unterminated_list(auto const &first, auto const &second) {
	return cons(first, second);
}

std::shared_ptr<Object> apply(BuiltinFunction const &func, Cons const &args);

std::shared_ptr<Object> nth(size_t const index, std::shared_ptr<Object> list);
std::shared_ptr<Object> nth(size_t const index, Cons const &list);
std::shared_ptr<Object> nth(size_t const index, Nil const &list);

std::shared_ptr<Object> wrapped_car(Cons const &args);
std::shared_ptr<Object> wrapped_cdr(Cons const &args);

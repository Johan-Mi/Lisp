#pragma once

#include "types.hpp"

std::string to_string(std::shared_ptr<Object const> const obj);
std::string to_string(Cons const &obj);
std::string to_string(Integer const &obj);
std::string to_string(Symbol const &obj);
std::string to_string(Error const &obj);
std::string to_string(Function const &obj);
std::string to_string(BuiltinFunction const &obj);
std::string to_string(Quote const &obj);

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	return accum + " . " + to_string(obj) + ')';
}

std::string to_string_cons(
		std::string const &accum, std::shared_ptr<Object const> const obj);
template<>
std::string to_string_cons(std::string const &accum, Cons const &obj);

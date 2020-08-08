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

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	return accum + " . " + to_string(obj) + ')';
}

std::string to_string_cons(std::string const &accum,
		std::shared_ptr<Object> obj);
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

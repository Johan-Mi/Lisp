#pragma once

#include <string>

#include "types.hpp"

std::string to_string(Object const &obj);
std::string to_string(Nil const &obj);
std::string to_string(Cons const &obj);
std::string to_string(Integer const &obj);
std::string to_string(Bit const &obj);
std::string to_string(Symbol const &obj);
std::string to_string(Error const &obj);

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	return accum + " . " + to_string(obj) + ')';
}

template<>
std::string to_string_cons(std::string const &accum, Object const &obj);
template<>
std::string to_string_cons(std::string const &accum, Nil const &obj);
template<>
std::string to_string_cons(std::string const &accum, Cons const &obj);

std::shared_ptr<Object> car(Object const &obj);
std::shared_ptr<Object> car(Cons const &obj);
std::shared_ptr<Object> car(Nil const &obj);
std::shared_ptr<Object> cdr(Object const &obj);
std::shared_ptr<Object> cdr(Cons const &obj);
std::shared_ptr<Object> cdr(Nil const &obj);

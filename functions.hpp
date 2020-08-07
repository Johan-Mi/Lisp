#pragma once

#include <string>

#include "types.hpp"

std::string to_string(Object const &obj);
std::string to_string(Nil const &obj);
std::string to_string(Cons const &obj);
std::string to_string(Integer const &obj);
std::string to_string(Bit const &obj);
std::string to_string(Symbol const &obj);

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	if constexpr(std::is_same<T, Object>()) {
		return std::visit([&](auto &&arg){
				return to_string_cons(accum, arg);
				}, obj);
	} else if constexpr(std::is_same<T, Nil>()){
		return accum + ')';
	} else if constexpr(std::is_same<T, Cons>()){
		return to_string_cons(accum + ' ' + to_string(*obj.first), *obj.second);
	} else {
		return accum + " . " + to_string(obj) + ')';
	}
}

std::unique_ptr<Object> car(Object const &obj);
std::unique_ptr<Object> car(Cons const &obj);
std::unique_ptr<Object> car(Nil const &obj);
std::unique_ptr<Object> cdr(Object const &obj);
std::unique_ptr<Object> cdr(Cons const &obj);
std::unique_ptr<Object> cdr(Nil const &obj);

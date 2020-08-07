#pragma once

#include <variant>
#include <memory>
#include <string>

struct LispNil;
struct LispCons;
struct LispInteger;

using LispObject = std::variant<LispNil, LispCons, LispInteger>;

struct LispNil {};

struct LispCons {
	std::unique_ptr<LispObject> first;
	std::unique_ptr<LispObject> second;
};

struct LispInteger {
	int value;
};

std::string to_string(LispObject const &obj);
std::string to_string(LispNil const &obj);
std::string to_string(LispCons const &obj);
std::string to_string(LispInteger const &obj);

template<class T>
std::string to_string_cons(std::string const &accum, T const &obj) {
	if constexpr(std::is_same<T, LispObject>()) {
		return std::visit([&](auto &&arg){
				return to_string_cons(accum, arg);
				}, obj);
	} else if constexpr(std::is_same<T, LispNil>()){
		return accum + ')';
	} else if constexpr(std::is_same<T, LispCons>()){
		return to_string_cons(accum + ' ' + to_string(*obj.first), *obj.second);
	} else {
		return accum + ' ' + to_string(obj) + ')';
	}
}

#pragma once

#include <variant>
#include <memory>
#include <string>

struct Nil;
struct Cons;
struct Integer;
struct Bit;
struct Symbol;

using Object = std::variant<Nil, Cons, Integer, Bit, Symbol>;

struct Nil {};

struct Cons {
	std::unique_ptr<Object> first;
	std::unique_ptr<Object> second;

	Cons(Cons const &other);
	Cons(std::unique_ptr<Object> const &first,
			std::unique_ptr<Object> const &second);
};

struct Integer {
	int value;
};

struct Bit {
	bool value;
};

struct Symbol {
	std::string value;
};

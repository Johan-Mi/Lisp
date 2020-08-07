#pragma once

#include <variant>
#include <memory>

struct Nil;
struct Cons;
struct Integer;

using Object = std::variant<Nil, Cons, Integer>;

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

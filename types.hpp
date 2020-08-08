#pragma once

#include <variant>
#include <memory>
#include <string>

using Object = std::variant<struct Nil, struct Cons, struct Integer,
	  struct Bit, struct Symbol, struct Function, struct Error>;

struct Nil {};

struct Cons {
	std::shared_ptr<Object> first;
	std::shared_ptr<Object> second;
};

struct Integer {
	int value;
};

struct Bit {
	bool value;
};

struct Symbol {
	std::string name;
};

struct Function {
	Cons parameters;
	std::shared_ptr<Object> body;
};

struct Error {
	std::string message;
};

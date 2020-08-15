#pragma once

#include <variant>
#include <memory>
#include <string>
#include <string_view>

struct Integer {
	int value;
};

struct Bit {
	bool value;
};

struct Symbol {
	std::string name;

	bool operator<=>(Symbol const &other) const = default;
};

struct Error {
	std::string message;
};

using Object = std::variant<struct Cons, Integer, Bit, Symbol, struct Function,
		Error, struct BuiltinFunction, struct Quote>;

struct Cons {
	std::shared_ptr<Object const> first;
	std::shared_ptr<Object const> second;
};

struct BuiltinFunction {
	std::shared_ptr<Object const> (*func)(Cons const &, Cons const &);
};

struct Function {
	Cons parameters;
	std::shared_ptr<Object const> body;
};

struct Quote {
	std::shared_ptr<Object const> contained;
};

template<class T>
constexpr inline std::string_view name_of_type = "<unknown type>";
template<>
constexpr inline std::string_view name_of_type<Cons> = "<type 'cons'>";
template<>
constexpr inline std::string_view name_of_type<Integer> = "<type 'integer'>";
template<>
constexpr inline std::string_view name_of_type<Bit> = "<type 'bit'>";
template<>
constexpr inline std::string_view name_of_type<Symbol> = "<type 'symbol'>";
template<>
constexpr inline std::string_view name_of_type<Function> = "<type 'function'>";
template<>
constexpr inline std::string_view name_of_type<Error> = "<type 'error'>";
template<>
constexpr inline std::string_view
		name_of_type<BuiltinFunction> = "<type 'builtin function'>";
template<>
constexpr inline std::string_view name_of_type<Quote> = "<type 'quote'>";

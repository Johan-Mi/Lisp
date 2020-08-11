#pragma once

#include <variant>
#include <memory>
#include <string>
#include <string_view>

struct Nil {};

struct Integer {
	int value;
};

struct Bit {
	bool value;
};

struct Symbol {
	std::string name;
};

struct Error {
	std::string message;
};

using Object = std::variant<Nil, struct Cons, Integer, Bit, Symbol,
		struct Function, Error, struct BuiltinFunction>;

struct Cons {
	std::shared_ptr<Object> first;
	std::shared_ptr<Object> second;
};

struct BuiltinFunction {
	std::shared_ptr<Object> (*func)(Cons const &);
};

struct Function {
	Cons parameters;
	std::shared_ptr<Object> body;
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
constexpr inline std::string_view name_of_type<Nil> = name_of_type<Cons>;

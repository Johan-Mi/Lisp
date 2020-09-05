#pragma once

#include <string>
#include <variant>

#include "types.hpp"

template<typename T, size_t index = 0>
constexpr size_t obj_index() {
	if constexpr(index == std::variant_size_v<Object>) {
		return index;
	} else if constexpr(std::is_same_v<
								std::variant_alternative_t<index, Object>, T>) {
		return index;
	} else {
		return obj_index<T, index + 1>();
	}
}

Cons make_nil();

bool is_nil(Cons const &obj);

std::shared_ptr<Object const> car(std::shared_ptr<Object const> const obj);
std::shared_ptr<Object const> car(Cons const &obj);
std::shared_ptr<Object const> cdr(std::shared_ptr<Object const> const obj);
std::shared_ptr<Object const> cdr(Cons const &obj);
std::shared_ptr<Object const> add(std::shared_ptr<Object const> const lhs,
		std::shared_ptr<Object const> const rhs);
std::shared_ptr<Object const> sub(std::shared_ptr<Object const> const lhs,
		std::shared_ptr<Object const> const rhs);
std::shared_ptr<Object const> mul(std::shared_ptr<Object const> const lhs,
		std::shared_ptr<Object const> const rhs);

size_t list_length(Cons const &list, size_t const accum = 0);

Cons make_list();

Cons make_list(auto const &first, auto const &... rest) {
	return Cons{first, std::make_shared<Object const>(make_list(rest...))};
}

Cons join_two_lists(std::shared_ptr<Object const> const first,
		std::shared_ptr<Object const> const second, Cons const &last);
Cons join_two_lists(Cons const &first, Cons const &second, Cons const &last);

Cons eval_list_elements(Cons const &list, Cons const &env);

std::shared_ptr<Object const> apply(std::shared_ptr<Object const> const func,
		Cons const &args, Cons const &env);
std::shared_ptr<Object const> apply(
		BuiltinFunction const &func, Cons const &args, Cons const &env);
std::shared_ptr<Object const> apply(
		Function const &func, Cons const &args, Cons const &env);

std::shared_ptr<Object const> eval(
		std::shared_ptr<Object const> const expr, Cons const &env);
std::shared_ptr<Object const> eval(Cons const &list, Cons const &env);
std::shared_ptr<Object const> eval(Symbol const &symbol, Cons const &env);

constexpr std::string_view name_of_contained_type(Object const &obj) {
	return std::visit(
			[](auto const &contained) {
				return name_of_type<std::decay_t<decltype(contained)>>;
			},
			obj);
}

std::string make_type_error_helper(Object const &first, auto const &... rest) {
	if constexpr(sizeof...(rest) == 0) {
		return std::string(name_of_contained_type(first)) + ')';
	} else {
		return std::string(name_of_contained_type(first)) + ' '
				+ make_type_error_helper(rest...);
	}
}

Error make_type_error(
		std::string_view const function_name, auto const &... objs) {
	static_assert(sizeof...(objs));
	return Error{std::string(function_name)
			+ " is not callable with argument types ("
			+ make_type_error_helper(objs...)};
}

bool is_proper_list(Cons const &list);

std::optional<Error> ensure_n_args(
		std::string_view const func_name, size_t n, Cons const &list);

#include "functions.hpp"
#include "to-string.hpp"

Cons make_nil() {
	return {nullptr, nullptr};
}

bool is_nil(Cons const &obj) {
	return !obj.first;
}

std::shared_ptr<Object const> car(std::shared_ptr<Object const> const obj) {
	switch(obj->index()) {
		case obj_index<Error>():
			return obj;
		case obj_index<Cons>():
			return car(std::get<Cons>(*obj));
		default:
			return std::make_shared<Object const>(make_type_error("car", *obj));
	}
}

std::shared_ptr<Object const> car(Cons const &obj) {
	if(is_nil(obj)) {
		return std::make_shared<Object const>(make_nil());
	} else {
		return obj.first;
	}
}

std::shared_ptr<Object const> cdr(std::shared_ptr<Object const> const obj) {
	switch(obj->index()) {
		case obj_index<Error>():
			return obj;
		case obj_index<Cons>():
			return cdr(std::get<Cons>(*obj));
		default:
			return std::make_shared<Object const>(make_type_error("cdr", *obj));
	}
}

std::shared_ptr<Object const> cdr(Cons const &obj) {
	if(is_nil(obj)) {
		return std::make_shared<Object const>(make_nil());
	} else {
		return obj.second;
	}
}

std::shared_ptr<Object const> add(std::shared_ptr<Object const> const lhs_obj,
		std::shared_ptr<Object const> const rhs_obj) {
	if(std::holds_alternative<Error>(*lhs_obj)) {
		return lhs_obj;
	}
	if(std::holds_alternative<Error>(*rhs_obj)) {
		return rhs_obj;
	}

	if(auto const lhs = std::get_if<Integer>(lhs_obj.get()),
			rhs = std::get_if<Integer>(rhs_obj.get());
			lhs && rhs) {
		return std::make_shared<Object const>(Integer{lhs->value + rhs->value});
	}

	return std::make_shared<Object const>(
			make_type_error("add", *lhs_obj, *rhs_obj));
}

std::shared_ptr<Object const> sub(std::shared_ptr<Object const> const lhs_obj,
		std::shared_ptr<Object const> const rhs_obj) {
	if(std::holds_alternative<Error>(*lhs_obj)) {
		return lhs_obj;
	}
	if(std::holds_alternative<Error>(*rhs_obj)) {
		return rhs_obj;
	}

	if(auto const lhs = std::get_if<Integer>(lhs_obj.get()),
			rhs = std::get_if<Integer>(rhs_obj.get());
			lhs && rhs) {
		return std::make_shared<Object const>(Integer{lhs->value - rhs->value});
	}

	return std::make_shared<Object const>(
			make_type_error("sub", *lhs_obj, *rhs_obj));
}

std::shared_ptr<Object const> mul(std::shared_ptr<Object const> const lhs_obj,
		std::shared_ptr<Object const> const rhs_obj) {
	if(std::holds_alternative<Error>(*lhs_obj)) {
		return lhs_obj;
	}
	if(std::holds_alternative<Error>(*rhs_obj)) {
		return rhs_obj;
	}

	if(auto const lhs = std::get_if<Integer>(lhs_obj.get()),
			rhs = std::get_if<Integer>(rhs_obj.get());
			lhs && rhs) {
		return std::make_shared<Object const>(Integer{lhs->value * rhs->value});
	}

	return std::make_shared<Object const>(
			make_type_error("mul", *lhs_obj, *rhs_obj));
}

size_t list_length(Cons const &list, size_t const accum) {
	if(is_nil(list)) {
		return accum;
	} else if(std::holds_alternative<Cons>(*cdr(list))) {
		return list_length(std::get<Cons>(*cdr(list)), accum + 1);
	} else {
		return accum + 1;
		// TODO Warn if cdr is not nil?
	}
}

Cons make_list() {
	return make_nil();
}

Cons join_two_lists(std::shared_ptr<Object const> const first_obj,
		std::shared_ptr<Object const> const second_obj, Cons const &last) {
	if(auto const first = std::get_if<Cons>(first_obj.get()),
			second = std::get_if<Cons>(second_obj.get());
			first && second) {
		return join_two_lists(*first, *second, last);
	}

	return last;
}

Cons join_two_lists(Cons const &first, Cons const &second, Cons const &last) {
	if(is_nil(first) || is_nil(second)) {
		return last;
	} else {
		return Cons{
				std::make_shared<Object const>(Cons{car(first), car(second)}),
				std::make_shared<Object const>(
						join_two_lists(cdr(first), cdr(second), last))};
	}
}

Cons eval_list_elements(Cons const &list, Cons const &env) {
	if(is_nil(list)) {
		return list;
	} else if(std::holds_alternative<Cons>(*cdr(list))) {
		return Cons{eval(car(list), env),
				std::make_shared<Object const>(
						eval_list_elements(std::get<Cons>(*cdr(list)), env))};
	} else {
		return Cons{eval(car(list), env),
				std::make_shared<Object const>(make_nil())};
		// TODO Don't pretend that all lists are null-terminated
	}
}

std::shared_ptr<Object const> apply(
		std::shared_ptr<Object const> const func_obj, Cons const &args,
		Cons const &env) {
	switch(func_obj->index()) {
		case obj_index<Error>():
			return func_obj;
		case obj_index<Function>():
			return apply(std::get<Function>(*func_obj), args, env);
		case obj_index<BuiltinFunction>():
			return apply(std::get<BuiltinFunction>(*func_obj), args, env);
		default:
			return std::make_shared<Object const>(
					make_type_error("apply", *func_obj));
	}
}

std::shared_ptr<Object const> apply(
		BuiltinFunction const &func, Cons const &args, Cons const &env) {
	return func.func(args, env);
}

std::shared_ptr<Object const> apply(
		Function const &func, Cons const &args, Cons const &env) {
	return eval(func.body,
			join_two_lists(
					func.parameters, eval_list_elements(args, env), env));
}

std::shared_ptr<Object const> eval(
		std::shared_ptr<Object const> const expr, Cons const &env) {
	switch(expr->index()) {
		case obj_index<Error>():
		case obj_index<Integer>():
		case obj_index<Function>():
		case obj_index<BuiltinFunction>():
			return expr;
		case obj_index<Cons>():
			if(auto const contained = std::get<Cons>(*expr);
					is_nil(contained)) {
				return expr;
			} else {
				return eval(contained, env);
			}
		case obj_index<Symbol>():
			return eval(std::get<Symbol>(*expr), env);
		case obj_index<Quote>():
			return std::get<Quote>(*expr).contained;
	}
	return nullptr; // Unreachable
					// ...unless expr is valueless, but that *should* never
					// happen
}

std::shared_ptr<Object const> eval(Cons const &list, Cons const &env) {
	if(auto const args = std::get_if<Cons>(cdr(list).get())) {
		return apply(eval(car(list), env), *args, env);
	} else {
		return std::make_shared<Object const>(
				Error{"car of argument passed to eval(cons) must be a cons"});
	}
}

std::shared_ptr<Object const> eval(Symbol const &symbol, Cons const &env) {
	if(!is_nil(env)) {
		if(std::holds_alternative<Symbol>(*car(car(env)))
				&& std::get<Symbol>(*car(car(env))) == symbol) {
			return cdr(car(env));
		} else if(std::holds_alternative<Cons>(*cdr(env))) {
			return eval(symbol, std::get<Cons>(*cdr(env)));
		}
	}
	return std::make_shared<Object const>(
			Error{"Unbound variable " + to_string(symbol)});
}

bool is_proper_list(Cons const &list) {
	if(is_nil(list)) {
		return true;
	} else {
		if(auto const next = std::get_if<Cons>(cdr(list).get())) {
			return is_proper_list(*next);
		} else {
			return false;
		}
	}
}

std::optional<Error> ensure_n_args(
		std::string_view const func_name, size_t n, Cons const &list) {
	if(!is_proper_list(list)) {
		return {Error{"Call to " + std::string(func_name)
				+ " must be a proper list"}};
	}

	size_t const length = list_length(list);
	if(length != n) {
		return {Error{std::string(func_name) + " expected " + std::to_string(n)
				+ " arguments but got " + std::to_string(length)}};
	}

	return std::nullopt;
}

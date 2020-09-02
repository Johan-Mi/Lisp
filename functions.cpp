#include "functions.hpp"
#include "to-string.hpp"

Cons make_nil() {
	return {nullptr, nullptr};
}

bool is_nil(Cons const &obj) {
	return !obj.first;
}

std::shared_ptr<Object const> car(std::shared_ptr<Object const> const obj) {
	if(std::holds_alternative<Error>(*obj)) {
		return obj;
	}

	return std::visit(
			[](auto const &arg) {
				using T = std::decay_t<decltype(arg)>;
				if constexpr(requires { car(arg); }) {
					return car(arg);
				} else {
					return std::make_shared<Object const>(
							Error{"car() called with invalid argument type "
									+ std::string(name_of_type<T>)});
				}
			},
			*obj);
}

std::shared_ptr<Object const> car(Cons const &obj) {
	if(is_nil(obj)) {
		return std::make_shared<Object const>(make_nil());
	} else {
		return obj.first;
	}
}

std::shared_ptr<Object const> cdr(std::shared_ptr<Object const> const obj) {
	if(std::holds_alternative<Error>(*obj)) {
		return obj;
	}

	return std::visit(
			[](auto const &arg) {
				using T = std::decay_t<decltype(arg)>;
				if constexpr(requires { cdr(arg); }) {
					return cdr(arg);
				} else {
					return std::make_shared<Object const>(
							Error{"cdr() called with invalid argument type "
									+ std::string(name_of_type<T>)});
				}
			},
			*obj);
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

Cons cons(std::shared_ptr<Object const> const first,
		std::shared_ptr<Object const> const second) {
	return Cons{first, second};
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
		return cons(
				std::make_shared<Object const>(cons(car(first), car(second))),
				std::make_shared<Object const>(
						join_two_lists(cdr(first), cdr(second), last)));
	}
}

std::shared_ptr<Object const> apply(
		std::shared_ptr<Object const> const func_obj, Cons const &args,
		Cons const &env) {
	if(std::holds_alternative<Error>(*func_obj)) {
		return func_obj;
	}

	if(auto const func = std::get_if<Function>(func_obj.get()); func) {
		return apply(*func, args, env);
	}

	if(auto const func = std::get_if<BuiltinFunction>(func_obj.get()); func) {
		return apply(*func, args, env);
	}

	return std::make_shared<Object const>(make_type_error("apply", *func_obj));
}

std::shared_ptr<Object const> apply(
		BuiltinFunction const &func, Cons const &args, Cons const &env) {
	return func.func(args, env);
}

std::shared_ptr<Object const> apply(
		Function const &func, Cons const &args, Cons const &env) {
	return eval(func.body, join_two_lists(func.parameters, args, env));
}

std::shared_ptr<Object const> eval(
		std::shared_ptr<Object const> const expr, Cons const &env) {
	if(std::holds_alternative<Error>(*expr)) {
		return expr;
	}

	return std::visit(
			[&env](auto const &contained) {
				using T = std::decay_t<decltype(contained)>;
				if constexpr(requires { eval(contained, env); }) {
					return eval(contained, env);
				} else {
					return std::make_shared<Object const>(
							Error{"eval() called with invalid argument type "
									+ std::string(name_of_type<T>)});
				}
			},
			*expr);
}

std::shared_ptr<Object const> eval(Cons const &list, Cons const &env) {
	if(is_nil(list)) {
		return std::make_shared<Object const>(make_nil());
	} else if(std::holds_alternative<Cons>(*cdr(list))) {
		return apply(eval(car(list), env), std::get<Cons>(*cdr(list)), env);
	} else {
		return std::make_shared<Object const>(
				Error{"car of argument passed to eval(cons) must be a cons"});
	}
}

std::shared_ptr<Object const> eval(Quote const &quote, Cons const &env) {
	return quote.contained;
}

std::shared_ptr<Object const> eval(Symbol const &symbol, Cons const &env) {
	if(is_nil(env)) {
		return std::make_shared<Object const>(
				Error{"Unbound variable " + to_string(symbol)});
	} else if(std::holds_alternative<Symbol>(*car(car(env)))
			&& std::get<Symbol>(*car(car(env))) == symbol) {
		return cdr(car(env));
	} else if(std::holds_alternative<Cons>(*cdr(env))) {
		return eval(symbol, std::get<Cons>(*cdr(env)));
	} else {
		return std::make_shared<Object const>(
				Error{"Unbound variable " + to_string(symbol)});
	}
}

std::shared_ptr<Object const> eval(Integer const &integer, Cons const &env) {
	return std::make_shared<Object const>(integer);
}

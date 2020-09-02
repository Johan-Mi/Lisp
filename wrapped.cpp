#include "wrapped.hpp"
#include "functions.hpp"

std::shared_ptr<Object const> wrapped_car(Cons const &args, Cons const &env) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object const>(
				Error{"wrapped_car() expected 1 argument but got "
						+ std::to_string(num_args)});
	}

	return car(eval(car(args), env));
}

std::shared_ptr<Object const> wrapped_cdr(Cons const &args, Cons const &env) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object const>(
				Error{"wrapped_cdr() expected 1 argument but got "
						+ std::to_string(num_args)});
	}

	return cdr(eval(car(args), env));
}

std::shared_ptr<Object const> wrapped_quote(Cons const &args, Cons const &env) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object const>(
				Error{"wrapped_quote() expected 1 argument but got "
						+ std::to_string(num_args)});
	}

	return car(args);
}

std::shared_ptr<Object const> wrapped_add(Cons const &args, Cons const &env) {
	if(is_nil(args)) {
		return std::make_shared<Object const>(Integer{0});
	} else {
		auto const lhs = eval(car(args), env);
		auto const unevaluated_rhs = cdr(args);
		if(!std::holds_alternative<Cons>(*unevaluated_rhs)) {
			return std::make_shared<Object const>(Error{
					"Arguments passed to wrapped_add must be a proper list"});
		}
		auto const rhs = wrapped_add(std::get<Cons>(*unevaluated_rhs), env);
		return add(lhs, rhs);
	}
}

std::shared_ptr<Object const> wrapped_sub(Cons const &args, Cons const &env) {
	size_t const num_args = list_length(args);
	switch(num_args) {
		case 0:
			return std::make_shared<Object const>(Error{
					"wrapped_sub() expected at least 1 argument but got 0"});
		case 1:
			return sub(std::make_shared<Object const>(Integer{0}),
					eval(car(args), env));
		default:
			auto const unevaluated_rhs = cdr(args);
			if(!std::holds_alternative<Cons>(*unevaluated_rhs)) {
				return std::make_shared<Object const>(
						Error{"Arguments passed to wrapped_sub must be a "
							  "proper list"});
			}
			return sub(eval(car(args), env),
					wrapped_add(std::get<Cons>(*unevaluated_rhs), env));
	}
}

std::shared_ptr<Object const> wrapped_mul(Cons const &args, Cons const &env) {
	if(is_nil(args)) {
		return std::make_shared<Object const>(Integer{1});
	} else {
		auto const lhs = eval(car(args), env);
		auto const unevaluated_rhs = cdr(args);
		if(!std::holds_alternative<Cons>(*unevaluated_rhs)) {
			return std::make_shared<Object const>(Error{
					"Arguments passed to wrapped_mul must be a proper list"});
		}
		auto const rhs = wrapped_mul(std::get<Cons>(*unevaluated_rhs), env);
		return mul(lhs, rhs);
	}
}

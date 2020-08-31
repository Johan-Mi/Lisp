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

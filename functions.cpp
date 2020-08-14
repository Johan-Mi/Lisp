#include "functions.hpp"

Cons make_nil() {
	return {nullptr, nullptr};
}

bool is_nil(Cons const &obj) {
	return !obj.first;
}

std::string to_string(std::shared_ptr<Object const> const obj) {
	return std::visit(
			[](auto const &arg) {
				return to_string(arg);
			},
			*obj);
}

std::string to_string(Cons const &obj) {
	if(is_nil(obj)) {
		return "()";
	} else {
		return to_string_cons('(' + to_string(car(obj)), cdr(obj));
	}
}

std::string to_string(Integer const &obj) {
	return std::to_string(obj.value);
}

std::string to_string(Bit const &obj) {
	return obj.value ? "1" : "0";
}

std::string to_string(Symbol const &obj) {
	return obj.name;
}

std::string to_string(Error const &obj) {
	return "Error: " + obj.message;
}

std::string to_string(Function const &obj) {
	return "Function " + to_string(obj.parameters) + " => "
			+ to_string(obj.body);
}

std::string to_string(BuiltinFunction const &obj) {
	return "Builtin function";
}

std::string to_string_cons(
		std::string const &accum, std::shared_ptr<Object const> const obj) {
	return std::visit(
			[&accum](auto const &arg) {
				return to_string_cons(accum, arg);
			},
			*obj);
}

template<>
std::string to_string_cons(std::string const &accum, Cons const &obj) {
	if(is_nil(obj)) {
		return accum + ')';
	} else {
		return to_string_cons(accum + ' ' + to_string(car(obj)), cdr(obj));
	}
}

std::shared_ptr<Object const> car(std::shared_ptr<Object const> const obj) {
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
	if(obj.first) {
		return obj.first;
	} else {
		return std::make_shared<Object const>(make_nil());
	}
}

std::shared_ptr<Object const> cdr(std::shared_ptr<Object const> const obj) {
	return std::visit(
			[](auto const &arg) {
				using T = std::decay_t<decltype(arg)>;
				if constexpr(requires { cdr(arg); }) {
					return cdr(arg);
				} else {
					return std::make_shared<Object const>(
							Error{"car() called with invalid argument type "
									+ std::string(name_of_type<T>)});
				}
			},
			*obj);
}

std::shared_ptr<Object const> cdr(Cons const &obj) {
	if(obj.second) {
		return obj.second;
	} else {
		return std::make_shared<Object const>(make_nil());
	}
}

Cons cons(std::shared_ptr<Object const> first,
		std::shared_ptr<Object const> const second) {
	return Cons{first, second};
}

size_t list_length(Cons const &list, size_t const accum = 0) {
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

std::shared_ptr<Object const> apply(
		std::shared_ptr<Object const> const func, Cons const &args) {
	return std::visit(
			[&args](auto const &contained) {
				if constexpr(requires { apply(contained, args); }) {
					return apply(contained, args);
				} else {
					return std::make_shared<Object const>(
							Error{"apply() called with invalid argument type"});
				}
			},
			*func);
}

std::shared_ptr<Object const> apply(
		BuiltinFunction const &func, Cons const &args) {
	return func.func(args);
}

std::shared_ptr<Object const> eval(
		Cons const &list, std::shared_ptr<Object const> const env) {
	if(std::holds_alternative<Cons>(*cdr(list))) {
		return apply(car(list), std::get<Cons>(*cdr(list)));
	} else {
		return std::make_shared<Object const>(
				Error{"car of argument passed to eval() must be a cons"});
	}
}

std::shared_ptr<Object const> nth(
		size_t const index, std::shared_ptr<Object const> const list) {
	return std::visit(
			[&index](auto const &arg) {
				if constexpr(requires { nth(index, arg); }) {
					return nth(index, arg);
				} else {
					return std::make_shared<Object const>(
							Error{"nth() called with invalid argument type"});
				}
			},
			*list);
}

std::shared_ptr<Object const> nth(size_t const index, Cons const &list) {
	if(index == 0) {
		return car(list);
	} else {
		return nth(index - 1, cdr(list));
	}
}

std::shared_ptr<Object const> wrapped_car(Cons const &args) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object const>(
				Error{"wrapped_car() expected 1 argument but got "
						+ std::to_string(num_args)});
	}

	return car(nth(0, args));
}

std::shared_ptr<Object const> wrapped_cdr(Cons const &args) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object const>(
				Error{"wrapped_cdr() expected 1 argument but got "
						+ std::to_string(num_args)});
	}

	return cdr(nth(0, args));
}

#include "functions.hpp"

std::string to_string(std::shared_ptr<Object> obj) {
	return std::visit([](auto &&arg){
			return to_string(arg);
			}, *obj);
}

std::string to_string(Nil const &obj) {
	return "nil";
}

std::string to_string(Cons const &obj) {
	return to_string_cons('(' + to_string(obj.first), obj.second);
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

std::string to_string_cons(std::string const &accum,
		std::shared_ptr<Object> obj) {
	return std::visit([&](auto &&arg){
			return to_string_cons(accum, arg);
			}, *obj);
}

template<>
std::string to_string_cons(std::string const &accum, Nil const &obj) {
	return accum + ')';
}

template<>
std::string to_string_cons(std::string const &accum, Cons const &obj) {
	return to_string_cons(accum + ' ' + to_string(obj.first), obj.second);
}

std::shared_ptr<Object> car(std::shared_ptr<Object> obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { car(arg); }) {
				return car(arg);
			} else {
				return std::make_shared<Object>(Error{
						"car() called with invalid argument type"});
			}
			}, *obj);
}

std::shared_ptr<Object> car(Cons const &obj) {
	return obj.first;
}

std::shared_ptr<Object> car(Nil const &obj) {
	return std::make_shared<Object>(Nil{});
}

std::shared_ptr<Object> cdr(std::shared_ptr<Object> obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { cdr(arg); }) {
				return cdr(arg);
			} else {
				return std::make_shared<Object>(Error{
						"car() called with invalid argument type"});
			}
			}, *obj);
}

std::shared_ptr<Object> cdr(Cons const &obj) {
	return obj.second;
}

std::shared_ptr<Object> cdr(Nil const &obj) {
	return std::make_shared<Object>(Nil{});
}

Cons cons(std::shared_ptr<Object> first, std::shared_ptr<Object> second) {
	return Cons{first, second};
}

size_t list_length(Cons const &list, size_t const accum = 0) {
	if(std::holds_alternative<Cons>(*cdr(list))) {
		return list_length(std::get<Cons>(*cdr(list)), accum + 1);
	} else {
		return accum + 1;
		// TODO Warn if cdr is not nil?
	}
}

std::shared_ptr<Object> apply(BuiltinFunction const &func, Cons const &args) {
	return func.func(args);
}

std::shared_ptr<Object> nth(size_t const index, std::shared_ptr<Object> list) {
	return std::visit([&index](auto &&arg){
			if constexpr(requires { nth(index, arg); }) {
				return nth(index, arg);
			} else {
				return std::make_shared<Object>(Error{
						"nth() called with invalid argument type"});
			}
			}, *list);
}

std::shared_ptr<Object> nth(size_t const index, Cons const &list) {
	if(index == 0) {
		return car(list);
	} else {
		return nth(index - 1, cdr(list));
	}
}

std::shared_ptr<Object> nth(size_t const index, Nil const &list) {
	return std::make_shared<Object>(Nil{});
}

std::shared_ptr<Object> wrapped_car(Cons const &args) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object>(Error{
				"wrapped_car() expected 1 argument but got "
				+ std::to_string(num_args)});
	}

	return car(nth(0, args));
}

std::shared_ptr<Object> wrapped_cdr(Cons const &args) {
	size_t const num_args = list_length(args);

	if(num_args != 1) {
		return std::make_shared<Object>(Error{
				"wrapped_cdr() expected 1 argument but got "
				+ std::to_string(num_args)});
	}

	return cdr(nth(0, args));
}

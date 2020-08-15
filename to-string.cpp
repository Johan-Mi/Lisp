#include "to-string.hpp"
#include "functions.hpp"

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

std::string to_string(Quote const &obj) {
	return "(quote " + to_string(obj.contained) + ')';
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

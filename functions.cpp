#include "functions.hpp"
#include "util.hpp"

std::string to_string(Object const &obj) {
	return std::visit([](auto &&arg){
			return to_string(arg);
			}, obj);
}

std::string to_string(Nil const &obj) {
	return "NIL";
}

std::string to_string(Cons const &obj) {
	return to_string_cons('(' + to_string(*obj.first), *obj.second);
}

std::string to_string(Integer const &obj) {
	return std::to_string(obj.value);
}

std::string to_string(Bit const &obj) {
	return obj.value ? "1" : "0";
}

std::string to_string(Symbol const &obj) {
	return obj.value;
}

std::string to_string(Error const &obj) {
	return "ERROR: " + obj.message;
}

template<>
std::string to_string_cons(std::string const &accum, Object const &obj) {
	return std::visit([&](auto &&arg){
			return to_string_cons(accum, arg);
			}, obj);
}

template<>
std::string to_string_cons(std::string const &accum, Nil const &obj) {
	return accum + ')';
}

template<>
std::string to_string_cons(std::string const &accum, Cons const &obj) {
	return to_string_cons(accum + ' ' + to_string(*obj.first), *obj.second);
}

std::shared_ptr<Object> car(Object const &obj) {
	return std::visit([](auto &&arg){
			using T = std::decay<decltype(arg)>;
			if constexpr(is_any_of<T, Cons, Nil>) {
				return car(arg);
			} else {
				return std::make_shared<Object>(Error{
						"car() called with invalid argument type"});
			}
			}, obj);
}

std::shared_ptr<Object> car(Cons const &obj) {
	return obj.first;
}

std::shared_ptr<Object> car(Nil const &obj) {
	return std::make_shared<Object>(Nil{});
}

std::shared_ptr<Object> cdr(Object const &obj) {
	return std::visit([](auto &&arg){
			using T = std::decay<decltype(arg)>;
			if constexpr(is_any_of<T, Cons, Nil>) {
				return cdr(arg);
			} else {
				return std::make_shared<Object>(Error{
						"car() called with invalid argument type"});
			}
			}, obj);
}

std::shared_ptr<Object> cdr(Cons const &obj) {
	return obj.second;
}

std::shared_ptr<Object> cdr(Nil const &obj) {
	return std::make_shared<Object>(Nil{});
}

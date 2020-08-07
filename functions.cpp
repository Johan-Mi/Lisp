#include "functions.hpp"

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

std::unique_ptr<Object> car(Object const &obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { car(arg); }) {
				return car(arg);
			} else {
				return std::make_unique<Object>(Nil{});
				// TODO Return an error
			}
			}, obj);
}

std::unique_ptr<Object> car(Cons const &obj) {
	return std::make_unique<Object>(*obj.first);
}

std::unique_ptr<Object> car(Nil const &obj) {
	return std::make_unique<Object>(Nil{});
}

std::unique_ptr<Object> cdr(Object const &obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { cdr(arg); }) {
				return cdr(arg);
			} else {
				return std::make_unique<Object>(Nil{});
				// TODO Return an error
			}
			}, obj);
}

std::unique_ptr<Object> cdr(Cons const &obj) {
	return std::make_unique<Object>(*obj.second);
}

std::unique_ptr<Object> cdr(Nil const &obj) {
	return std::make_unique<Object>(Nil{});
}

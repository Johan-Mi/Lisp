#include "functions.hpp"

std::unique_ptr<LispObject> car(LispObject &obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { car(arg); }) {
				return car(arg);
			} else {
				return std::make_unique<LispObject>(LispNil{});
				// TODO Return an error
			}
			}, obj);
}

std::unique_ptr<LispObject> car(LispCons &obj) {
	return std::move(obj.first);
}

std::unique_ptr<LispObject> car(LispNil &obj) {
	return std::make_unique<LispObject>(LispNil{});
}

std::unique_ptr<LispObject> cdr(LispObject &obj) {
	return std::visit([](auto &&arg){
			if constexpr(requires { cdr(arg); }) {
				return cdr(arg);
			} else {
				return std::make_unique<LispObject>(LispNil{});
				// TODO Return an error
			}
			}, obj);
}

std::unique_ptr<LispObject> cdr(LispCons &obj) {
	return std::move(obj.second);
}

std::unique_ptr<LispObject> cdr(LispNil &obj) {
	return std::make_unique<LispObject>(LispNil{});
}

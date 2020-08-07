#include <type_traits>

#include "types.hpp"

std::string to_string(LispObject const &obj) {
	return std::visit([](auto &&arg){
			return to_string(arg);
			}, obj);
}

std::string to_string(LispNil const &obj) {
	return "NIL";
}

std::string to_string(LispCons const &obj) {
	return to_string_cons("(" + to_string(*obj.first), *obj.second);
}

std::string to_string(LispInteger const &obj) {
	return std::to_string(obj.value);
}

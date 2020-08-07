#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	auto a = LispObject{LispCons{
				std::make_unique<LispObject>(LispInteger{1}),
				std::make_unique<LispObject>(LispCons{
						std::make_unique<LispObject>(LispInteger{2}),
						std::make_unique<LispObject>(LispNil{})})}};

	auto b = LispObject{LispCons{
				std::make_unique<LispObject>(LispNil{}),
				std::make_unique<LispObject>(LispNil{})}};

	auto c = LispObject{LispNil{}};

	std::cout << to_string(a) << '\n';
	std::cout << to_string(b) << '\n';
	
std::cout << to_string(c) << '\n';

	return EXIT_SUCCESS;
}

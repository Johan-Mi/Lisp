#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	auto a = Object{Cons{
				std::make_unique<Object>(Integer{1}),
				std::make_unique<Object>(Cons{
						std::make_unique<Object>(Integer{2}),
						std::make_unique<Object>(Nil{})})}};

	auto b = Object{Cons{
				std::make_unique<Object>(Nil{}),
				std::make_unique<Object>(Nil{})}};

	auto c = Object{Nil{}};

	auto d = Object{Cons{
				std::make_unique<Object>(Integer{1}),
				std::make_unique<Object>(Integer{2})}};

	std::cout << to_string(a) << '\n';
	std::cout << to_string(b) << '\n';
	std::cout << to_string(c) << '\n';
	std::cout << to_string(d) << '\n';

	return EXIT_SUCCESS;
}

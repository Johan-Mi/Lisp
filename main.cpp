#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	auto a = Object{Cons{
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Cons{
						std::make_shared<Object>(Integer{2}),
						std::make_shared<Object>(Nil{})})}};

	auto b = Object{Cons{
				std::make_shared<Object>(Nil{}),
				std::make_shared<Object>(Nil{})}};

	auto c = Object{Nil{}};

	auto d = Object{Cons{
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Integer{2})}};

	auto e = Object{Cons{
				std::make_shared<Object>(Bit{1}),
				std::make_shared<Object>(Bit{0})}};

	auto f = Object{Symbol{"foo"}};

	std::cout << to_string(a) << '\n';
	std::cout << to_string(b) << '\n';
	std::cout << to_string(c) << '\n';
	std::cout << to_string(d) << '\n';
	std::cout << to_string(e) << '\n';
	std::cout << to_string(f) << '\n';

	return EXIT_SUCCESS;
}

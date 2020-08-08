#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	auto const a = Object{Cons{
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Cons{
						std::make_shared<Object>(Integer{2}),
						std::make_shared<Object>(Nil{})})}};

	auto const b = Object{Cons{
				std::make_shared<Object>(Nil{}),
				std::make_shared<Object>(Nil{})}};

	auto const c = Object{Nil{}};

	auto const d = Object{Cons{
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Integer{2})}};

	auto const e = Object{Cons{
				std::make_shared<Object>(Bit{1}),
				std::make_shared<Object>(Bit{0})}};

	auto const f = Object{Symbol{"foo"}};

	std::cout << to_string(a) << '\n';
	std::cout << to_string(b) << '\n';
	std::cout << to_string(c) << '\n';
	std::cout << to_string(d) << '\n';
	std::cout << to_string(e) << '\n';
	std::cout << to_string(f) << '\n';
	std::cout << to_string(*car(f)) << '\n';

	return EXIT_SUCCESS;
}

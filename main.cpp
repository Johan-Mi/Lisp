#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	// (1 2)
	auto const a = std::make_shared<Object>(cons(
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(cons(
						std::make_shared<Object>(Integer{2}),
						std::make_shared<Object>(Nil{})))));

	// (NIL)
	auto const b = std::make_shared<Object>(cons(
				std::make_shared<Object>(Nil{}),
				std::make_shared<Object>(Nil{})));

	// NIL
	auto const c = std::make_shared<Object>(Nil{});

	// (1 . 2)
	auto const d = std::make_shared<Object>(cons(
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Integer{2})));

	// (1 . 0)
	auto const e = std::make_shared<Object>(cons(
				std::make_shared<Object>(Bit{1}),
				std::make_shared<Object>(Bit{0})));

	// foo
	auto const f = std::make_shared<Object>(Symbol{"foo"});

	std::cout << to_string(a) << '\n';
	std::cout << to_string(b) << '\n';
	std::cout << to_string(c) << '\n';
	std::cout << to_string(d) << '\n';
	std::cout << to_string(e) << '\n';
	std::cout << to_string(f) << '\n';
	std::cout << to_string(car(f)) << '\n';

	return EXIT_SUCCESS;
}

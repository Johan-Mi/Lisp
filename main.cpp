#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
	auto const a = std::make_shared<Object>(cons(
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(cons(
						std::make_shared<Object>(Integer{2}),
						std::make_shared<Object>(Nil{})))));

	auto const b = std::make_shared<Object>(cons(
				std::make_shared<Object>(Nil{}),
				std::make_shared<Object>(Nil{})));

	auto const c = std::make_shared<Object>(Nil{});

	auto const d = std::make_shared<Object>(cons(
				std::make_shared<Object>(Integer{1}),
				std::make_shared<Object>(Integer{2})));

	auto const e = std::make_shared<Object>(cons(
				std::make_shared<Object>(Bit{1}),
				std::make_shared<Object>(Bit{0})));

	auto const f = std::make_shared<Object>(Symbol{"foo"});

	std::cout << to_string(a) << '\n'; // (1 2)
	std::cout << to_string(car(a)) << '\n'; // 1
	std::cout << to_string(b) << '\n'; // (NIL)
	std::cout << to_string(c) << '\n'; // NIL
	std::cout << to_string(d) << '\n'; // (1 . 2)
	std::cout << to_string(e) << '\n'; // (1 . 0)
	std::cout << to_string(f) << '\n'; // foo
	std::cout << to_string(car(f)) << '\n'; // Error

	return EXIT_SUCCESS;
}

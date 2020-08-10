#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
#define X std::make_shared<Object>

	auto const a = X(cons(
				X(Integer{1}),
				X(cons(
						X(Integer{2}),
						X(Nil{})))));

	auto const b = X(cons(
				X(Nil{}),
				X(Nil{})));

	auto const c = X(Nil{});

	auto const d = X(cons(
				X(Integer{1}),
				X(Integer{2})));

	auto const e = X(cons(
				X(Bit{1}),
				X(Bit{0})));

	auto const f = X(Symbol{"foo"});

	auto const g = X(Function{
			cons(
					X(Symbol{"a"}),
					X(cons(
							X(Symbol{"b"}),
							X(Nil{})))),
			X(Integer{42})});

#undef X

	std::cout << to_string(a) << '\n'; // (1 2)
	std::cout << to_string(car(a)) << '\n'; // 1
	std::cout << to_string(cdr(a)) << '\n'; // (2)
	std::cout << to_string(cdr(cdr(a))) << '\n'; // nil
	std::cout << to_string(cdr(cdr(cdr(a)))) << '\n'; // nil
	std::cout << to_string(b) << '\n'; // (nil)
	std::cout << to_string(c) << '\n'; // nil
	std::cout << to_string(d) << '\n'; // (1 . 2)
	std::cout << to_string(e) << '\n'; // (1 . 0)
	std::cout << to_string(f) << '\n'; // foo
	std::cout << to_string(car(f)) << '\n'; // Error
	std::cout << to_string(g) << '\n'; // Function (a b) => 42

	return EXIT_SUCCESS;
}

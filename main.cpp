#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"

int main() {
#define X std::make_shared<Object const>

	auto const env = make_list();

	auto const a = X(make_list(X(Integer{1}), X(Integer{2})));

	auto const b = X(make_list(X(make_nil())));

	auto const c = X(make_nil());

	auto const d = X(make_unterminated_list(X(Integer{1}), X(Integer{2})));

	auto const e = X(make_unterminated_list(X(Bit{1}), X(Bit{0})));

	auto const f = X(Symbol{"foo"});

	auto const g = X(Function{
			make_list(X(Symbol{"a"}), X(Symbol{"b"})), X(Integer{42})});

	auto const h = X(BuiltinFunction{wrapped_car});

	auto const i = eval(make_list(h, a), env);

#undef X

	std::cout << to_string(a) << '\n'; // (1 2)
	std::cout << to_string(car(a)) << '\n'; // 1
	std::cout << to_string(cdr(a)) << '\n'; // (2)
	std::cout << to_string(cdr(cdr(a))) << '\n'; // ()
	std::cout << to_string(cdr(cdr(cdr(a)))) << '\n'; // ()
	std::cout << to_string(b) << '\n'; // (())
	std::cout << to_string(c) << '\n'; // ()
	std::cout << to_string(d) << '\n'; // (1 . 2)
	std::cout << to_string(e) << '\n'; // (1 . 0)
	std::cout << to_string(f) << '\n'; // foo
	std::cout << to_string(car(f)) << '\n'; // Error
	std::cout << to_string(g) << '\n'; // Function (a b) => 42
	std::cout << to_string(h) << '\n'; // Builtin function
	std::cout << to_string(i) << '\n'; // 1

	return EXIT_SUCCESS;
}

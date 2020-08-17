#include <cstdlib>
#include <iostream>

#include "types.hpp"
#include "functions.hpp"
#include "to-string.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {

#define X std::make_shared<Object const>

	auto const env = make_list();

	auto const a = X(make_list(X(std::get<0>(*parse_integer("1"))),
			X(std::get<0>(*parse_integer("2")))));

	auto const b = X(make_list(X(make_nil())));

	auto const c = X(make_nil());

	auto const d = X(make_unterminated_list(X(std::get<0>(*parse_integer("1"))),
			X(std::get<0>(*parse_integer("2")))));

	auto const f = X(std::get<0>(*parse_symbol("foo")));

	auto const g = X(Function{make_list(X(std::get<0>(*parse_symbol("a"))),
									  X(std::get<0>(*parse_symbol("b")))),
			X(std::get<0>(*parse_symbol("a")))});

	auto const h = X(BuiltinFunction{wrapped_car});

	auto const i = eval(make_list(h, X(Quote{a})), env);

	std::cout << to_string(a) << '\n'; // (1 2)
	std::cout << to_string(car(a)) << '\n'; // 1
	std::cout << to_string(cdr(a)) << '\n'; // (2)
	std::cout << to_string(cdr(cdr(a))) << '\n'; // ()
	std::cout << to_string(cdr(cdr(cdr(a)))) << '\n'; // ()
	std::cout << to_string(b) << '\n'; // (())
	std::cout << to_string(c) << '\n'; // ()
	std::cout << to_string(d) << '\n'; // (1 . 2)
	std::cout << to_string(f) << '\n'; // foo
	std::cout << to_string(eval(f, env)) << '\n'; // Error
	std::cout << to_string(car(f)) << '\n'; // Error
	std::cout << to_string(g) << '\n'; // Function (a b) => a
	std::cout << to_string(
			eval(make_list(g, X(Integer{5}), X(Integer{20})), env))
			  << '\n'; // 5
	std::cout << to_string(h) << '\n'; // Builtin function
	std::cout << to_string(i) << '\n'; // 1

#undef X

	return EXIT_SUCCESS;
}
